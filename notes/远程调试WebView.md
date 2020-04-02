使用 Chrome 开发者工具在您的原生 Android 应用中调试 WebView。
在 Android 4.4 (KitKat) 或更高版本中，使用 DevTools 可以在原生 Android 应用中调试 WebView 内容。

在您的原生 Android 应用中启用 WebView 调试；在 Chrome DevTools 中调试 WebView。
通过 chrome://inspect 访问已启用调试的 WebView 列表。
调试 WebView 与通过远程调试调试网页相同。

#### 配置 WebViews 进行调试
必须从您的应用中启用 WebView 调试。要启用 WebView 调试，请在 WebView 类上调用静态方法 setWebContentsDebuggingEnabled。

```
if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.KITKAT) {
    WebView.setWebContentsDebuggingEnabled(true);
}
```
此设置适用于应用的所有 WebView。

#### 在 DevTools 中打开 WebView
chrome://inspect 页面将显示您的设备上已启用调试的 WebView 列表。

要开始调试，请点击您想要调试的 WebView 下方的 inspect。像使用远程浏览器标签一样使用 DevTools。
与 WebView 一起列示的灰色图形表示 WebView 的大小和相对于设备屏幕的位置。如果您的 WebView 已设置标题，标题也会一起显示。




