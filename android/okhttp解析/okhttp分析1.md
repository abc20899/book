### 请求流程分析
1.创建httpclient对象(build设计模式) 全局实例 

```
OkHttpClient okHttpClient = new OKhttpClient.Builder().xx().build();
//创建builder时 已经实例化请求分发器
//dispatcher = new Dispatcher();  
```

2.创建Request对象

```
Request request = new Request.Builder().url().params().get().build();
```

3.返回Call对象,发起请求并接受返回结果

**同步**

```
 //返回一个Call对象  链接request和response的桥梁
 //RealCall.newRealCall(this, request, false);
  Call call = okHttpClient.newCall(request); 
  //发起请求 同步方式
  try {
      Response response = call.execute(); //会阻塞当前线程 直到有响应
      System.out.println("syncRequest: " + response.body().toString());
  } catch (IOException e) {
      e.printStackTrace();
  }
```

**异步**

```
//发起请求 异步方式  会开启一个新工作线程
call.enqueue(new Callback() {
    @Override
    public void onFailure(Call call, IOException e) {
    }

    @Override
    public void onResponse(Call call, Response response) throws IOException {
        System.out.println("asynRequest: " + response.body().toString());
    }
});
```

**OkHttpClient类中**newCall(request); 方法源码分析

```
 /**
   * 返回call对象
   */
  @Override public Call newCall(Request request) {
    return RealCall.newRealCall(this, request, false /* for web socket */);
  }
```

**RealCall类中**newRealCall(OkHttpClient client, Request originalRequest, boolean forWebSocket)方法源码

```
 static RealCall newRealCall(OkHttpClient client, Request originalRequest, boolean forWebSocket) {
    // 实例化 返回RealCall 对象
    RealCall call = new RealCall(client, originalRequest, forWebSocket);
    call.eventListener = client.eventListenerFactory().create(call);
    return call;
  }
```

```
//同步方法执行
  @Override public Response execute() throws IOException {
    synchronized (this) {
      //executed 标志位同一个请求只能执行一次  没有执行过设置为true
      if (executed) throw new IllegalStateException("Already Executed");
      executed = true;
    }
    captureCallStackTrace();  //捕捉异常堆栈信息
    eventListener.callStart(this);
    try {
      client.dispatcher().executed(this); //label-2 分发器对象将同步请求加入到同步请求队列当中
      Response result = getResponseWithInterceptorChain(); //label-3拦截器链
      if (result == null) throw new IOException("Canceled");
      return result;
    } catch (IOException e) {
      eventListener.callFailed(this, e);
      throw e;
    } finally {
      client.dispatcher().finished(this); //主动回收请求
    }
  }
```

```
 //异步请求 数据返回responseCallback接口
  @Override public void enqueue(Callback responseCallback) {
    synchronized (this) {
      // executed call对象是否执行过
      if (executed) throw new IllegalStateException("Already Executed");
      executed = true;
    }
    captureCallStackTrace();
    eventListener.callStart(this);
    //实例化AsyncCall对象 实现Runnable接口
    //label-4
    client.dispatcher().enqueue(new AsyncCall(responseCallback));
  }
```

*label-2*
**OkHttpClient类**dispatcher()方法源码:

```
//返回初始化好的dispatcher对象
public Dispatcher dispatcher() {
    return dispatcher;
  }
```
**Dispatcher类中** synchronized void executed(RealCall call);源码

```
//同步请求
  synchronized void executed(RealCall call) {
    runningSyncCalls.add(call);  //将同步请求加入到同步请求队列当中
  }
```

**Dispatcher类源码**

