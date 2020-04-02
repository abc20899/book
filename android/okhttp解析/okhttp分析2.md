**官网：**<br>
拦截器是OkHttp中提供一种强大机制，它可以实现网络监听、请求以及响应重写、请求失败重试等功能。

1.创建一系列拦截器，并将其放入一个拦截器list中<br>
2.创建一个拦截器链RealInterceptorChin，并执行拦截器链的proceed方法，也就是执行下一个拦截器

1.在发起请求前对request进行处理<br>
2.调用下一个拦截器，获取response<br>
3.对response进行处理，返回给上一个拦截器

**Interceptor接口**源码：

```
public interface Interceptor {
  Response intercept(Chain chain) throws IOException;

  interface Chain {
    Request request();

    Response proceed(Request request) throws IOException;

    /**
     * Returns the connection the request will be executed on. This is only available in the chains
     * of network interceptors; for application interceptors this is always null.
     */
    @Nullable Connection connection();

    Call call();

    int connectTimeoutMillis();

    Chain withConnectTimeout(int timeout, TimeUnit unit);

    int readTimeoutMillis();

    Chain withReadTimeout(int timeout, TimeUnit unit);

    int writeTimeoutMillis();

    Chain withWriteTimeout(int timeout, TimeUnit unit);
  }
}
```

**RealInterceptorChain类**核心源码

```
//实现Interceptor.Chain接口
public final class RealInterceptorChain implements Interceptor.Chain {
  private final List<Interceptor> interceptors;  //拦截器集合
  private final StreamAllocation streamAllocation;
  private final HttpCodec httpCodec;
  private final RealConnection connection;
  private final int index; //拦截器索引
  private final Request request;
  private final Call call;
  private final EventListener eventListener;
  private final int connectTimeout;
  private final int readTimeout;
  private final int writeTimeout;
  private int calls;
  
  //构造方法
   public RealInterceptorChain(List<Interceptor> interceptors, StreamAllocation streamAllocation,
      HttpCodec httpCodec, RealConnection connection, int index, Request request, Call call,
      EventListener eventListener, int connectTimeout, int readTimeout, int writeTimeout) {
        ......
        ......
        ......
  }
}


 //进行处理
  public Response proceed(Request request, StreamAllocation streamAllocation, HttpCodec httpCodec,
      RealConnection connection) throws IOException {
    //如果index索引大于 拦截器集合  则抛异常
    if (index >= interceptors.size()) throw new AssertionError();
     ......
     ......
     ......
    // Call the next interceptor in the chain.  index + 1 在链中调用下一个拦截器 实例化自己Chain对象
    RealInterceptorChain next = new RealInterceptorChain(interceptors, streamAllocation, httpCodec,
        connection, index + 1, request, call, eventListener, connectTimeout, readTimeout,
        writeTimeout);
    //获取拦截器Interceptor类型对象执行intercept(Chain chain)方法
    Interceptor interceptor = interceptors.get(index); 
    //传入chain类型对象next 返回Response
    Response response = interceptor.intercept(next);   
    ......
    ......
    ......
    return response;
  }

```

**RetryAndFollowUpInterceptor类 重定向拦截器**核心源码：

