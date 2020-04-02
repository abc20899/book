# 一、Activity生命周期
### 什么是Activity？
Activity是Android与用户进行交互的接口，它提供了一个界面，让用户进行点击、滑动等操作。

#### 1.Activity的四种状态
##### 1.running状态：处于活动状态，此时用户可以点击屏幕，屏幕会做出响应；处于Activity栈顶的状态。
##### 2.paused状态：处于Activity失去焦点的状态，或者被非全屏的Activity占据，或者被非透明状态处于栈顶。失去焦点的Activity所有的成员变量都还在，没有被销毁，只是暂时不能与用户进行交互。内存紧张时，该Activity会被销毁。
##### 3.stopped状态：当一个Activity被另一个Activity完全覆盖时，被覆盖那个Activity就处于stopped状态，它将不再是可见的，内存不紧张时，其成员变量就还在。
##### 4.killed状态：Activity被系统回收，所保存的信息和成员变量全都被销毁。

#### 2.Activity生命周期
##### 1.Activity启动：onCreate()——>onStart()——>onResume()
onCreate()：完成界面的初始化，数据加载等。
onStart()：处于用户可见的状态，但不能进行交互。
onResume()：用户可见，并能进行交互，可进行点击滑动等操作。

##### 2.点击Home键回到主界面（Activity不可见） ：onPause()——>onStop()
onPause()：
Activity处于可见的，但是不能被触摸的状态，对应的是onResume()方法。
onStop()：表明Activity处于完全不可见的状态，当内存紧张时，该Activity可能被回收。
##### 3.当再次回到原Activity时 ：onRestart()——>onStart()——>onResume()
onRestart()：由不可见状态变到可见状态的时候，会调用该方法。
onStart()：处于用户可见的状态，但不能进行交互。
onResume()：用户可见，并能进行交互，可进行点击滑动等操作。

##### 4.退出当前Activity时 ：onPause()——>onStop()——>onDestroy()
onPause()：Activity处于可见的，但是不能被触摸的状态，对应的是onResume()方法。
onStop()：表明Activity处于完全不可见的状态，当内存紧张时，该Activity可能被回收。
onDestroy()：表明Activity正在被销毁，由于回收和释放资源。

#### 3.Android进程优先级

##### 1.前台进程 ：处于前台正在与用户进行交互的Activity，或者在前台绑定的Service。

##### 2.可见进程 ：可见但不可交互的Activity。

##### 3.服务进程 ：在后台开启的Service就是服务进程。

##### 4.后台进程 ：当处于前台的Activity，被按下Home键之后，该Activity会变成后台进程，但后台进程不会被立马销毁，系统会根据内存情况进行相应的回收。

##### 5.空进程 ：表示没有活跃的组件，只是出于缓存的目的而保留，可被随时收回。

### 二、Android任务栈

任务栈是后进先出的栈结构，Android通过任务栈可以有序管理每一个Activity。任务栈并不是唯一的，一个App中可以有多个任务栈，但是，在某些情况下，一个Activity也可以独享一个任务栈。

### 三、Activity启动模式

##### 1.Standard模式 ：每次启动Activity都会创建一个Activity实例，加入任务栈中，不会考虑任务栈中是否有相同的Activity。较为消耗资源。

##### 2.SingleTop模式 ：栈顶复用模式，如果新创建的Activity与当前的Activity一致，处于栈顶的话，就不会创建新的Activity，而是复用栈顶的Activity。

##### 3.SingleTask模式 ：任务栈复用模式，在新建Activity之前会检测任务栈中是否有相同的Activity，有的话直接把Activity移到栈顶，这个Activity以上的Activity都会被移除和销毁；没有就新建一个。

##### 4.SingleInstance模式 ：在整个系统中，有且只有一个实例，而且这个Activity独享任务栈。

#### 场景
singleTop适合接收通知启动的内容显示页面。<br>
例如，某个新闻客户端的新闻内容页面，如果收到10个新闻推送，每次都打开一个新闻内容页面是很烦人的。<br>
singleTask适合作为程序入口点。<br>
例如浏览器的主界面。不管从多少个应用启动浏览器，只会启动主界面一次，其余情况都会走onNewIntent，并且会清空主界面上面的其他页面。<br>
singleInstance适合需要与程序分离开的页面。<br>
例如闹铃提醒，将闹铃提醒与闹铃设置分离。<br>
singleInstance不要用于中间页面，如果用于中间页面，跳转会有问题，比如：A -> B (singleInstance) -> C，完全退出后，在此启动，首先打开的是B。

### Activity状态的保存与恢复
Activity提供了相应的保存状态和恢复状态的回调方法。<br>
保存状态:<br>
onSaveInstanceState(Bundle)<br>
onSaveInstanceState(Bundle,PersistableBundle)<br>
恢复状态:<br>
onCreate(Bundle)<br>
onRestoreInstanceState(Bundle)<br>
onRestoreInstanceState(Bundle,PersistableBundle)<br>

#### 方法回调的时机说明
* onSaveInstanceState(Bundle)
	1. 该方法在onPause()之后，onStop()之前被触发
	2. Activity调用finish()方法关闭Activity时不回调该方法
	3. 当前Activity(A)开启另一个Activity(B)时触发回调。执行顺序为A.onPause()->B.onCreate()->B.onStart()->B.onResume()->A.onSaveInstanceState()->A.onStop。这里其实相当于给每一个Activity提供了一个在程序退到后台时保存状态的时机。但实际又是提前保存的状态。
	4. 锁屏或者Home键退出App时触发回调。执行顺序为onPause()->onSaveInstanceState()->onStop()
	5. 手机配置发生改变时，比如旋屏。
* onCreate(Bundle)或onRestoreInstanceState(Bundle)
  1. 重建Activity时触发，注意是“重建”
  2. 重建对应的操作：<br>
     App进程被系统异常杀死<br>
     手机配置改变，旋屏等<br>
  3. 应用退到后台，在“最近使用”列表中杀死App并会触发重建





### 四、Scheme跳转模式

android中的scheme是一种页面内跳转协议，是一种非常好的实现机制，通过定义自己的scheme协议，可以非常方便跳转app中的各个页面；通过scheme协议，服务器可以定制化告诉app跳转哪个页面，可以通过通知栏消息定制化跳转页面，可以通过H5页面跳转页面等。
