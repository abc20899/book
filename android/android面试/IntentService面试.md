### 一、IntentService是什么
   是一个特殊的Service，继承Service，优先级比Service高，内部通过HandlerThread和Handler实现异步操作
   IntentService是继承并处理异步请求的一个类，在IntentService内有一个工作线程来处理耗时操作，启动IntentService的方式和
   启动传统的Service一样，同事，当任务执行完后，IntentService会自动停止，而不需要我们手动控制或stopSelf(),另外可以启动
   IntentService多次，而每一个耗时操作会以工作队列的方式在IntentService的onHandleIntent方法中执行，并且每次只会执行一个工作线程
   ，执行完再执行第二个。
   
### 二、IntentService的使用
   继承IntentService  构造方法(String)  onHandleIntent方法  

### 三、IntentService源码解析
    onCreate方法中创建HandlerThread对象
    HandlerThread thread = new HandlerThread("IntentService[" + mName + "]");
    thread.start();  //启动
    mServiceLooper = thread.getLooper(); //获取looper对象
    mServiceHandler = new ServiceHandler(mServiceLooper);  //实例化handler

     private final class ServiceHandler extends Handler {
        public ServiceHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            onHandleIntent((Intent)msg.obj);
            stopSelf(msg.arg1);
        }
    }

    //实现方法
    protected abstract void onHandleIntent(@Nullable Intent intent);

