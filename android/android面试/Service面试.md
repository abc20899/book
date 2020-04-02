### 一、Service的应用场景，和Thread的区别

#### 1.Service是什么？
Service是一种可以在后台执行长时间运行操作而没有用户界面的应用组件。可由其他应用组件（如：Activity、Broadcast等）来启动，服务一旦启动后将在后台一直运行，即使启动它的组件已经被销毁了也不会受影响。可以把Service与Activity进行绑定，此时Service和Activity就可以进行数据交互。运行在主线程，不能执行长时间耗时操作。

#### 2.Service和Thread的区别。
Service定义 ：表示后台服务。Service的运行是依托于它所在的主线程上，不能直接做耗时操作。即使应用被关闭，这个Service仍然存在，可以在后台进行一些计算，进行数据统计之类的。Service开启子线程之后，就算Activity销毁了，Service也能继续执行对后台任务进行控制。

Thread定义 ：表示子线程。Thread是程序执行的最小单元，可以用它来执行一些异步操作，也就是耗时操作。Thread是相对独立的。

### 二、开启Service的两种方式以及区别

#### 1.startService() ：使用此方法启动Service之后，就会在后台无限期地运行，就算Activity被销毁了，也对Service不影响。除非手动关闭该Service才会停止。

使用步骤：

(1)定义一个类继承Service。

(2)在Manifest.xml文件中配置该Service。

(3)使用Context的startService(Intent)方法启动该Service。

(4)不再使用时，调用stopService(Intent)方法停止该服务。

#### 2.bindService ()：绑定Service的时候，Service和Activity即处于绑定状态，提供了一个客户端和服务端的接口，允许Service和Activity进行数据交互、交换请求等等。甚至Service和Activity在不同的进程时，可以进行进程间通信来传输数据。多个Activity可以绑定一个Service，当所有绑定取消之后，Service会自动被销毁。

使用步骤：

(1)创建BindService服务端，继承自Service，并在类中创建一个实现IBinder接口的实例对象，提供公共方法给客户端调用。

(2)从onBind()回调方法返回此Binder实例。

(3)在客户端中，从onServiceConnected()回调方法接收Binder，并使用提供的方法调用绑定服务。
