http://www.runoob.com/linux/linux-shell-io-redirections.html <br>

### 将命令输出到变量
```
OUTPUT=$(nginx -V 2>&1)
echo $OUTPUT | grep conf
```

文件标识符是一个数字，不同数字代表不同的含义，默认情况下，系统占用了3个，分别是0标准输入（stdin）,1标准输出(stdout), 2标准错误(stderr), 另外3-9是保留的标识符，可以把这些标识符指定成标准输入，输出或者错误作为临时连接。通常这样可以解决很多复杂的重定向请求。

### 列出/dev目录下的所有文件

```
ls /dev   

# 会把命令的标准输出重新定向到一个文件filename,而不是显示到屏幕上，如果不指明文件标识符，系统默认的就是1, 因此1可以省略
ls /dev 1>filename.txt

#把输出追加到filename文件的末尾
ls /dev >>filename.txt

#把标准错误重新定向到文件 
#显然 -qw是一个错误参数，通常会在显示器上报告一个错误信息，但由于把2标准错误（stderr）重新定向到了文件filename，因此显示器没有错误信息，而信息写#到了文件里面
ls -qw  /dev  2>filename

#把标准输出和错误都定向到文件 "&"在这里代表标准输出和标准错误
ls /dev &>filename
```

#### Bash Shell中命令行选项/参数处理

```
./test.sh -f config.conf -v --prefix=/home
   我们称-f为选项，它需要一个参数，即config.conf, -v 也是一个选项，但它不需要参数。
   --prefix我们称之为一个长选项，即选项本身多于一个字符，它也需要一个参数，用等号连接，当然等号不是必须的，/home可以直接写在--prefix后面，即--prefix/home,更多的限制后面具体会讲到。
在手工处理方式中，首先要知道几个变量，还是以上面的命令行为例：
    *    $0 ： ./test.sh,即命令本身，相当于C/C++中的argv[0]
    *    $1 ： -f,第一个参数.
    *    $2 ： config.conf
    *    $3, $4 ... ：类推。
    *    $#  参数的个数，不包括命令本身，上例中$#为4.
    *    $@ ：参数本身的列表，也不包括命令本身，如上例为 -f config.conf -v --prefix=/home
    *    $* ：和$@相同，但"$*" 和 "$@"(加引号)并不同，"$*"将所有的参数解释成一个字符串，而"$@"是一个参数数组。如下例所示：

for arg in "$*"
do
    echo $arg
done

for arg in "$@"
do
    echo $arg
done

```


### 字符串替换

```
url="https://valipl-vip.cp31.ott.cibntv.net/657249C8BE74671C6348E546D/03000900005C7EF065C7D9A4D899D52DDB0CEC-D949-413A-911E-0970789513E2-1-114.m3u8?ccode=0502&duration=2288&expire=18000&psid=f8638b26e7543c6f88bef7d97fede9de&ups_client_netip=d20c3069&ups_ts=1553050376&ups_userid=1487395092&utid=ht9vFIwvAD0CAXtxJLYjKz48&vid=XMzk1MjYwNTgxNg&vkey=A6092019c29c865018540558e45a6bb59&sm=1&operate_type=1"
bb=${url//'?'/'\?'}
cc=${bb//'&'/'\&'}
echo $cc

```






