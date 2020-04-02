### 一、Glide使用方法

Glide是一款图片加载框架，可以本地或网络加载图片。

使用Glide需在build.gradle文件中添加下述代码：

```
compile 'com.github.bumptech.glide:glide:4.0.0'

```
使用Glide将网络图片加载到ImageView的方式如下：

```
Glide.with(this)
        .load("http://www.baidu.com/img/bdlogo.png")
        .into(imageView);

```

### 二、Glide源码分析

在上述Glide.with(this)的with方法实现如下：

```
/**
 * Begin a load with Glide that will tied to the give
 * @param activity The activity to use.
 * @return A RequestManager for the given FragmentActivity that can be used to start a load.
 */
public static RequestManager with(FragmentActivity activity) {
  return getRetriever(activity).get(activity);
}
```
RequestManager主要是用来管理与Glide进行绑定的Activity或Fragment的。

继续往下看，其中的getRetriever(activity)方法实现如下：

```
private static RequestManagerRetriever getRetriever(@Nullable Context context) {
  Preconditions.checkNotNull(
      context,
      "You cannot start a load on a not yet attached View or a  Fragment where getActivity() "
          + "returns null (which usually occurs when getActivity() is called before the Fragment "
          + "is attached or after the Fragment is destroyed).");
  return Glide.get(context).getRequestManagerRetriever();
}
```
可以看到，首先会进行判断非空的操作，之后将执行getRequestManagerRetriever()方法，该方法的实现如下：

```
public RequestManagerRetriever getRequestManagerRetriever() {
  return requestManagerRetriever;
}
```

该方法返回了一个RequestManagerRetriever对象。RequestManagerRetriever对象是用于将RequestManager与Activity或者Fragment进行绑定的一个管理类。

回到上面的getRetriever(activity).get(activity);，这里的get(activity)方法的实现如下：

```
public RequestManager get(FragmentActivity activity) {
  if (Util.isOnBackgroundThread()) { //运行在后台线程 判断是否是在主线程
    return get(activity.getApplicationContext()); //通过activity中的上下文获取RequestManager
  } else {
    assertNotDestroyed(activity); //判断未被销毁
    FragmentManager fm = activity.getSupportFragmentManager(); //通过activity获取FragmentManager
    return supportFragmentGet(activity, fm, null /*parentHint*/); //获取RequestManager
  }
}
```
其中的supportFragmentGet()方法的具体实现如下：

```
private RequestManager supportFragmentGet(Context context, FragmentManager fm,
    Fragment parentHint) {
  SupportRequestManagerFragment current = getSupportRequestManagerFragment(fm, parentHint); //获取支持RequestManager的Fragment
  RequestManager requestManager = current.getRequestManager(); //获取RequestManager
  if (requestManager == null) {
    Glide glide = Glide.get(context); //获取Glide实例
    requestManager =
        factory.build(glide, current.getGlideLifecycle(), current.getRequestManagerTreeNode()); //用工厂模式生成RequestManager
    current.setRequestManager(requestManager); //为Fragment设置RequestManager
  }
  return requestManager;
}
```
下面回到Glide.with(this).load(url)的load()方法，该方法的实现如下：

```
public RequestBuilder<Drawable> load(@Nullable Object model) {
  return asDrawable().load(model);
}

```
可以看到asDrawable()的具体实现如下：

```
public RequestBuilder<Drawable> asDrawable() {
  return as(Drawable.class).transition(new DrawableTransitionOptions());
}
```
其中as(class)方法具体实现如下：

```
public <ResourceType> RequestBuilder<ResourceType> as(Class<ResourceType> resourceClass) {
  return new RequestBuilder<>(glide, this, resourceClass);
}
```

而RequestBuilder的构造方法RequestBuilder<>(glide, this, resourceClass)的实现如下：

```
protected RequestBuilder(Glide glide, RequestManager requestManager,
    Class<TranscodeType> transcodeClass) {
  this.glide = glide;
  this.requestManager = requestManager;
  this.context = glide.getGlideContext();
  this.transcodeClass = transcodeClass;
  this.defaultRequestOptions = requestManager.getDefaultRequestOptions();
  this.requestOptions = defaultRequestOptions;
}
```
回退到as(Drawable.class).transition(new DrawableTransitionOptions());的transition方法，具体实现如下：

```
public RequestBuilder<TranscodeType> transition(
    @NonNull TransitionOptions<?, ? super TranscodeType> transitionOptions) {
  this.transitionOptions = Preconditions.checkNotNull(transitionOptions);
  return this;
}
```
该方法对传入的选项进行判断非空后，返回了RequestBuilder本身。

回退到asDrawable().load(model);的load()方法，实现如下：

```
public RequestBuilder<TranscodeType> load(@Nullable Object model) {
  return loadGeneric(model);
}
```
其中的loadGeneric(model)方法的实现如下：

```
private RequestBuilder<TranscodeType> loadGeneric(@Nullable Object model) {
  this.model = model;
  isModelSet = true;
  return this;
}

```
可以看到，该方法在对传入的参数进行设置之后，返回了RequestBuilder本身。

退回最前面的Glide.with(this) .load(url).into(imageView);的into(imageView)方法，该方法的具体实现如下：

```
public Target<TranscodeType> into(ImageView view) {
  Util.assertMainThread(); //检查是否在主线程
  Preconditions.checkNotNull(view); //判断view非空

  if (!requestOptions.isTransformationSet()
      && requestOptions.isTransformationAllowed()
      && view.getScaleType() != null) {
    if (requestOptions.isLocked()) {
      requestOptions = requestOptions.clone();
    }
    switch (view.getScaleType()) {
      case CENTER_CROP:
        requestOptions.optionalCenterCrop();
        break;
      case CENTER_INSIDE:
        requestOptions.optionalCenterInside();
        break;
      case FIT_CENTER:
      case FIT_START:
      case FIT_END:
        requestOptions.optionalFitCenter();
        break;
      case FIT_XY:
        requestOptions.optionalCenterInside();
        break;
      case CENTER:
      case MATRIX:
      default:
        // Do nothing.
    }
  }

  return into(context.buildImageViewTarget(view, transcodeClass));
}
```
该方法最后一行的into()方法的具体实现如下：

```
public <Y extends Target<TranscodeType>> Y into(@NonNull Y target) {
  Util.assertMainThread(); //判断运行在主线程
  Preconditions.checkNotNull(target); //判断传入的参数非空
  if (!isModelSet) { //判断不是模型集合
    throw new IllegalArgumentException("You must call #load() before calling #into()");
  }

  Request previous = target.getRequest(); //从参数中获取请求

  if (previous != null) { //参数的请求非空
    requestManager.clear(target); //从requestManager中移除当前传入的参数
  }

  requestOptions.lock(); //锁定当前选项
  Request request = buildRequest(target); //根据传入的参数新建请求
  target.setRequest(request); //为当前的参数设置请求
  requestManager.track(target, request); //requestManager进行参数与请求的追踪

  return target;
}
```
最终，Glide加载图片的操作将通过线程池进行完成。

总结：with()方法是对RequestManager进行配置，load()方法是对RequestBuilder进行配置，into()方法是通过线程池给imageView进行图片的加载设置。