```
//实现Interceptor接口 实现intercept(Chain chain)方法
public final class RetryAndFollowUpInterceptor implements Interceptor {
  
  //执行intercept方法   Chain chain 转换为 RealInterceptorChain对象
  @Override public Response intercept(Chain chain) throws IOException {
    Request request = chain.request();
    RealInterceptorChain realChain = (RealInterceptorChain) chain;
    Call call = realChain.call();
    EventListener eventListener = realChain.eventListener();

    //创建streamAllocation对象  网络请求所需的组件
    streamAllocation = new StreamAllocation(client.connectionPool(), createAddress(request.url()),
        call, eventListener, callStackTrace);

    int followUpCount = 0;
    Response priorResponse = null;
    while (true) {
      if (canceled) {
        streamAllocation.release();
        throw new IOException("Canceled");
      }

      Response response;
      boolean releaseConnection = true;
      try {
        //执行proceed 下一个拦截器
        response = realChain.proceed(request, streamAllocation, null, null);
        releaseConnection = false;
      } catch (RouteException e) {
        // The attempt to connect via a route failed. The request will not have been sent.
        if (!recover(e.getLastConnectException(), false, request)) {
          throw e.getLastConnectException();
        }
        releaseConnection = false;
        continue;
      } catch (IOException e) {
        // An attempt to communicate with a server failed. The request may have been sent.
        boolean requestSendStarted = !(e instanceof ConnectionShutdownException);
        if (!recover(e, requestSendStarted, request)) throw e;
        releaseConnection = false;
        continue;
      } finally {
        // We're throwing an unchecked exception. Release any resources.
        if (releaseConnection) {
          streamAllocation.streamFailed(null);
          streamAllocation.release();
        }
      }

      // Attach the prior response if it exists. Such responses never have a body.
      if (priorResponse != null) {
        response = response.newBuilder()
            .priorResponse(priorResponse.newBuilder()
                    .body(null)
                    .build())
            .build();
      }

      Request followUp = followUpRequest(response);

      if (followUp == null) {
        if (!forWebSocket) {
          streamAllocation.release();
        }
        return response;
      }

      closeQuietly(response.body());

      //MAX_FOLLOW_UPS 为20  重试最大次数为20
      if (++followUpCount > MAX_FOLLOW_UPS) {
        streamAllocation.release();
        throw new ProtocolException("Too many follow-up requests: " + followUpCount);
      }

      if (followUp.body() instanceof UnrepeatableRequestBody) {
        streamAllocation.release();
        throw new HttpRetryException("Cannot retry streamed HTTP body", response.code());
      }

      if (!sameConnection(response, followUp.url())) {
        streamAllocation.release();
        streamAllocation = new StreamAllocation(client.connectionPool(),
            createAddress(followUp.url()), call, eventListener, callStackTrace);
      } else if (streamAllocation.codec() != null) {
        throw new IllegalStateException("Closing the body of " + response
            + " didn't close its backing stream. Bad interceptor?");
      }

      request = followUp;
      priorResponse = response;
    }
  }
}
```
**作用**<br>
1. 创建 streamAllocation对象<br>
2. 调用RealInterceptorChain.proceed()方法进行网络请求<br>
3. 根据异常结果或者响应结果判定是否进行重新请求<br>
4. 调用下一个拦截器，对response进行处理，返回给上一个拦截器。<br>

**BridgeInterceptor类 桥接拦截器**核心源码：<br>

```
//为request添加头部信息  
public final class BridgeInterceptor implements Interceptor {
   @Override public Response intercept(Chain chain) throws IOException {
    Request userRequest = chain.request();  
    Request.Builder requestBuilder = userRequest.newBuilder();

    RequestBody body = userRequest.body();
    if (body != null) {
      MediaType contentType = body.contentType();
      if (contentType != null) {
        requestBuilder.header("Content-Type", contentType.toString());
      }

      long contentLength = body.contentLength();
      if (contentLength != -1) {
        requestBuilder.header("Content-Length", Long.toString(contentLength));
        requestBuilder.removeHeader("Transfer-Encoding");
      } else {
        requestBuilder.header("Transfer-Encoding", "chunked");
        requestBuilder.removeHeader("Content-Length");
      }
    }

    if (userRequest.header("Host") == null) {
      requestBuilder.header("Host", hostHeader(userRequest.url(), false));
    }

    if (userRequest.header("Connection") == null) {
      requestBuilder.header("Connection", "Keep-Alive"); //保持连接
    }

    // If we add an "Accept-Encoding: gzip" header field we're responsible for also decompressing
    // the transfer stream.
    boolean transparentGzip = false;
    if (userRequest.header("Accept-Encoding") == null && userRequest.header("Range") == null) {
      transparentGzip = true;
      requestBuilder.header("Accept-Encoding", "gzip");
    }

    List<Cookie> cookies = cookieJar.loadForRequest(userRequest.url());
    if (!cookies.isEmpty()) {
      requestBuilder.header("Cookie", cookieHeader(cookies));
    }

    if (userRequest.header("User-Agent") == null) {
      requestBuilder.header("User-Agent", Version.userAgent());
    }

    //执行下一个拦截器
    Response networkResponse = chain.proceed(requestBuilder.build());
    HttpHeaders.receiveHeaders(cookieJar, userRequest.url(), networkResponse.headers());

    Response.Builder responseBuilder = networkResponse.newBuilder()
        .request(userRequest);

    if (transparentGzip
        && "gzip".equalsIgnoreCase(networkResponse.header("Content-Encoding"))
        && HttpHeaders.hasBody(networkResponse)) {
      GzipSource responseBody = new GzipSource(networkResponse.body().source());
      Headers strippedHeaders = networkResponse.headers().newBuilder()
          .removeAll("Content-Encoding")
          .removeAll("Content-Length")
          .build();
      responseBuilder.headers(strippedHeaders);
      String contentType = networkResponse.header("Content-Type");
      responseBuilder.body(new RealResponseBody(contentType, -1L, Okio.buffer(responseBody)));
    }

    return responseBuilder.build();
  }
}
```

