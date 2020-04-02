### 一、什么是AsyncTask

AsyncTask是安卓提供的轻量级的异步类，使用时可以继承AsyncTask，在类中可以进行异步操作，可以把运算好的结果交给UI线程来进行UI的显示。适合做一些耗时比较短的操作，耗时长的操作适合用线程池。

AsyncTask本质上是一个封装了线程池和Handler的异步框架，主要是用来执行异步任务的，由于内部集成了Handler，所以能够方便的在UI线程与子线程中灵活的切换。

### 二、AsyncTask的使用方法

#### 1.三个参数

1)第一个参数是在执行AsyncTask时所要传入的参数，此参数可以在后台任务中使用。

2)第二个参数表示在后台执行任务时，需要在界面上显示的当前进度。

3)第三个参数是运算结果的返回值类型。

#### 2.五个方法

1)onRreExecute()方法 ：用来在执行异步任务之前执行初始化操作，是在UI线程中调用的，经常用来显示进度条。

2)doInBackground()方法 ：用来做耗时操作，在onRreExecute()方法之后调用，其返回结果会传到onPostExecute()方法里；同时也可以在其中调用publicProgress()方法来发布一个进度单位。

3)publicProgress()方法 ：用来发布当前执行的进度。

4)onProgressUpdate()方法 ：在publicProgress()执行完之后调用，用来动态显示进度条。

5)onPostExecute()方法 ：用来对doInBackground()的返回结果进行处理。

### 三、AsyncTask的机制原理

1.AsyncTask的本质是一个静态的线程池，AsyncTask派生出的子类可以实现不同的异步任务，这些任务都是提交到静态的线程池中执行。

2.线程池中的工作线程执行doInBackground(mParams)方法执行异步任务。

3.当任务状态改变之后，工作线程会向UI线程发送消息，AsyncTask内部的InternalHandler响应这些消息，并调用相关的回调函数。

总结 ：AsyncTask内部封装了线程池，通过Handler发送消息，在UI线程和子线程中传递。

### 四、AsyncTask注意事项

1.内存泄漏 ：AsyncTask声明在Activity是一个非静态的内部类，会持有Activity的匿名引用，当想销毁Activity时AsyncTask还在执行异步任务的话，Activity就不能销毁，会造成内存泄漏。

解决方法：

1.将AsyncTask设置成静态的。

2.让AsyncTask内部持有Activity的弱引用。

3.在Activity的onDestroy()方法中将AsyncTask给cancel掉。

2.生命周期 ：如果在Activity销毁前不将AsyncTask给cancel掉，AsyncTask是会一直存在的。所以必须在Activity的onDestroy()方法中将AsyncTask给cancel掉。

3.结果丢失 ：当Activity被销毁，而AsyncTask在执行异步任务，会重新创建Activity，但AsyncTask所持有的是之前的Activity的引用，所以onPostExecute()方法不会生效。

4.并行or串行 ：并行和串行都可以，为了保证安全性，一般只使用串行。
