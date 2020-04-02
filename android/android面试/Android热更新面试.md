### 一、热更新流程

1.线上检测到严重的crash。

2.拉出bugfix分支并在分支上修复问题。

3.jenkins构建和补丁生成。

4.app通过推送或主动拉取补丁文件。

5.将bugfix代码合并到master分支上。

**热更新** ：在不关闭软件的情况下，对软件进行更新。

### 二、主流热更新框架介绍

1.Dexposed：阿里巴巴的开源框架，基于AOP的思想，包括日志记录、性能统计、安全控制、事务处理等方面。

2.AndFix：也是阿里巴巴的开源框架，唯一的功能就是热修复。

3.Nuwa：基于dex分包技术，将一个dex文件拆分成多个dex文件，在应用启动的时候，会先将一个dex作为主dex进行加载，应用启动后将逐个加载其他的dex。会逐个遍历dex文件，如果有相同的方法，前面的dex里的方法将被执行。

### 三、热更新原理

1.Android类加载机制

1）DexClassLoader：主要是加载dex、jar、apk文件等等。

2）PathClassLoader：主要是加载系统类和应用类。

2.热修复机制

1.BaseClassLoader中会创建好dexElements这个数组。

2.ClassLoader会遍历这个数组。

**原理** ：把需要修复的类打包成dex文件，把这个修复过的dex文件排在dexElements最前面，ClassLoader加载到修复过的dex文件的类之后就不会再去加载错误的类了。