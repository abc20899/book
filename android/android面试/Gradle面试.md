在Android Studio的目录中，一个有三个gradle相关的文件，分别是：

setting.gradle ：用来配置多模块的设置。

```
include ':app'
```
build.gradle ：全局gradle配置文件。

```
buildscript {

    repositories { //仓库
        maven { url 'https://maven.google.com' }
        jcenter()
    }
    dependencies { //依赖
        classpath 'com.android.tools.build:gradle:2.3.2'

        // NOTE: Do not place your application dependencies here; they belong
        // in the individual module build.gradle files
    }
}

allprojects {
    repositories {
        maven { url 'https://maven.google.com' }
        jcenter()
    }
}
```
app目录下的build.gradle ：模块的gradle配置文件。其android中的设置可以覆盖AndroidManifest.xml中的属性。

```
apply plugin: 'com.android.application' //官方插件

android { //此处的配置可以覆盖AndroidManifest.xml中的属性
    compileSdkVersion 25 //编译版本
    buildToolsVersion "25.0.2" //构建版本
    defaultConfig {
        applicationId "linchange.example.com.waimain"
        minSdkVersion 15
        targetSdkVersion 25
        versionCode 1
        versionName "1.0"
        testInstrumentationRunner "android.support.test.runner.AndroidJUnitRunner"
    }
    buildTypes {
        release {
            minifyEnabled false
            proguardFiles getDefaultProguardFile('proguard-android.txt'), 'proguard-rules.pro'
        }
    }
}

dependencies { //项目依赖
    compile fileTree(dir: 'libs', include: ['*.jar'])
    androidTestCompile('com.android.support.test.espresso:espresso-core:2.2.2', {
        exclude group: 'com.android.support', module: 'support-annotations'
    })
    compile 'com.android.support:appcompat-v7:25.2.0'
    testCompile 'junit:junit:4.12'
    compile 'com.android.support.constraint:constraint-layout:1.0.1'
    compile 'com.android.support:design:25.2.0'
}
```