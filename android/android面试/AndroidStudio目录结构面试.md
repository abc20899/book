Android中，一个project可以有多个module，每个module都可以写自己另外的逻辑。

Android Studio的目录结构及其功能：

.gradle目录：里面包含了gradle编译后生成的脚本。

.idea目录：包含了Android Studio工具所必要的配置文件。

app目录：包含Java代码和布局文件等安卓的文件。

app里的build目录：生成module编译好后生成的文件。

app里的libs目录：包含第三方jar包或者aar文件。

app里的src目录：包含了Java代码和或布局配置文件等。

app里的build.gradle文件：模块相关的gradle配置文件。

build目录：包含了执行module或project编译好后所生成的文件，包括apk、jar文件等等。

gradle目录：对gradle进行了封装。

.gitignore文件：有关git的配置文件。

build.gradle文件：整个项目的gradle基础配置文件。

gradle.properties文件：全局gradle配置文件。

gradlew文件：Linux下的可执行文件，运行可执行gradle的一些操作。

gradlew.bat：Window下的可执行文件。

local.properties文件：用来设置本地属性。

setting.gradle文件：设置相关的gradle配置文件。
