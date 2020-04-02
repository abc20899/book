---
title: Java中创建对象的5种方式
date: 2017-05-21 13:35:26
tags: java
categories: java
---

## Java中有5种创建对象的方式
方式                               | 构造函数调用
----------------------------------|--------------------
使用new关键字                       | } → 调用了构造函数
使用Class类的newInstance方法	       | } → 调用了构造函数
使用Constructor类的newInstance方法  |  } → 调用了构造函数
使用clone方法	                       | } → 没有调用构造函数
使用反序列化	                       | } → 没有调用构造函数
<!--more-->
### 1.使用new关键字
这是最常见也是最简单的创建对象的方式了。通过这种方式，我们可以调用任意的构造函数(无参的和带参数的)。
比如：
```
Persion p = new Persion();
Persion june = new Persion("junechiu",28);
```
### 2.使用Class类的newInstance方法
我们也可以使用Class类的newInstance方法创建对象，这个newInstance方法调用无参的构造器创建对象，
如：
```
Student student2 = (Student)Class.forName("包名.Student").newInstance();　
```
或者：
```
Student stu = Student.class.newInstance();
```
### 3.使用Constructor类的newInstance方法
本方法和Class类的newInstance方法很像，java.lang.relect.Constructor类里也有一个newInstance方法可以创建对象。我们可以通过这个newInstance方法调用有参数的和私有的构造函数。
如： 
```
Constructor<Student> constructor = Student.class.getInstance(); 
Student stu = constructor.newInstance();　
```
这两种newInstance的方法就是大家所说的反射，事实上Class的newInstance方法内部调用Constructor的newInstance方法。这也是众多框架Spring、Hibernate、Struts等使用后者的原因。
### 4.使用clone方法
无论何时我们调用一个对象的clone方法，jvm就会创建一个新的对象，将前面对象的内容全部拷贝进去。用clone方法创建对象并不会调用任何构造函数。要使用clone方法，我们需要先实现Cloneable接口并实现其定义的clone方法。
如：
```
Student stu2 = <Student>stu.clone();
```
这也是原型模式的应用。

### 5.使用反序列化
当我们序列化和反序列化一个对象，JVM会给我们创建一个单独的对象，在反序列化时，JVM创建对象并不会调用任何构造函数。为了反序列化一个对象，我们需要让我们的类实现Serializable接口。
如：
```
ObjectInputStream in = new ObjectInputStream (new FileInputStream("data.obj")); 
Student stu3 = (Student)in.readObject();
```
两种newInstance方法区别:
* Class类位于java的lang包中，而构造器类是java反射机制的一部分。
* Class类的newInstance只能触发无参数的构造方法创建对象，而构造器类的newInstance能触发有参数或者任意参数的构造方法来创建对象。
* Class类的newInstance需要其构造方法是共有的或者对调用方法可见的，而构造器类的newInstance可以在特定环境下调用私有构造方法来创建对象。
* Class类的newInstance抛出类构造函数的异常，而构造器类的newInstance包装了一个InvocationTargetException异常。
* Class类本质上调用了反射包构造器类中无参数的newInstance方法，捕获了InvocationTargetException，将构造器本身的异常抛出。





























           