**作用**<br>
1.设置编码方式，内容长度，压缩等header设置的内容<br>
2.负责将用户构建的一个Request请求转换为能够进行网络访问的请求<br>
3.将这个符合网络请求的Requst进行网络请求<br>
4.将网络请求回来的响应Response转换为用户可用的Respnse。


**CacheInterceptor类 缓存拦截器**核心源码：<br>
使用<br>

```
okhttpClient.Builder().cache()方法
.cache(new Cache(new File("file"), 24 * 24 * 1024))
```


**作用**<br>
为下一次网络请求提速
[链接](http://lowett.com/2017/03/09/okhttp-6/)
Cache类：

```
//put方法
@Nullable CacheRequest put(Response response) {
    //获取method
    String requestMethod = response.request().method();

    //是否有效
    if (HttpMethod.invalidatesCache(response.request().method())) {
      try {
        remove(response.request());
      } catch (IOException ignored) {
        // The cache cannot be written.
      }
      return null;
    }
    //如果是get 不缓存
    if (!requestMethod.equals("GET")) {
      // Don't cache non-GET responses. We're technically allowed to cache
      // HEAD requests and some POST requests, but the complexity of doing
      // so is high and the benefit is low.
      return null;
    }

    if (HttpHeaders.hasVaryAll(response)) {
      return null;
    }
 
    //创建entry对象
    Entry entry = new Entry(response);
    DiskLruCache.Editor editor = null; //DiskLruCache 缓存算法实现 内部维护了一个清理线程池，自动清理
    try {
      editor = cache.edit(key(response.request().url()));
      if (editor == null) {
        return null;
      }
      entry.writeTo(editor);
      return new CacheRequestImpl(editor); //保存body
    } catch (IOException e) {
      abortQuietly(editor);
      return null;
    }
  }
```
1. 判断是否是get方法
2. 创建entry对象写入缓存的信息
3. 返回CacheRequestImpl对象 写入body

```
 //从缓存中读取
  @Nullable Response get(Request request) {
    String key = key(request.url());
    DiskLruCache.Snapshot snapshot; //缓存快照
    Entry entry;
    try {
      snapshot = cache.get(key); //根据key返回
      if (snapshot == null) {
        return null;
      }
    } catch (IOException e) {
      // Give up because the cache cannot be read.
      return null;
    }

    try {
      entry = new Entry(snapshot.getSource(ENTRY_METADATA)); //创建entry对象
    } catch (IOException e) {
      Util.closeQuietly(snapshot);
      return null;
    }

    Response response = entry.response(snapshot); //获取响应对象

    if (!entry.matches(request, response)) {  //匹配请求响应
      Util.closeQuietly(response.body());
      return null;
    }

    return response;
  }
```

**ConnectInterceptor连接池拦截器**

1. 弄一个RealConnection对象
2. 选择不同的链接方式
3. CallServerInterceptor  完成整个http操作

**CallServerInterceptor**

1. 产生一个streamAllocation对象
2. streamAllocation的弱引用添加到RealConnection对象的allocations集合
3. 从连接池中获取

连接池清理<br>
1. gc算法 标记清除
2. streamAllocation的数量会渐渐变成0
3. 被线程池检测到并回收，这样就可以保持多个健康的keep-alive连接


**CallServerInterceptor**
读取网络响应

#### 总结
1. Call对象的对请求的封装
2. dispatcher对请求的分发
3. getResponseWithIntercepter()方法拦截器链
4. 重试重定向请求(RetryAndFollowUpInterceptor):
   缓存(CacheInterceptor):处理缓存拦截器
   桥接(BrigeInterceptor):转换请求
   连接(ConnectionInterceptor):和流对象建立连接
   完成最终(CallServerInterceptor):完成最终的网络请求
   