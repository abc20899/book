### 一、Broadcast广播

#### 1.广播的定义

类似观察者模式，当数据变化时会通知观察者对相应的数据进行处理。在Android中，Broadcast是一种广泛运用的在应用程序之间传输信息的机制，Android中我们要发送的广播内容是一个Intent，这个Intent中可以携带我们要传送的数据。可以通过广播接收Service传来的消息，不用直接让Activity和Service交互。

#### 2.广播的使用场景

A.同一个App具有多个进程的不同组件之间的消息通信。

B.不同App之间的组件之间消息通信。

#### 3.广播种类

1) 普通广播：Context.sendBroadcast。

2) 系统广播（有序广播）：Context.sendOrderedBroadcast。

3) 本地广播：只在自身App内传播。

### 二、实现广播

#### 1.静态注册：在Manifest.xml中注册完成就一直运行，App关闭了也不受影响。

#### 2.动态注册：在代码中注册，跟随Activity的生命周期。

### 三、Broadcast内部实现机制

#### 1.自定义广播接收者BroadcastReceiver，并复写onRecvice()方法。

#### 2.通过Binder机制向AMS(Activity Manager Service)进行注册。

#### 3.广播发送者通过Binder机制向AMS发送广播。

#### 4.AMS查找符合相应条件(IntentFilter/Permission等)的BroadcastReceiver，将广播发送到BroadcastReceiver（一般是Activity）相应的消息循环队列中。

#### 5.消息循环拿到此广播，回调BroadcastReceiver中的onReceive()方法。

### 四、LocalBroadcastManager详解

#### 1.使用它发送的广播将只在自身App内传播，不用担心泄漏隐私数据。

#### 2.其他App无法对你的App发送该广播，因为App根本就不可能接收到非自身应用发送的该广播。

#### 3.比系统的全局广播更加高效。

#### 4.LocalBroadcastManager高效的原因是因为它内部使用了Handler发送Message来实现。

#### 5.系统广播通过Binder实现，因此LocalBroadcastManager的Handler机制更高效，而且发送消息也不会离开App内部。