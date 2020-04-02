### 基础开发
  vim编辑器 <br>
  c语言回顾指针 <br>
  linux/mac c语言的编译与调试 <br>
  linux/mac 常用开发工具 <br>


vim编辑器  <br>
    处理模式 命令行模式 拷贝、删除、粘贴等 i/a等键切换到编辑模式 
    编辑模式 编辑字符 esc进行切换编辑模式

 ```
 常用命令 
    创建      vim filename
    保存      :w
    关闭      :q
    关闭保存  :wq
    查看文件  cat 
    拷贝     yy拷贝一行数据  yw拷贝一个词
    粘贴     p
    删除     dd删除一行  dw删除一个词

    光标移动
     左 h 
     下 j 
     上 k 
     右 l
     调到文件头 gg
     调到文件尾 G
     行首 ^
     行尾 $
     向前 w/ 2w
     向后 b/ 2b

    查找关键字 :/关键字
    查找与替换 :%s/关键字/替换字/gc 

    vim多窗口
    :split 横向分开
    :vsplit 竖向分开
    control ww
 ```
    

### c语言

```
    #include <stdio.h>
    int main(int argc,char* argv[]){
      printf("hello world!\n");
      return 0;
    }
    编译：
    clang -g -o helloworld helloworld.c
    -g :debug调试
    -o :目标文件
    helloworld 可执行程序
    ./helloworld

    数据类型
    short 16位 2个字节
    int    4个字节  32位
    long   4个字节  32位
    float  4个字节  32位
    double 4个字节  32位
    char   1个字节  8位
    void   指针使用 void* 代表指针

    常量与变量
    int a = 0; //变量 可以赋值
    const int b = 3.14 //不能改变

    指针
    指针就是内存地址: void*、char*
    数组 一块连续的同一类型的空间
    char c[2]  
    int arr[10]
    数组的地址只有一个
    指针本身运算：
    栈空间：系统自动回收释放  
    堆空间：程序员控制
    内存映射
    内存的分配  void* mem = malloc(size); //堆空间分配
    内存释放    free(mem) 
    内存泄漏    不断申请内存，也不释放
    野指针      占用别的内存
    函数指针    返回值类型(*指针变量名)([形参列表])
    int func(int x); //函数 
    int (*f)(int x); //函数指针
    f = func;  将func函数的首地址赋给指针f

    结构体
    struct st{
      int a; 
      int b;
    };
    struct st sst;
    sst.a = 10;

    枚举
    enum em{
       red_color=0,
       green_color,
       blue_color
    };

    enum em et;
    et = red_color;

    算数运算与比较运算
    +、-、*、/、%
    > == < >= <= !=
    if else

    循环语句
    for(int i = 0;i<100;i++){

    }
    while(a>b){
    }
    do{
    }while()
    while(1){} 1永远为真

    函数
    void func(int a){}
    int func(int a){
        return a+b;
    }

    文件操作
    FILE* file;
    打开文件 FILE* fopen(path,mode);
    关闭文件 fclose(FILE*);
    a+ 追加模式



    编译器  GCC/CLANG

    gcc/clang -g -O2 -o test test.c -I... -L... -l

    -c: 编译生成链接库
    -g: 输出文件中的调试信息
    -O: 对输出文件做指令优化
    -o: 输出执行文件名
    -I: 指定头文件
    -L: 指定库文件位置
    -l: 指定具体使用哪个库

    编译过程
    预编译
    编译
    链接，动态链接/静态链接

    add.h  对add.c的声明
    add.c  没有main函数 
    clang -g -c add.c  生成add.o 链接库
    libtool -static -o libmylib.a add.o  生成libmylib.a库
    编译 testlib.c
    clang -g -o testlib testlib.c -I . -L . -lmylib
    .表示本目录

    add.h:
      int add(int x,int y);
    add.c:
      int add(int x,int y){
         return (x+y);
      }
    testlib.c:
      #include <stdio.h>
      #include "add.h"
      int main(int argc,char* agrv[]){
         printf("add is %d",add(3,3));
         return 0;
      }


调试器  gdb lldb
  原理
   -g 参数
   指令地址、对应源代码的行号
   指令完成后，回调

  设置断点  b   b main main函数设置断点
  运行程序  r
  单步执行  n
  跳入函数  s
  挑出函数  finish
  打印内容  p

  lldb testlib  开启调试
  break list 查看断点
  l 查看源码
  r 运行代码
  s 跳入函数
  p x 打印x变量的值
  c 继续执行程序
  q 退出调试

  testlib.dSYM/Contents/Resources/DWARF/testlib
  dwarfdump testlib 
```





















