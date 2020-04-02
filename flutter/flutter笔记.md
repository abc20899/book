### 环境安装
1. dart安装: <br>
   https://dart.dev/get-dart

2. flutter安装: <br>
   1) 直接下载 <br>
https://storage.googleapis.com/flutter_infra/releases/stable/macos/flutter_macos_v1.2.1-stable.zip <br>
   2) git安装 <br>
  https://flutter.dev/community/china <br>

	```
	git clone -b master https://github.com/flutter/flutter.git
	flutter upgrade
   ```

3. flutter文档 <br>
[官网文档](https://flutter.cn/docs/get-started/)

4. Flutter切换发布渠道 
https://flutter.cn/docs/development/tools/sdk/upgrading <br>
Flutter 有 4个发布渠道，分别是 stable, beta, dev, 和 master。 <br>
推荐使用 stable <br>
如果在第二步卡主可以在flutter根目录下执行  <br>

	```
	git checkout stable
	flutter channel
	flutter channel stable
	flutter upgrade
	
	export PUB_HOSTED_URL=https://pub.flutter-io.cn
   export FLUTTER_STORAGE_BASE_URL=https://storage.flutter-io.cn
git clone -b dev https://github.com/flutter/flutter.git
export PATH="$PWD/flutter/bin:$PATH"
	```
5. 常用命令

  ```
   cd ./flutter
	flutter doctor
	flutter help
	flutter devices
	flutter run
	flutter format <filename>
	flutter build apk
	flutter install
	flutter analyze  #分析错误
	flutter doctor -v
  
  ```


### web开发
克隆Flutter Web代码仓库 <br>

```
git clone https://github.com/flutter/flutter_web.git
cd flutter_web/examples/hello_world
flutter pub get
webdev serve
使用浏览器打开http://localhost:8080
webdev serve --hostname 0.0.0.0

https://github.com/flutter/flutter_web
要安装webdev软件包（为Flutter for web提供构建工具）
flutter pub global activate webdev
flutter pub upgrade
webdev serve
```

### 使用终端代理

```
export http_proxy=http://127.0.0.1:54660
export https_proxy=http://127.0.0.1:54660
```


### 学习资源

```
http://www.devio.org/2018/09/09/awesome-flutter/
https://itsallwidgets.com/
https://book.flutterchina.club/chapter8/listener.html
```

### ios设置 真机运行
#### 模拟器

```
xcrun simctl list 列设备
xcrun simctl boot "simctl列表中的模拟器名"
在flutter项目中执行  open ios/Runner.xcworkspace  打开功能
flutter run

```
#### 真机  

```
https://flutter.dev/docs/get-started/install/macos
flutter doctor
1、open ios/Runner.xcworkspace 打开xocode工程
2、Select the 'Runner' project in the navigator then the 'Runner' target
in the project settings
3、In the 'General' tab, make sure a 'Development Team' is selected
在flutter工程下 右键工程open ios module in xcode

CocoaPods 1.7.4 is available.
To update use: `sudo gem install cocoapods`
```

### 插件开发

```
1、flutter create --template=plugin wechat
- android // Android 相关原生代码目录
- ios // ios 相关原生代码目录
- lib // Dart 代码目录
- example // 一个完整的调用了我们正在开发的插件的 Flutter App
- pubspec.yaml // 项目配置文件

example/lib/main.dart:

VideoPlayerPlugin:
注册插件
public static void registerWith(Registrar registrar) {
    final MethodChannel channel = new MethodChannel(registrar.messenger(), "video_player");
    channel.setMethodCallHandler(new VideoPlayerPlugin());
  }
@Override
  public void onMethodCall(MethodCall call, Result result) {
    if (call.method.equals("getPlatformVersion")) {
      result.success("Android " + android.os.Build.VERSION.RELEASE);
    } else {
      result.notImplemented();
    }
  }  
dart 中的 getPlatformVersion 通过 _channel.invokeMethod 发起一次请求，然后，Java 代码中的 onMethodCall 方法回被调用，该方法有两个参数：
MethodCall call：请求本身
Result result：结果处理方法
```


### Flutter UI系统原理：

虽然Dart是先调用了OpenGL，OpenGL才会调用操作系统API，但是这仍然是原生渲染，因为OpenGL只是操作系统API的一个封装库，它并不像WebView渲染那样需要JavaScript运行环境和CSS渲染器，所以不会有性能损失。
对应用开发者定义的开发标准:
组合和响应式 我们要开发一个UI界面，需要通过组合其它Widget来实现，Flutter中，一切都是Widget，当UI要发生变化时，我们不去直接修改
DOM，而是通过更新状态，让Flutter UI系统来根据新的状态来重新构建UI。

Element
最终的UI树其实是由一个个独立的Element节点构成。我们也知道了组件最终的Layout、渲染都是通过RenderObject来完成的，从创建到渲染的大体流程是：根据Widget生成Element，然后创建相应的RenderObject并关联到Element.renderObject属性上，最后再通过RenderObject来完成布局排列和绘制。



### 常用库

```
dependencies:
  json_annotation: ^2.0.0  #json序列化库
  dio: ^2.1.7 #网络库
dev_dependencies:
  build_runner: ^1.0.0       #https://github.com/dart-lang/json_serializable
  json_serializable: ^3.0.0  #json序列化库 #flutter packages pub run build_runner build

```

### 学习

```
https://book.flutterchina.club/
https://rodydavisjr.com/2019/03/12/making-a-piano/
https://github.com/AppleEducate/flutter_piano

https://github.com/CarGuo/GSYFlutterBook  https://guoshuyu.cn/home/wx/Flutter-1.html
https://github.com/CarGuo/GSYGithubAppFlutter

https://github.com/brianegan/flutter_architecture_samples
```


### advanced-flutter-project
https://steemit.com/utopian-io/@tensor/advanced-flutter-project---best-practices---generic-bloc-providers---part-three






