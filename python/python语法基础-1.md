---
title: python基础
date: 2018-02-09 21:33:38
tags: python
categories: python
---

### 语言介绍
[官网](https://www.python.org)

* 优点:
简洁、优雅、灵活、动态、面向对象
* 缺点:
相较于c、c++、java运行效率慢
* 应用:
	1. 爬虫 Scrapy
	2. AI机器学习 Tensor Flow
	3. 自动化运维、测试
	4. 大数据 Spark
	5. web开发 Flask、Django
	6. 脚本处理

### 语法基础
终端退出python:exit() 
#### 基本数据类型
* 6种标准类型:
	1. Number 数字
	2. String 字符串
	3. List  列表
	4. Tuple 元组
	5. Dictionary 字典
	6. Sets 集合
	<!--more-->
	
##### Number `<class 'int'>`
   * int     整型(其他语言short、int、long)   
   * float   浮点型 (其他语言float、double)
   * bool    0:False   非0:True
   * complex complex(x,y) x实部y虚部     
   
   ```
   #整形类型
	a = 100
	#浮点类型
	pi = 3.14
	#二进制表示0b开头
	print(0b10)  # 2
	print(0b11)  # 3
	print(0b11111111) # 255
	#八进制表示0o开头
	print(0o10)  # 8
	print(0o11)  # 9
	#十六进制表示0x开头
	print(0x1F)  #31
	#其他进制转换为二进制
	print(bin(10))  #0b1010
	print(bin(0o7)) #0b111
	print(bin(0xE)) #0b1110
	#其他进制转换为十进制
	print(int(0b111)) #7
	print(int(0o77)) #63
	print(int(0xF))  #15
	#其他进制转换为十六进制 
	print(hex(255))        #0xff
	print(hex(0b1011))     #0xb
	print(hex(0o777))      #0x1ff
	#其他进制转换为八进制
	print(oct(12))         #0o14
	print(oct(0b111))      #0o7
	print(oct(0x123))      #0o443
	
	print(a,pi)   #100 3.14
	print(1+3)    #4
	print(type(1+1.0))  #<class 'float'> 浮点类型
	print(type(1*1.0))  #<class 'float'> 浮点类型
	print(type(2/2))    #<class 'float'> /除法,自动转型浮点类型
	print(type(2//2))   #<class 'int'> //取整除法 输出整型
	
	print(bool(0))      #False
	print(bool(2))      #True
	print(bool(0b0))    #False
	print(bool(0b10))
	#不仅数字可以转换为bool类型
	print(bool('june'))          #True
	print(bool(''))              #False
	print(bool([1,2,3]))         #True
	print(bool([]))              #False
	print(bool({'name','june'})) #True
	print(bool({}))              #False
	print(bool(None))            #False
	
   #复数
   x = 1.2
   y = 2.3
   z = complex(x,y)
   print(z)         #(1.2+2.3j)  a + bj
	
	#多个变量赋值
	a = b = c = 200
	print(a,b,c)
	
	#多元赋值
	x,y,z = 100,200,'dddd'
	print(x,y,z)
	#占位符
	print('i am %s' % 'junechiu')  

   ```
   
##### String类型 `<class 'str'>`
   * 单引号  'let"s go'
   * 双引号  "let's go"
   * 三引号  
     '''ssss'''  
     """hello world"""
   * 转义字符 特殊的字符、无法看见的字符、与语言语法有冲突的字符
     'let\'s go' 
   * 占位符    'i am %s' % 'junechiu'
   * print(r'hello \n world')  加r输出原始字符串，不会被转义
   * 字符串常用方法
     
     ```
     #字符串用单引号或者双引号 用\作转义 字符数组下标操作
	  name = 'I\'m junechiu'
	  print(name)
	  print(len(name))          #输出字符串的长度
	  print(name[0])            #输出第一个字符
	  print(name[0:-1])         #输出第一个到倒数第二个
	  print(name[1:2])          #输出第1到第2个字符
	  print(name[2:])           #输出从2个位置开始以后的字符串
	  print(name*2)             #重复2次
	  print('Hello,'+name)      #拼接
	  print('june' in name)     #是否包含
	  print('june' not in name) 
	  print(name.upper())       #转换成大写
	  print(name.lower())       #转换成小写
	  print(name.capitalize())  #字符串第一个字符大写
	  print(name.isspace())     #是否包含空格
	  print(name.replace('june','hehe')) #替换操作
	  print("h*h*".split("*"))   #分割操作
	  print(name.strip())        #去掉字符串的左右空格
	  print(name.lstrip())       #去掉左空格
	  print(name.rstrip())       #去掉右空格
	  print(r'hello \n world')   #输出原始字符串
	  print(str(1234))           #转换为字符串
	  print('hello world'[6:20]) # world 
	  print('hello world'[6:]) # world
	
	  #占位符 %d %f %s
	  hehe = 'hello,%s' % 'python'
	  print(hehe)
	  aaa = 'python %d %s %.2f' % (666,'niubai',9.99)
	  print(aaa)
	
	  sss = ''' 
		ssss\n
		hahah\n
		随便写\t
		呵呵\t
     '''
     ```
   * 截取字符串  
    
    ```
 str = '0123456789'
 print(str[0:3])    #截取第一位到第三位的字符
 print(str[:])      #截取字符串的全部字符
 print(str[6:])     #截取第七个字符到结尾
 print(str[:-3])    #截取从头开始到倒数第三个字符之前
 print(str[2])      #截取第三个字符
 print(str[-1])     #截取倒数第一个字符
 print(str[::-1])   #创造一个与原字符串顺序相反的字符串
 print(str[-3:-1])  #截取倒数第三位与倒数第一位之前的字符
 print(str[-3:])    #截取倒数第三位到结尾
 print(str[:-5:-3]) #逆序截取
    ```
   * 连接字符串 +、join
    
    ```
ok_str = ','
str_arr = ['python','java','javaScript','ruby']
print(ok_str.join(str_arr))
>> python,java,javaScript,ruby
    ```
   * 分割字符串
    
    ```
str1 = 'ab,cde,fgh,ijk'
str2 = ','
str1 = str1[str1.find(str2) + 1:]
print(str1)
>> cde,fgh,ijk
#或者
s = 'ab,cde,fgh,ijk'
print(s.split(','))
>> ['ab', 'cde', 'fgh', 'ijk']
    ```
   * 查找字符串 find、index
    
    ```
 str1 = 'abcdefg'
 str2 = 'cde'
 print(str1.find(str2)) 
 >> 2
    ```
   * 翻转字符串 [::-1]
    
    ```
 str1 = 'abcdefg'
 str1 = str1[::-1]
 print(str1)
    ```
   * 比较字符串 ==、is
    
    ```
 str1 = 'strch'
 str2 = 'strch'
 print(str1 is str2)
    ```
##### List列表  `<class 'list'>`
列表中可以添加不同类型的元素
* 定义

	```
	arr = ['hehe',100,100.00,True,'$aa']
	print(arr)
	print(len(arr)) #长度
	#二维数组
	arr2 = [[1,2,3],[4,5,6],[7,8,9]]
	print(arr2)
   ```
* 常用操作方法

  ```
	#访问元素
	arr = ['hehe',1,2,3,True,10,11]
	print(arr[2])    #下标为2的元素
	print(arr[2:])   #从第2个元素开始的子列表
	print(arr[2:4])  #位置2到位置4的子列表
	
	#添加元素
	s1 = [False]
	arr = arr+s1         #连接元素
	print(arr)
	s2 = [200,44]
	arr.extend(s2)       #在列表的末尾追加一个列表
	print(arr)
	arr.append("哈哈")    #列表末尾追加一个新的对象
	print(arr)
	arr.insert(2,"插入")  #在指定位置插入一个元素
	print('拼接打印：'+str(arr))
	
	#更新元素
	arr[1] = '更新第二个元素'  #下标更新
	print('更新：'+str(arr))
	
	#删除元素
	arr.pop()         #默认删除最后一个元素
	arr.pop(1)        #删除第二个元素
	del arr[3]        #删除指定位置
	arr.remove('$aa') #删除匹配对象
	print(arr)
	
	#其他方法
	print(arr*2)      #重复两次
	arr.reverse()     #反向列表
	arr2 = arr.copy() #复制列表
	print(arr2)
	arr2.clear()      #清空列表
	print(arr2)
  ```
  
##### Tuple 元组  `<class 'tuple'>`
用()包含元素 元素不能被修改 可以包含一个list类型的元素
  
  ```
arrInner = [100,22,'ddd']
array = (100,100.00,'arr',True,'$$%^',arrInner)
print(array)  
>>(100, 100.0, 'arr', True, '$$%^', [100, 22, 'ddd'])
print(array[2:])
array2 = (1,False) 
print(array+array2) 
>>(100, 100.0, 'arr', True, '$$%^', [100, 22, 'ddd'], 1, False)
print(type((1)))    #元组中只有一个元素 此时()表示数学运算符
>> <class 'int'>
print(type(('hello')))
>> <class 'str'>
#表示只有一个元素的元组
arr = (1,)
print(type(arr))
#空元组
arr_empty = ()
print(type(arr_empty))
  ```

**str、list、tuple 都为序列，每个元素都有一个序号，有序**

```
  #切片操作 可以进行 + * 运算
  print([1,2,3,4,5][0:3])
  print([1,2,3,4,5][-1:])
  print("hello world"[0:8:2])
  >> hlow
  b = 3 in [1,2,3,4,5]      #是否在列表中
  print(b)
  b = 10 not in [1,2,3,4,5] 
  len_num = len([1,2,3,4,5,6])  #长度
  print(len_num)
  max_int = max([1,2,3,4,5,6,8]) #最大值
  print(max_int)
  min_int = min((1,2,3,4,5))
  print(min_int)
  max_char = max('hello world')
  print(max_char) 
  min_char = min('hello world')
  print(min_char)  #空格最前 asc码顺序
  num = ord('w')   #asc码 
  print(num)
  >> 119
  print(ord(' '))
  >> 32
```

##### 集合 set 无序,不重复 `<class 'set'>`
* 定义
  
  ```
  set = {1,2,3,4,5}
  print(type(set))
  set2 = {1,1,2,2,3,4,5,5}
  print(set2)
  >> {1, 2, 3, 4, 5}
  set_empty = set()  #定义一个空的集合
  print(set_empty)
  print(type(set()))
  ```
  
* 操作 add、len、in、not in
  
  ```
  set = {1,2,3}
  print(len(set))
  b = 1 in set
  print(b)
  set_all = {1,2,3,4,5,6}
  set_1 = {2,3}
  set_2 = set_all - set_1   #两个集合的差集
  print(set_2)
  >> {1, 4, 5, 6}
  set_3 = {4,5}
  set_result = set_all & set_3  #两个集合的交集
  print(set_result)
  >> {4, 5}
  set_00 = {1,2,3,4,5}
  set_11 = {1,3,4,8,9}
  set_22 = set_00 | set_11     #合并两个集合并且元素不重复
  print(set_22)
  >> {1, 2, 3, 4, 5, 8, 9}
  set_lan = set()            #定义一个集合
  set_lan.add('python')      #添加元素
  set_lan.add('java')
  set_lan.add('c++')
  print(set_lan)
  >> {'java', 'c++', 'python'}
  ```
  
##### Dictionary 字典 key-value`<class 'dict'>`
* 定义
  
  ```
dic_person = {'name':'junechiu','age':28}
print(dic_person)
>> {'name': 'junechiu', 'age': 28}
handle = {'W':'前','A':'左','D':'右','S':'后'}
print(handle['W'])    #根据key取值
handle['W'] = '向前'   #修改元素
print(handle)
#删除元素 pop('id')
#清空元素 clear
#用dict()方法创建一个字典
d = dict(id=10010,des='i am junechiu',job='coder')
print(d)
print(d.keys())     #输出所有key
print(d.values())   #输出所有value
dict_empty = {}     #创建一个空字典
  ```
  
* value取值类型: str、int、float、list、set、dict
* key取值类型: 不可变的类型 int、str、()元组

##### 数据类型转换
* python 空值用 None 来表示

```
#数据类型转换 内置一些函数
x = '22'
cc = int(x)     #转换为int
print(cc)
cc = float(x)   #转换为float
print(cc)
cc = str(x)     #转换为str
print(cc)
cc = list(x)    #转换为一个列表
print(cc)       #['2', '2']
```

   
    
    