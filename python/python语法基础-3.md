---
title: python基础3
date: 2018-02-10 19:57:19
tags: python
categories: python
---

### python面向对象
#### 定义类 
最基本的作用：封装、模板

```
# class 类名(父类):
#单下划线 protected 保护类型 只允许本类和子类访问  不能用于 from module import*
class Student():
   name = ''      #类变量
   age = 0        #类变量
   score_dic = {}
   __sex =''  #__两个下划线表示私有属性，私有方法也是如此，不能被外部类所访问
   
   #构造函数 实例化时自动调用 不能返回除None外的值
   def __init__(self,name,age,score_dic):
      self.name = name        #实例变量
      self.age = age
      self. score_dic = score_dic
   
   def getSex(self):
      return self.__sex

   def setSex(self,sex):
      self.__sex = sex
   
   #实例方法     
   def info(self):
      print(self.name +' '+ str(self.age) + 'score:' + str(self.score_dic))    
```
<!--more-->
#### 实例化

```
stu = Student('小明',12,{'Math':99})
stu.info()       #调用方法
print(type(stu))
print(stu.name)       #访问属性
print(stu.__dict__)   #打印对象字典
>> {'name': '小明', 'age': 12, 'score_dic': {'Math': 99}}
print(Student.__dict__)   #打印类字典

#寻找属性 对象-->实例--->父类
```

#### 类变量、类方法、静态方法

```
class Person(object):
    sum = 0  # 类变量

    def __init__(self):
        self.__class__.sum += 1  # 调用类变量
        print('Person: sum' + str(self.__class__.sum))

    # 定义一个类方法
    @classmethod  # 装饰器
    def print_sum(cls):
        print('sum:' + str(cls.sum))
    
    #定义一个静态方法 不需要传 self和cls
    @staticmethod
    def add():
        print('static：'+str(Person.sum))  #访问类变量

p1 = Person()
p2 = Person()
p3 = Person()
>> Person: sum1
>> Person: sum2
>> Person: sum3
Person.print_sum()  #调用类方法
>> sum:3
Person.add()        #调用静态方法

#静态方法和类方法不能访问实例变量
```

#### 继承

```
# C继承B，B继承A
class A(object):
    a = ''
    def __init__(self,a):
        self.a = a
        print('a'+str(a))

class B(A):
    b = ''
    def __init__(self,a,b):
        super(B,self).__init__(a) #调用父类的1个参数的构造函数
        self.b = b  #子类自己的属性

class C(B):
    c = ''
    def __init__(self,a,b,c):
        super(C,self).__init__(a,b) #调用父类的2个参数的构造函数
        self.c = c #子类自己的属性


#D 继承A、B、C
class A(object):
    a = ''
    def __init__(self,a):
        self.a = a

class B(A):
    b = ''
    def __init__(self,a,b):
        super(B,self).__init__(a)
        self.b = b

class C(object): #单独继承 object类
    c = ''
    def __init__(self,c):
        self.c = c

class D(B,C):
    d = ''
    def __init__(self,a,b,c,d):
        super(D,self).__init__(a,b) #继承B 与父类参数相同
        C.__init__(self,c)   #继承C C类参数相同
        self.d = d  #自己属性
        
#单继承  super函数 父类必须继承object类
class Persion(object):
    name = ''
    age = 0
    __sex = '' #私有变量

    #构造函数
    def __init__(self,name,age,sex):
        self.name = name
        self.age = age
        self.__sex = sex
    #函数
    def set_sex(self,sex):
        self.__sex = sex

    def get_sex(self):
        return self.__sex

#单继承
class Student(Persion): #继承Persion
    persion_id = 0  #子类属性

    #定义构造方法
    def __init__(self,name,age,sex,persion_id):
        # 调用父类的构造方法
       # Persion.__init__(self,name,age,sex)
       super(Student,self).__init__(name,age,sex) #调用父类的init
       self.persion_id = persion_id

    #重写父类的方法
    def set_sex(self,sex):
        self.__sex = sex

    def get_sex(self):
        return self.__sex


if __name__ == '__main__':
      # 单继承
   student = Student('june',29,'男',10010)
   print(student.age)                
```

#### 捕获异常

```
try:
    name = '128s'
    print(int(name))
except ValueError as e: #异常基类BaseException
    print(e)
finally:
    print('finally')
```

#### 正则表达式
特殊的字符序列,由元字符组成