```
public final class Dispatcher {
  private int maxRequests = 64; //最大请求数目
  
  private int maxRequestsPerHost = 5; //最大主机数目
  
  private @Nullable Runnable idleCallback;

  /** 线程池 懒加载*/
  private @Nullable ExecutorService executorService;

  //缓存的请求队列
  private final Deque<AsyncCall> readyAsyncCalls = new ArrayDeque<>();

  //正在运行的 异步请求队列
  private final Deque<AsyncCall> runningAsyncCalls = new ArrayDeque<>();

  //正在运行的同步请求队列
  private final Deque<RealCall> runningSyncCalls = new ArrayDeque<>();

  public Dispatcher(ExecutorService executorService) {
    this.executorService = executorService;
  }

  public Dispatcher() {
  }

  //返回一个线程池对象
  public synchronized ExecutorService executorService() {
    if (executorService == null) {
//    核心线程数目为0 空闲时全部消毁    最大线程数Integer.MAX_VALUE 无限扩充    线程池最多存活60秒
      executorService = new ThreadPoolExecutor(0, Integer.MAX_VALUE, 60, TimeUnit.SECONDS,
          new SynchronousQueue<Runnable>(), Util.threadFactory("OkHttp Dispatcher", false));
    }
    return executorService;
  }

  public synchronized void setMaxRequests(int maxRequests) {
    if (maxRequests < 1) {
      throw new IllegalArgumentException("max < 1: " + maxRequests);
    }
    this.maxRequests = maxRequests;
    promoteCalls();
  }

  public synchronized int getMaxRequests() {
    return maxRequests;
  }

  public synchronized void setMaxRequestsPerHost(int maxRequestsPerHost) {
    if (maxRequestsPerHost < 1) {
      throw new IllegalArgumentException("max < 1: " + maxRequestsPerHost);
    }
    this.maxRequestsPerHost = maxRequestsPerHost;
    promoteCalls();
  }

  public synchronized int getMaxRequestsPerHost() {
    return maxRequestsPerHost;
  }

  public synchronized void setIdleCallback(@Nullable Runnable idleCallback) {
    this.idleCallback = idleCallback;
  }

  //异步请求
  synchronized void enqueue(AsyncCall call) {
    //判断异步请求队列是否小于最大请求数  并且运行的主机是否小于最大
    if (runningAsyncCalls.size() < maxRequests && runningCallsForHost(call) < maxRequestsPerHost) {
      runningAsyncCalls.add(call);  //添加到异步队列
      executorService().execute(call); //开启线程池执行
    } else {
      readyAsyncCalls.add(call);  //如果当前请求数目大于64 或者host数目大于5  添加到缓存池当中
    }
  }

  public synchronized void cancelAll() {
    for (AsyncCall call : readyAsyncCalls) {
      call.get().cancel();
    }

    for (AsyncCall call : runningAsyncCalls) {
      call.get().cancel();
    }

    for (RealCall call : runningSyncCalls) {
      call.cancel();
    }
  }

  private void promoteCalls() {
    if (runningAsyncCalls.size() >= maxRequests) return; // Already running max capacity.
    if (readyAsyncCalls.isEmpty()) return; // No ready calls to promote.
//从缓存池中迭代 添加到正在执行的队列中 继续执行
    for (Iterator<AsyncCall> i = readyAsyncCalls.iterator(); i.hasNext(); ) {
      AsyncCall call = i.next();

      if (runningCallsForHost(call) < maxRequestsPerHost) {
        i.remove();
        runningAsyncCalls.add(call);
        executorService().execute(call);
      }

      if (runningAsyncCalls.size() >= maxRequests) return; // Reached max capacity.
    }
  }

  private int runningCallsForHost(AsyncCall call) {
    int result = 0;
    for (AsyncCall c : runningAsyncCalls) {
      if (c.host().equals(call.host())) result++;
    }
    return result;
  }

  //同步请求
  synchronized void executed(RealCall call) {
    runningSyncCalls.add(call);  //将同步请求加入到同步请求队列当中
  }

  //结束异步请求队列中的
  void finished(AsyncCall call) {
    finished(runningAsyncCalls, call, true);
  }

  //结束同步请求中的某个请求
  void finished(RealCall call) {
    finished(runningSyncCalls, call, false);
  }

  //从请求队列当中移除请求
  private <T> void finished(Deque<T> calls, T call, boolean promoteCalls) {
    int runningCallsCount;
    Runnable idleCallback;
    synchronized (this) {
    //从队列中删除请求
      if (!calls.remove(call)) throw new AssertionError("Call wasn't in-flight!");
      if (promoteCalls) promoteCalls();
      runningCallsCount = runningCallsCount();   //重新计算队列
      idleCallback = this.idleCallback;
    }

    //为0 没有请求
    if (runningCallsCount == 0 && idleCallback != null) {
      idleCallback.run();
    }
  }

  /** Returns a snapshot of the calls currently awaiting execution. */
  public synchronized List<Call> queuedCalls() {
    List<Call> result = new ArrayList<>();
    for (AsyncCall asyncCall : readyAsyncCalls) {
      result.add(asyncCall.get());
    }
    return Collections.unmodifiableList(result);
  }

  /** Returns a snapshot of the calls currently being executed. */
  public synchronized List<Call> runningCalls() {
    List<Call> result = new ArrayList<>();
    result.addAll(runningSyncCalls);
    for (AsyncCall asyncCall : runningAsyncCalls) {
      result.add(asyncCall.get());
    }
    return Collections.unmodifiableList(result);
  }

  public synchronized int queuedCallsCount() {
    return readyAsyncCalls.size();
  }

  //同步和异步总共的数目
  public synchronized int runningCallsCount() {
    return runningAsyncCalls.size() + runningSyncCalls.size();
  }
}
```

