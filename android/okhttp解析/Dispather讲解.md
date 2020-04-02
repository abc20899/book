Dispather
1.如何实现同步和异步请求
发送的同步/异步请求都会在dispatcher中管理其状态

2.到底什么是dispatcher
dispatcher的作用是为维护请求的状态，并维护一个线程池，用于执行相应的请求。

每当有请求时通过call来封装通过dispatcher推送到readAsyncCalls队列里面类进行判断
维护任务队列的作用

3.异步请求为什么需要两个队列
dispatcher：生产者
ExcutorService：消费池

//缓存队列
private final Deque<AsyncCall> readyAsyncCalls = new ArrayDeque<>();
//正在执行队列
private final Deque<AsyncCall> runningAsyncCalls = new ArrayDeque<>();

每当有新的请求到dispatcher管理类中(通过call.enqueue()方法)，dispatcher会通过判断runningAsyncCalls队列数目是否在最大请求数限制内和相同主机最大请求数两个条件
如果满足就会
runningAsyncCalls.add(call);  //添加到异步队列
executorService().execute(call); //开启线程池执行
如果不满足
readyAsyncCalls.add(call);  //如果当前请求数目大于64 或者host数目大于5


同步的维护：
直接将请求添加到runningSyncCalls集合当中
