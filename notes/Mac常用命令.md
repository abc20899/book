```
➜  work cd /
➜  / ls
Applications              bin                       net
Library                   cores                     private
Network                   dev                       sbin
System                    etc                       tmp
Users                     home                      usr
Volumes                   installer.failurerequests var

//常用命令
➜  / cd bin
➜  /bin ls
[          date       expr       ln         pwd        sync
bash       dd         hostname   ls         rm         tcsh
cat        df         kill       mkdir      rmdir      test
chmod      domainname ksh        mv         sh         unlink
cp         echo       launchctl  pax        sleep      wait4path
csh        ed         link       ps         stty       zsh

//更多命令
➜  bin cd /usr/bin/
➜  bin ls
****
```

把粘贴板内容直接存入一个文件：
```
$ pbpaste > out.txt
```
打开终端所在的当前目录
```
$ open .
```
查看一个文件有多少行
```
$ wc -l out.txt
```
查看文件前 100 行
```
$ head -100 out.txt
```
查看文件最后 100 行
```
$ tail -100 out.txt
```
对英文单词进行发音，挺常用的。
```
say xxx
```
当前目录下建立文件
```
touch xx 
```
用finder打开某个目录
```
open xx 
```
定时关机
```
sudo shutdown -h 23:00  //表示在23点定时关机 
```
关机命令
```
sudo shutdown -h now
```
mac启用root
```
sudo passwd root
```
重启
```
sudo reboot
```
列出当前目录的文件
```
ls /    //参数 -w 显示中文，-l 详细信息， -a 包括隐藏文件
```
切换目录
```
cd android
```
建立新目录
```
mkdir backup
```
拷贝文件
```
cp -R ~/work/123 ~/android/234   //参数R表示对目录进行递归操作
```
移动文件 
```
mv ~/work/123.txt ~/Desktop/234.txt
```
删除文件
```
rm -rf ~/work/123   //参数－rf 表示递归和强制，千万要小心使用，如果执行了 "rm -rf /" 你的系统就全没了
```
更改文件权限
```
chmod a+x ~/work/shut.sh
```




























