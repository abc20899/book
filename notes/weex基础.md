### 安装依赖
```
brew install node
$ node -v
v6.3.1
$ npm -v
3.10.3
```
通常，安装了 Node.js 环境，npm 包管理工具也随之安装了。因此，直接使用 npm 来安装 weex-toolkit。
npm 是一个 JavaScript 包管理工具，它可以让开发者轻松共享和重用代码。Weex 很多依赖来自社区，同样，Weex 也将很多工具发布到社区方便开发者使用。
注意: weex-toolkit 在 1.0.1 之后才支持初始化 Vue 项目，使用前请确认版本是否正确。

```
npm install -g weex-toolkit
weex -v
```

<!--more-->

### 初始化
```
weex init awesome-project
```
在 awesome-project 目录中就创建了一个使用 Weex 和 Vue 的模板项目

### 开发
进入项目所在路径，weex-toolkit 已经为我们生成了标准项目结构。
在 package.json 中，已经配置好了几个常用的 npm script，分别是：
build: 源码打包，生成 JS Bundle
dev: webpack watch 模式，方便开发
serve: 开启静态服务器
debug: 调试模式

通过 npm install 安装项目依赖。之后运行 npm run dev 和 npm run serve 开启watch 模式和静态服务器。

然后我们打开浏览器，进入 http://localhost:8080/index.html 即可看到 weex h5 页面。

vue 官网 https://cn.vuejs.org/
weex 官网 https://weex.apache.org/cn/

### Android 集成有两种方式
源码依赖：能够快速使用WEEX最新功能，可以根据自己项目的特性进行相关改进。
SDK依赖：WEEX 会在jcenter 定期发布稳定版本。jcenter

### Vue in Weex
Vue.js 是 Evan You 开发的渐进式 JavaScript 框架，在易用性、灵活性和性能等方面都非常优秀。开发者能够通过撰写 *.vue 文件，基于 
```
<template>, <style>,<script> 快速构建组件化的 web 应用。
```

### 整体结构设计
* 页面：首先移动应用应该可以被拆解成若干个页面，每个页面相对解耦独立，同时每个页面都有一个 URL 进行唯一标识。
* 路由：这些页面将会通过路由机制有机的串联起来，页面之间的关系是通过路由来进行调度的。常见的移动应用路由包括导航栏、tab 切换等。
* 设备能力：以各种 API 或服务的方式提供出来，供页面自由使用。
这样的话，在构建一个完整的移动应用之前，先确定你的应用有多少页面，每个页面分别是什么 URL，页面之间的关联和跳转逻辑是怎样的，然后梳理整个移动应用需要的所有 API 和服务。
然后通过 Weex 创建不同的页面，并分别进行开发、调试和发布。

### Weex 页面结构
一个 Weex 页面就是一个相对独立解耦的移动应用界面，它不仅包括了界面展示、更包含了逻辑处理、设备能力使用、生命周期管理等部分。

#### DOM 模型
Weex 页面通过类似 HTML DOM 的方式管理界面，首先页面会被分解为一个 DOM 树，，每个 DOM 结点都代表了一个相对独立的 native 视图的单元。然后不同的视图单元之间通过树形结构组合在了一起，构成一个完整的页面。
https://weex.apache.org/cn/references/native-dom-api.html

#### 组件
Weex 支持文字、图片、视频等内容型组件，也支持 div、list、scroller 等容器型组件，还包括 slider、input、textarea、switch 等多种特殊的组件。Weex 的界面就是由这些组件以 DOM 树的方式构建出来的。
https://weex.apache.org/cn/references/components/index.html

#### 布局系统
Weex 页面中的组件会按照一定的布局规范来进行排布，我们这里提供了 CSS 中的盒模型、flexbox 和 绝对/相对/固定/吸附布局这三大块布局模型。
* 盒模型：通过宽、高、边框、内外边距、边框等 CSS 属性描述一个组件本身的尺寸。
* flexbox：通过 CSS 3 Flexbox 布局规范定义和描述组件之间的空间分布情况。
* position：支持 CSS position 属性中的 absolute, relative, fixed, sticky 位置类型，其中 relative 是默认值。

#### 功能
Weex 提供了非常丰富的系统功能 API，包括弹出存储、网络、导航、弹对话框和 toast 等，开发者可以在 Weex 页面通过获取一个 native module 的方式引入并调用这些客户端功能 API。
https://weex.apache.org/cn/references/modules/index.html

#### 生命周期
每个 Weex页面都有其自身的生命周期，页面从开始被创建到最后被销毁，会经历到整个过程。这是通过对 Weex 页面的创建和销毁，在路由中通过 SDK 自行定义并实现的。

### 使用 weex-toolkit
* 实时预览
```
weex src/foo.vue
weex src --entry src/foo.vue #预览整个项目 传入的参数指定预览的目录和入口文件。
```
* 打包weex项目
如果开发完成后，你可以使用 weex compile 通过命令行工具进行单个文件或者整个项目的打包。
命令行需要两个参数，你的源码文件或者目录， 以及你生成打包后的目录地址。
```
weex compile src/foo.vue dist
```

### 调试 Weex 页面
单纯启动一个调试服务器，并同时唤起Chrome浏览器打开调试主页。
```
weex debug
weex debug your_weex.vue
weex debug your/we/path  -e index.we     # -e 表示入口文件
```
接入文档 https://weex.apache.org/cn/references/advanced/integrate-devtool-to-android.html

### weex platform 以及 run 命令
weexpack 是基于 Weex 快速搭建应用原型的利器。它能够帮助开发者通过命令行创建 Weex 工程，添加相应平台的 Weex app 模版，并基于模版从本地，GitHub 或者 Weex 应用市场安装插件，快速打包 Weex 应用并安装到手机运行，对于具有分享精神的开发者而言还能够创建 Weex 插件模版并发布插件到 Weex 应用市场。
如果我们希望在模拟器或者真机上查看 Weex 运行的效果，我们可以使用 platform 添加或者删除 Weex 应用模板。
weex platform add ios

### weex plugin 命令
```
weex plugin add plugin_name
weex plugin add weex-chart
weex plugin remove weex-chart
```

### 用weexpack运行demo(Android／iOS／H5)
1. 安装weexpack
```
npm install -g weexpack
```
2. 创建工程，如MyApp
```
weexpack create MyApp
```
3. 创建运行平台
```
cd MyApp & weexpack platform add ios (/android)
```
4. 添加地图插件，有两种方式
－从插件市场下载安装： 
```
weexpack plugin add weex-amap
```
－地图插件代码clone到本地后安装， 
```
weexpack plugin add /users/abcd/Code/weex-plugins/weex-amap (
    这后面是地图插件本地代码的目录)
```
5. 编译和运行demo
把demo文件（所有在目录plugins/weex-amap/demos/下的文件）拷贝到项目工程MyApp/src下，然后：
对H5用如下命令：
```
weexpack build web & weexpack run web
```
对安卓和iOS用命令：
```
weexpack run ios (/android) #可在模拟器或者device上运行
```

































