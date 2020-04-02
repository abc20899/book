### SublimeText3运行JavaScript控制台
JavaScript控制台的调试和输出在浏览器端的使用算是工作中常用了，作为前端开发主力编辑器Sublime Text本身是不支持JavaScript的输出和运行的。有的时候我们需要看一下输出的效果，不得不借助于F12查看控制台的程序。作为插件系统及其丰富的编辑器，我们可以通过添加Build System的方法来让Sublime Text支持Javascript Console控制台调试。
#### NodeJS方式
1.下载安装NodeJS  

2.启动Sublime  Text，Tools > Build System > New Build System,在BuildSytem添加以下内容:

```
{
"cmd": ["/Users/keso/.nvm/versions/node/v0.12.7/bin/node", "$file"],
"selector": "source.js"
}
```

[]里为node命令安装目录，查看node安装目录如下:

```
which node
```

获取路径如下:

```
/usr/local/bin/node
```

配置如下:

```
{
"cmd": ["/Users/keso/.nvm/versions/node/v0.12.7/bin/node", "$file"],
"selector": "source.js"
}
```
调试js代码快捷键command+b


