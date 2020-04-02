### 在mac下设置环境变量
1. 打开 应用程序 -> 实用工具 -> 终端； 
2. 在终端中定位到自己用户的主目录，输入： cd ~ ； 
3. 创建一个空文件，输入：touch .bash_profile ； 
4. 编辑这个文件，输入：open .bash_profile ； 
5. 在这个文件中输入：export PATH=${PATH}:<文件目录> ；（将"<文件目录>"替换成自己想要的目录）export PATH=${PATH}:/Users/rye/android/android-sdk-mac_x86/tools; 
6. 如果需要添加其他的环境变量例如JAVA_HOME，可以输入：export JAVA_HOME=/Library/Java/Home ； 
7. source .bash_profile重启终端，测试。

### xcode 命令行工具
### macOS 缺失的软件包管理器 brew
https://brew.sh/index_zh-cn.html
```
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```
### python 
### nodejs
### git
### jdk
### wget
### ffmpeg 多媒体处理
### sdl
### cocos2dx 游戏引擎
### vcl
### Charles 抓包
### dash https://kapeli.com/dash
### sublime text
### MacDown
### PlistEdit Pro
### iTerm2
http://www.tuicool.com/articles/FFN7Vbq
iTerm2 是一个终端模拟器，官方网站： http://www.iterm2.com/
更改配色方案为 Solarized
Solarized 的主页： http://ethanschoonover.com/solarized
快捷键呼出 
Preferences - Keys - Hotkey - Hotkey toggles a dedicated window with profile 
把它设置成 Hotkey Window，按快捷键之后 Hotkey Window 会从屏幕上面折叠下来




