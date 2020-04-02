---
title: python基础2
date: 2018-02-10 15:18:49
tags: python
categories: python
---

### python基础2
#### 变量
用简单简介的英文单词来标识一个变量，由字母、数字、下划线组成，变量首字母不能为数字，系统关键字不能用在变量中。变量没有类型限制。

```
a = 1
b = a
a = 3
print(b)
>> 1                     # int 值类型

a = [1,2,3,4,5]
b = a
a[0] = '1'
print(b)
>> ['1', 2, 3, 4, 5]     #list 引用类型
```
**int、str、tuple 值类型，不可变** 

**list、set、dict 引用类型，可变**

<!--more-->

```
a = 'hello'
print(id(a))              #4514374688 打印a的内存地址
a = a + ' python'         #一个新的字符串
print(a)  
print(id(a))              #4513862576 打印a的内存地址

#列表
aa = [1,2,3]
print(hex(id(aa)))        # 0x10985e388
bb = aa 
print(hex(id(bb)))        # 0x10985e388

#元组 不能修改,不可改变
c = (1,2,3)
print(c)

cc = (1,2,3,['a','b','c'])
print(cc[-1][2])
>> c
cca = (1,2,3,[1,2,['a','b']])
print(cca[-1][2][1])
>> b
cca[-1][2][1] = 'xx'   #修改元组中 列表中的元素
print(cca[-1][2][1])
>> xx
```

#### 运算符

算术运算符 `+ - * / % ** //`
赋值运算符 `= += *= **= /= //= %= -=`
比较运算符 `==  != > < >= <=`
逻辑运算符 `and or not`
位运算符   `& | ^ ~ << >>`
成员运算符 `in   not in`
身份运算符 `is  is not`

```
print(1+2)
print(2**5)   #乘方  32
print(5%2)
print(4//3)
print(4/3)

sum = 2+4
print(sum)
a,b = 2,3
b += a
print(b)

c = 1
c+=c>=1    #c += True
print(c)   #c = 1 + 1
>> 2

print('a'>'b')  #比较asc码
ord(a)  # 97
ord(b)  # 98
print('abc'<'abd')  #单独每个字母比较 'a'<'a' 'b'<'b' 'c'<'d'
>> Ture
print([1,2,3]<[2,3,4])
>> Ture
print((1,2,3)<(1,3,2))
>> True

eq1 = 4>3
eq2 = 5>6
print(eq1 and eq2)
>> False
print(eq1 or eq2)
>> True
print(not False)
>> True
print('a' and 'b')
>> b
print('a' or 'b')
>> a
print([1] or [])
>> [1]             #非空列表为True
print(1 and 2)
>> 2               #非0为True
```
**in float 0 认为是False，非0认为True**
**字符串 空字符串认为是False，非空字符串认为True**
**集合、元组()、字典{}、列表[] 空为False，非空认为True**

##### in   not in

```
a = 1
arr = [1,2,3,4,5]
print(a in arr)
>> True

c = 'hello'
print('w' not in c)
>> True

t = (1,2,3)       # 列表 集合 same
print(4 in t)
>> False

d = {'c':1}       #字典判断的是key
print(1 in d)
>> False
print('c' in d)
>> True
```

##### is is not  比较内存地址

```
a = '123'
b = 123
print(a is b)
>> False

a = 1
b = 1.0
print(a is b)
>> False

a = 1
b = 1
print(a is b)
>> True

str1 = 'abc'
str2 = 'abc'
print(str1 is str2)
>> True

a = {1,2,3}
b = {2,1,3}
print(a == b)      #集合无序，比较元素
>> True
print(a is b)      #内存地址不一样
>> False

t1 = (1,2,3)
t2 = (2,1,3)
print(t1 == t2)    #元组属于序列是有序
>> False
print(t1 is t2)    #内存地址不一样
>> False

a = 1
print(type(a) == int)  #判断类型 不推荐
>> True
eq = isinstance(a,str)
print(eq)
>> False

tt = 'hello'
eq = isinstance(tt,(int,str,float))
print(eq)
>> True
```
**对象的三个特征 id、value、type**
**对应的判断 is、==、isinstance()**

