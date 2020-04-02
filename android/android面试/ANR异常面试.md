### 一、什么是ANR

ANR是Application Not Responding（程序未响应），系统回弹出对话框让用户进行等待或者关闭程序。一个Activity执行时间超过5s，一个Service执行时间超过10s，都会出现ANR。

### 二、造成ANR的主要原因

1.主线程中被耗时IO操作阻塞（从Android 4.0之后网络IO不允许在主线程中）。

2.主线程中存在耗时的计算。

Android中的哪些操作是在主线程呢？

1.Activity的所有生命周期都是执行在主线程的。

2.Service默认是执行在主线程的。

3.BroadcastReceiver的onReceive回调是执行在主线程的。

4.没有使用子线程的Looper的Handler的handleMessage，post(Runnable)是执行在主线程的。

5.AsyncTask的回调方法除了doInBackground，其他都是执行在主线程。

### 三、如何解决ANR

1.使用AsyncTask处理耗时IO操作。

2.使用Thread或者HandlerThread提高优先级。

3.使用Handler来处理工作线程的耗时任务。

4.Activity的onCreate和onResume回调中尽量避免耗时的代码。