### 一、HandlerThread是什么

#### 1.HandlerThread产生背景

1)需要开启Thread子线程进行耗时操作。

2)多次创建和销毁线程是很耗系统资源的。

#### 2.HandlerThread是什么

HandlerThread = Handler + Thread + Looper

HandlerThread是一个内部有Looper的Thread。

#### 3.HandlerThread的特点

1)HandlerThread本质上是一个线程类，它继承了Thread。

2)HandlerThread有自己的内部Looper对象，可以进行looper循环。

3)通过获取HandlerThread的Looper对象传递给Handler对象，可以在handleMessae方法中执行异步任务。

4)优点是不会有堵塞，减少了对性能的消耗。

5)缺点是不能同时进行多任务处理，需要进行等待，处理效率较低。

6)与线程池侧重并发不同，HandlerThread是一个串行队列，HandlerThread背后只有一个线程。


### 二、handlerThread源码解析
   Handy class for starting a new thread that has a looper. The looper can then be 
   used to create handler classes
   
   继承Thread类 并创建了looper对象
   protected void onLooperPrepared() 在开启循环之前调用

    @Override
    public void run() {
        mTid = Process.myTid();
        Looper.prepare();  //初始化looper
        synchronized (this) {   //解决线程同步问题
            mLooper = Looper.myLooper();
            notifyAll();  //通知当前等待的线程  通知getLooper方法  阻塞等待完成同步问题
        }
        Process.setThreadPriority(mPriority);
        onLooperPrepared();
        Looper.loop();
        mTid = -1;
    }

     public Looper getLooper() {
        if (!isAlive()) {
            return null;
        }
        
        // If the thread has been started, wait until the looper has been created.
        synchronized (this) {
            while (isAlive() && mLooper == null) {
                try {
                    wait();
                } catch (InterruptedException e) {
                }
            }
        }
        return mLooper;
    }
