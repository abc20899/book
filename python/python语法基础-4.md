---
title: python基础4
date: 2018-02-10 22:31:13
tags: python
categories: python
---

### 枚举类

```
from enum import Enum
# 枚举类型
# 常量不可变
# 可以==比较
# 枚举标签的值可以相同，以第一个为准 如果没有@unique装饰
# 只允许有数字可以继承IntEnum

class VIP(Enum):
    YELLOW = 1
    YELLOW_ALIAS = 1
    GREEN = 2
    RED = 3

print(VIP.GREEN.value)  # 获取枚举值 2
print(VIP.GREEN.name)  # 获取枚举名称 GREEN
print(VIP(2))          # VIP.GREEN

#遍历枚举
for v in VIP:
    print(v)
```
<!--more-->
### 函数式编程
```
def add(x, y):
    return x + y

print(type(add))  # <class 'function'>

```

#### 闭包

```
def fun_out():
    a = 25
    def fun_in(x):
        print('this is inner func')
        return a * x * x
    return fun_in  #返回内部函数

f = fun_out()  # fun_in()
print(f(2))    # 调用  
>> this is inner func
>> 100

a = 10        # 修改a变量值?        
print(f(2))   # f(内部函数) 会调用fun_out函数中环境变量 a = 25   
>> 100

# 闭包 = 函数+环境变量
print(f.__closure__)  
>> (<cell at 0x10066a0d8: int object at 0x100279000>,)
print(f.__closure__[0].cell_contents)  
>> 25


#测试
def f1():
    a = 10
    def f2():
        a = 20  #a内部函数的局部变量，没有引用外部环境变量，所以不为闭包
        print(a)
    print(a)
    f2()
    print(a)

f1()
>> 10
>> 20
>> 10
ff = f1()  #不是闭包

#demo
def result(pos):
    def add(step):
        nonlocal pos  # 非局部变量
        pos = pos + step
        return pos
    return add
fs = result(0)
print(fs(2))  
>> 2
print(fs(3))  
>> 5
print(fs(4))  
>> 9

```

#### 匿名函数
```
# 有名字的函数
def sum(a, b):
    return a + b

# 定义匿名函数 lambda 参数:表达式
lam = lambda a, b: a + b
print(lam(1, 2))  
>> 3

# 三元表达式 如果为真返回if前的结果
r = 2 if 2 > 1 else 1

# map映射函数  参数：fun类型,序列类型
def sq(x):                            #函数
    return x * x
    
list_x = [1, 2, 3, 4, 5, 6, 7, 8, 9]  #序列

rr = map(sq, list_x)                  #进行列表元素映射 元素平方
print(list(rr))
>> [1, 4, 9, 16, 25, 36, 49, 64, 81]

# 使用lambda
map(lambda x: x * x, list_x)

list_y = [1, 2, 3, 4, 5, 6, 7, 8, 9]
map(lambda x, y: x * x + y, list_x, list_y)  # 传入多个列表

# reduce连续对每个元素进行计算
list_z = [1, 2, 3, 4, 5, 6, 7, 8, 9]
red = reduce(lambda x, y: x + y, list_z)
print(red)
>> 45

# filter 过滤
list_xx = [1, 2, 3, 4, 5, 6, 6, 7, 8, 8, 9, 9]
fi = filter(lambda x: x > 4, list_xx)
print(list(fi))
>> [5, 6, 6, 7, 8, 8, 9, 9]

```

#### 装饰器
```
def ff():
    print('ff')

def ff2():
    print('ff2')

#在已有函数中加入时间功能
def print_time(func):
    print(time.time())
    func

print_time(ff())
print_time(ff2())

# 装饰器定义
def decorator(func):
    def wrapper():
        print(time.time())
        func()
    return wrapper

f3 = decorator(ff)
f3()

# 装饰器
@decorator
def ff5():
    print('ff5')
ff5()

# 带参数的装饰器 多参数 关键字参数
def decorator2(func):
    def wrapper(*param, **kw):
        print(time.time())
        func(*param, **kw)
    return wrapper

@decorator2
def ff6(name):
    print('ff6：' + name)

@decorator2
def ff7(name, age):
    print('ff7：' + name + ": " + str(age))

@decorator2
def ff8(name, age, **kw):
    print('ff8：' + name + ": " + str(age) + " kw:" + str(kw))

ff6('name')
ff7('hehe', 23)
ff8('ss', 33, a='aa', b='bb')
```

### 字典映射

```
def get_monday():
    return 'Monday'

def get_tuesday():
    return 'Tuesday'

def get_wednesday():
    return 'Wednesday'

def get_default():
    return ''

switcher = {
    1: get_monday,
    2: get_tuesday,
    3: get_wednesday
}

day = 2
day_name = switcher.get(day, get_default)()
print(day_name)
```

### tuple、set、列表、字典推导式
```
a = [1, 2, 3, 4, 5, 6, 7]
b = [i ** 2 for i in a]
print(b)
# [1, 4, 9, 16, 25, 36, 49]
c = [i for i in a if i > 5]
print(c)
# [6, 7]

ss = {1, 2, 3, 4, 5, 6, 7, 8, 9}
s3 = {s for s in ss if s > 2}
print(s3)
# {3, 4, 5, 6, 7, 8, 9}

students = {
    '小明': 12,
    '小张': 13,
    '小李': 14
}
keys = [key for key, value in students.items()]
print(keys)
# ['小明', '小张', '小李']
kvs = {value: key for key, value in students.items()}
print(kvs)
# {12: '小明', 13: '小张', 14: '小李'}
# key value 颠倒
```


### None也是一个对象 不等于 空字符串、空列表、False、0
```
aaa = ''
bbb = []
ccc = False
print(aaa == None)  # False
print(bbb == None)  # False
print(ccc == None)  # False
print(type(None))  # <class 'NoneType'>


# 判空操作 if a:   if not a:

class Test():
    pass

test = Test()
if test:
    print('s')
print(bool(None))
print(bool([]))
print(bool(test))  # True


class Test2():
    # 返回ture整个类为true 优先__len__方法
    def __bool__(self):
        return True

    # 返回非0整个类为true
    def __len__(self):
        return 0  # 0 为False  对象为False


test2 = Test2()
print(bool(test2))  # False
print(len(test2))  # 调用对象中的__len__方法
```