##### 位运算符  转换为二进制进行计算

```
a = 2      #bin(a)  0b10   
b = 3      #bin(b)  0b11
print(a&b) # 10 11 按位与 得到 10    0b10 = 2
>> 2

print(a|b)  # 10 11 按位或有1取1  得到11    0b11 = 3
>> 3
```
#### 流程控制
* if else
  
  ```
  a = 11
  b = int(0b1011)
  if a >= b:
     print('yes')
  else:
     print('no')     
  >> yes
  
  t = (1,2,'b','b')
  if 2 in t:
     print('2')
  else:   
     print('0')
  >> 2
  
  print('please input your name')
  account_list = ('john','lisa','june')
  user_name = input()
  print('please input your password')
  user_passwd = input()
  if user_name in account_list:
	 if user_passwd == '123456':
	    print('welcome')
	 else:
	    print('password is wrong')
  else:
	 print('sorry')   
  ```
* while
 
  ```
  counter = 1
  while counter <= 10:
      counter+=1
      print(counter)
  else:
     pass    
  ```
* for

  ```
  # 遍历循环序列或者集合、字典
  t = (1,2,3,4,5)
  for a in t:
    print(a)
  
  a = [['a','b','c','d'],(1,2,3)]
  for x in a:
      for y in x:
        print(y)
  else:          #遍历到最后执行
    pass   
  
  tt = [1,2,3]
  for c in tt:
      if c == 2:
        continue    #跳过此条件的执行
      print(c)      # 1 3  
      
  arr = set()
  for i in range(0,10):
     arr.add(i)
  print(arr)
  >> {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}
  
  for x in range(0,10,2):   #步长为2
      print(x,end=' | ')
  >> 0 | 2 | 4 | 6 | 8 |     
  for x in range(10,0,-2):  #步长为-2
      print(x,end=' | ')
  >> 10 | 8 | 6 | 4 | 2 |
  
  a = [1,2,3,4,5,6,7,8,9]    
  b = a[0:len(a):2]    # 步长为2
  print(b)  
  >> [1, 3, 5, 7, 9]
  ```
  
##### pass语句 空语句、占位语句

	```
	if a > b:
	  pass
	```
#### 函数
项目组织结构:包、模块、类、函数和变量

文件夹下有__init__.py文件的称为一个python package
__init__.py文件中：

```
# 批量导入功能
import os
import sys

#定义可以导入的模块
__all__ = []  
```

```
 import xx.xx.Mid
 mid = Mid.create()
 
 import xx.xx.x.MySql as sql
 sql.insert()
 
 from xx.xx import Image
 img = Image(path)
 
 from xx.xx import *
```

```
a = 1.22345
print(round(a,2))   #四舍五入
>> 1.22
>> help(round)      #终端中输入 可以查看函数介绍 :q 退出
>> import this


def add(x,y):
  return x+y
print(add(3,4)）
>> 7

#返回多个值
def result(x,y):
    a = x*3
    b = y*2+10
    return a,b

su = result(2,3)
print(su)
>> (6, 16)
#序列解包
a,b = result(2,3) 

a,b,c = 1,2,3
d = 1,2,3
print(type(d))
>> <class 'tuple'>

a=b=c=1
print(a,b,c)

#必须参数 x、y没有默认值
def need_params(x,y):
    return x+y
sum = need_params(y=1,x=2)  #关键字参数

#默认参数 y为默认参数
def default_params(x,y=1):
    return x+y
print(default_params(2))    #传一个参数即可

#可变参数 *x  一个tuple类型
def hello4(*x):
    print(x)
hello4('s',100,True) #('s', 100, True)

#关键字参数 **y 接收到的是一个字典
def hello5(**y):
    print(y)
hello5(name='june',age=29)

#全局变量 函数为变量赋值时，默认为本地变量赋值，屏蔽作用域外同名变量，使用golbal可以表示向一个全局变量赋值
z = 10
def hello8(x):
    global z
    z = x
    print('z='+str(z))
hello8(123)
```













