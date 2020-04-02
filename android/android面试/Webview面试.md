### 一、Webview常见的一些坑

#### 1.Android API level 16以及之前的版本存在远程代码执行安全漏洞，该漏洞源于程序没有正确限制使用Webview.addJavaScriptInterface方法，远程攻击者可通过反射利用该漏洞执行任意Java对象的方法。

#### 2.当Webview是在代码中动态添加的，比如添加在LinearLayout中，在onDestroy()方法中，需先将Webview从LinearLayout中移除掉，不然会造成内存泄漏。

#### 3.jsbridge：通过JavaScript搭一座桥，可以通过本地native代码可以调用远端JS的代码，同时也可以让远端JS的代码调用本地native的代码。

#### 4.webviewClient.onPageFinished是判断网页又没有加载完成时调用的，当网页没有加载完成时就跳转页面，该方法将会调用无数次。建议使用WebChromeClient.onProgressChanged方法。

#### 5.后台耗电，开启webview之后会自动开启后台线程，如果没有很好将webview销毁的话，这些线程将会一直运行。

#### 6.webview硬件加速导致页面渲染问题，容易出现页面加载白块和页面闪烁的现象，解决方法是设置暂时关闭硬件加速。

### 二、关于webview的内存泄漏问题

问题原因 ：webview会与Activity进行关联，webview执行的操作是在新的线程中进行的，Activity的生命周期和新线程的生命周期是不一样的，导致webview会一直持有Activity的引用，不能回收。

解决方法 ：

1.单独开启一个进程给webview进行操作，简单暴力，不过可能涉及到进程间通信。

2.动态添加webview，对传入的webview中使用Context的弱引用，在布局创建个ViewGroup用来放置webview，Activity创建时add进来，Activity停止时remove掉。