```
import re
a = 'java|python|kotlin|ruby|javaScript'
r = re.findall('python',a)
print(r)  #返回一个列表  
>> ['python']

b = 'strf23hj3hjf2jigh7jff8ksffih9'
r = re.findall('\d',b)  #提取所有数字
print(r)
>> ['2', '3', '3', '2', '7', '8', '9']

s = 'abc,acc,asd,ade,afg,afc,ahv'
r = re.findall('a[cf]c',s)
print(r)
>> ['acc', 'afc']


ss = 'A24G8D73H59D6F4G'
def convert(value):
    num = value.group()
    if int(num) >= 6:
       return '9'
    else:
       return '0'
r = re.sub('\d',convert,ss)
print(r)
#A00G9D90H09D9F0G





'''
1.特殊符号
1) ^ $ * ? + {2} {2,} {2,5} |
2）[] [^] [a-z] .
3) \s \S \w \W
4) [\u4E00-\u9FA5] () \d
'''

# ^表示以什么开头 ^b 以b开头
# .表示任意字符
# *表示*前面的字符出现的次数 长度限制  >= 0
# $表示以$前面的字符结尾  3$ 表示以3结尾
# ?非贪婪匹配,按顺序匹配  默认是贪婪匹配模式，匹配到最后一个结果
# ()表示提取子字符串 括号中的字符串
# +表示+前面的字符出现大于一次的   >=1
# {2}表示前面的字符出现的次数
# {2,}表示前面的字符出现2次以上
# {2，5}表示前面的字符出现2到5次
# | 表示或关系
# [] 表示匹配括号中的任意一个字符 [abcd]  区间
# [0-9,a-z] 表示直接的字符 [.]表示. [*]表示*
# \s 表示空格一个字符长度
# \S 表示不为空格 一个字符长度
# \w 表示[a-zA-Z0-9_] 中的任意字符
# \W 表示不为上面w的的字符
# [\u4E00-\u9FA5] 表示提取中文
# \d 表示数字

import re

line = 'bobby123'
regex_str = '^b.*'  # 以b开头的任意字符串出现多次
if re.match(regex_str, line):  # match函数 参数1:模式  参数2:待匹配字符串
    print('yes')

regex_str2 = '^a'
print(re.match(regex_str2, line))  # None

regex_str3 = '.*3$'
print(re.match(regex_str3, line))  # 返回对象

regex_str4 = '^b.3$'  # 表示以b开头b后面是任意字符但是出现一次，以3结尾   bc3 bd3 等
regex_str5 = '^b.*3$'  # 表示以b开头b后面是任意字符任意长度，以3结尾   bcsss3 bsd3等

print(re.match(regex_str4, line))
print(re.match(regex_str5, line))

line2 = 'booooobby123'
regex_str6 = '.*(b.*b).*'  # 提取第一个b开头到第二个b结尾的字符串
match_obj = re.match(regex_str6, line2)  # 会贪婪匹配 匹配到最后两个bb
if match_obj:
    print(match_obj.group(1))  # group 取出所有匹配组中 第一组的字符串 返回bb  不是booooob
regex_str7 = '.*?(b.*?b).*'  # 从左边开始按顺序匹配 第一个b到第二个b结束
match_obj2 = re.match(regex_str7, line2)
if match_obj2:
    print(match_obj2.group(1))  # booooob

line3 = 'booooobbby123'
regex_str8 = '.*(b.+b).*'  # 提取以b开头，然后一个任意字符只出现大于一次的以b结尾的字符串
match_obj3 = re.match(regex_str8, line3)
if match_obj3:
    print(match_obj3.group(1))  # bbb  baab也匹配

line4 = 'booooobaab123'
regex_str9 = '.*(b.{2}b).*'
match_obj4 = re.match(regex_str9, line4)
if match_obj4:
    print(match_obj4.group(1))  # baab

line5 = 'bobby123'
regex_str10 = '(bobby|bobby123)'
match_obj5 = re.match(regex_str10, line5)
if match_obj5:
    print(match_obj5.group(1))  # bobby

regex_str11 = '([abcd].*b)'
match_obj6 = re.match(regex_str11, line5)  # bobb
if match_obj6:
    print(match_obj6.group(1))

phone = '18511234563'
regex_str12 = '1[34578][0-9]{9}'  # [0-9]0到9直接的任意字符
match_obj7 = re.match(regex_str12, phone)
if match_obj7:
    print('yes')

match_obj8 = re.match('你\s好', '你 好')
if match_obj8:
    print('yes')

hh1 = re.match('h[a-zA-Z0-9_]', 'haha_xx')  # 等同于下面
hh2 = re.match('\w', 'haha_xx')
print(hh1)
print(hh2)

study = 'study in 清华大学'
zhongwen = re.match('.*?([\u4E00-\u9FA5]+大学)', study)  # ? 非贪婪匹配
print(zhongwen.group(1))

year = '出生于2001年'
ye = re.match('.*?(\d{4})', year)
print(ye.group(1))  # 2001



line = 'XXXX出生于2001年7月21日'
line = 'XXXX出生于2001/7/21'
line = 'XXXX出生于2001-7-21'
line = 'XXXX出生于2001-07-21'
line = 'XXXX出生于2001-7'

# 提前年月日
rege_str = '.*出生于(\d{4}[年/-]\d{1,2}([月/-]\d{1,2}|[月/-]$|$))'
match_obj = re.match(rege_str, line)
print(match_obj.group(1))

'''
.*出生于(\d{4}[年/-]\d{1,2}([月/-]\d{1,2}|[月/-]$|$))
( 
  \d{4}    年/-
  \d{1,2}     月/- \d{1,2}   |   [月/-]$ | $

'''
```

#### JSON

```
# json 库
"""
json与python数据类型的对应关系
object            dict
array             list
number            int或float
null              None
true/flase        True/False
string            str
"""

import json

#对数据进行编码
python_data = {'persions':[{'name':'june','age':29},{'name':'zhen','age':31}]} #一个字典
json_str = json.dumps(python_data) #转换成一个json
print(json_str)

json_data = '{"name":"june","age":29}'
python_dic = json.loads(json_data)
print(python_dic)
```