*label-4*
**RealCall类中**内部类AsyncCall类

```
 //异步回调接口 继承runnable接口
  final class AsyncCall extends NamedRunnable {
    private final Callback responseCallback; //响应回调

    AsyncCall(Callback responseCallback) {
      super("OkHttp %s", redactedUrl());
      this.responseCallback = responseCallback;
    }

    String host() {
      return originalRequest.url().host();
    }

    Request request() {
      return originalRequest;
    }

    RealCall get() {
      return RealCall.this;
    }

    @Override protected void execute() {
      boolean signalledCallback = false;
      try {
        //接受返回的数据 通过拦截器  label-3
        Response response = getResponseWithInterceptorChain();
        if (retryAndFollowUpInterceptor.isCanceled()) {
          signalledCallback = true;
          responseCallback.onFailure(RealCall.this, new IOException("Canceled"));
        } else {
          signalledCallback = true;
          responseCallback.onResponse(RealCall.this, response);
        }
      } catch (IOException e) {
        if (signalledCallback) {
          // Do not signal the callback twice!
          Platform.get().log(INFO, "Callback failure for " + toLoggableString(), e);
        } else {
          eventListener.callFailed(RealCall.this, e);
          responseCallback.onFailure(RealCall.this, e);
        }
      } finally {
        //从队列中移除此次请求 结束线程
        client.dispatcher().finished(this);
      }
    }
  }
```

**NamedRunnable抽象类**源码：

```
public abstract class NamedRunnable implements Runnable {
  protected final String name;

  public NamedRunnable(String format, Object... args) {
    this.name = Util.format(format, args);
  }

  @Override public final void run() {
    String oldName = Thread.currentThread().getName();
    Thread.currentThread().setName(name);
    try {
      execute(); //子类执行
    } finally {
      Thread.currentThread().setName(oldName);
    }
  }

  protected abstract void execute();
}
```

*label-3*

```
//执行拦截器链
  Response getResponseWithInterceptorChain() throws IOException {
    // Build a full stack of interceptors.
    List<Interceptor> interceptors = new ArrayList<>();
    interceptors.addAll(client.interceptors());    //用户自定义拦截器 应用拦截器
    interceptors.add(retryAndFollowUpInterceptor);
    interceptors.add(new BridgeInterceptor(client.cookieJar()));
    interceptors.add(new CacheInterceptor(client.internalCache()));
    interceptors.add(new ConnectInterceptor(client));
    if (!forWebSocket) {
      interceptors.addAll(client.networkInterceptors());
    }
    interceptors.add(new CallServerInterceptor(forWebSocket));

    //将拦截器集合传入RealInterceptorChain 构造方法中
    // RealInterceptorChain实现 Interceptor.Chain接口
    Interceptor.Chain chain = new RealInterceptorChain(interceptors, null, null, null, 0,
        originalRequest, this, eventListener, client.connectTimeoutMillis(),
        client.readTimeoutMillis(), client.writeTimeoutMillis());

    return chain.proceed(originalRequest);
  }
```



