### 一、retrofit使用简介 

1.在retrofit中通过一个接口作为http请求的api接口

2.创建一个Retrofit实例

3.调用api接口

在Android Studio中添加下述依赖：

```
compile 'com.squareup.retrofit2:retrofit:2.0.1'

```
第一步：创建api接口

```
public interface NetApi {
    @GET("repos/{owner}/{repo}/contributors")
    Call<ResponseBody> contributorsBySimpleGetCall(@Path("owner") String owner, @Path("repo") String repo);
}
```
注意：@Path注解的内容与@GET注解{}中的参数是对应的。

```
//第二步：创建Retrofit对象
Retrofit retrofit = new Retrofit.Builder()
        .baseUrl("https://api.github.com/")
        .build();

//通过retrofit对象创建网络请求的接口
NetApi repo = retrofit.create(NetApi.class);

//第三步：调用网络请求的接口获取网络请求
retrofit2.Call<ResponseBody> call = repo.contributorsBySimpleGetCall("username", "path");
call.enqueue(new Callback<ResponseBody>() { //进行异步请求
    @Override
    public void onResponse(Call<ResponseBody> call, Response<ResponseBody> response) {
        //进行异步操作
    }

    @Override
    public void onFailure(Call<ResponseBody> call, Throwable t) {
        //执行错误回调方法
    }
});
```
### 二、retrofit源码解析-动态代理

1.首先，通过method把它转换成ServiceMethod。

2.然后，通过serviceMethod，args获取到okHttpCall对象。

3.最后，再把okHttpCall进一步封装并返回Call对象。

创建retrofit对象的方法如下：

```
Retrofit retrofit = new Retrofit.Builder()
        .baseUrl("https://api.github.com/")
        .build();
```
可见，在创建retrofit对象的时候用到了build()方法，该方法的实现如下：

```
public Retrofit build() {
  if (baseUrl == null) {
    throw new IllegalStateException("Base URL required.");
  }

  okhttp3.Call.Factory callFactory = this.callFactory;
  if (callFactory == null) {
    callFactory = new OkHttpClient(); //设置kHttpClient
  }

  Executor callbackExecutor = this.callbackExecutor;
  if (callbackExecutor == null) {
    callbackExecutor = platform.defaultCallbackExecutor(); //设置默认回调执行器
  }

  // Make a defensive copy of the adapters and add the default Call adapter.
  List<CallAdapter.Factory> adapterFactories = new ArrayList<>(this.adapterFactories);
  adapterFactories.add(platform.defaultCallAdapterFactory(callbackExecutor));

  // Make a defensive copy of the converters.
  List<Converter.Factory> converterFactories = new ArrayList<>(this.converterFactories);

  return new Retrofit(callFactory, baseUrl, converterFactories, adapterFactories,
      callbackExecutor, validateEagerly); //返回新建的Retrofit对象
}
```
方法最后返回了一个Retrofit对象。

通过retrofit对象创建网络请求的接口的方式如下：

```
NetApi repo = retrofit.create(NetApi.class);

```
此处调用了retrofit对象的create()方法，此方法的实现如下：

```
public <T> T create(final Class<T> service) {
  Utils.validateServiceInterface(service);
  if (validateEagerly) {
    eagerlyValidateMethods(service);
  }
  return (T) Proxy.newProxyInstance(service.getClassLoader(), new Class<?>[] { service },
      new InvocationHandler() {
        private final Platform platform = Platform.get();

        @Override public Object invoke(Object proxy, Method method, Object... args)
            throws Throwable {
          // If the method is a method from Object then defer to normal invocation.
          if (method.getDeclaringClass() == Object.class) {
            return method.invoke(this, args); //直接调用该方法
          }
          if (platform.isDefaultMethod(method)) {
            return platform.invokeDefaultMethod(method, service, proxy, args); //通过平台对象调用该方法
          }
          ServiceMethod serviceMethod = loadServiceMethod(method); //获取ServiceMethod对象
          OkHttpCall okHttpCall = new OkHttpCall<>(serviceMethod, args); //传入参数生成okHttpCall对象
          return serviceMethod.callAdapter.adapt(okHttpCall); //执行okHttpCall
        }
      });
}
```
总结：retrofit最终网络请求依然是通过调用okhttp3.0进行实现的。



