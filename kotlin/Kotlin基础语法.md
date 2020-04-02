---
title: Kotlin基础
date: 2017-06-11 16:36:36
tags: android kotlin
categories: kotlin
---
基础语法
---
#### 定义包名
 ```
 package my.demo
 import java.util.*
 ```
 包名不必和文件夹路径一致：源文件可以放在任意位置。
 <!--more-->
#### 定义函数
```
//传入两个Int类型，返回Int
fun sum(a: Int, b: Int): Int{
  return a+b
}
//等价于
fun sum1(a: Int, b: Int) = a + b
//返回一个没有意义值 Unit相当于java的void
//Unit可以省略
fun setValue(a: String): Unit{
    println("a=$a")
}
fun printSum(a: Int, b: Int) {
    println("sum of $a and $b is ${a + b}")
}
```
#### 局部变量
```
//声明常量
val a: Int = 2 //Int类型并初始化
val b = 3      //自动推导出Int类型
val c: Int     //声明类型
c = 3          //初始化
//声明变量
var x: Int = 5
var y = 5
println("y+1=${y+1}")

```
#### 字符串模板
```
//字符串模板
var aa = 1
var bb = 3
var s1 = "aa is $aa"
//使用表达式模板
var s2 = "${s1.replace("aa", "bb")}${bb}"
println(s1)
println(s2)
```
#### 条件表达式
```
//条件表达式
fun max(a: Int, b: Int) = if (a > b) a else b
```
#### 可空变量以及空值检查
当空值可能出现时应该明确指出该引用可空。
```
fun parseInt(str : String): Int?{
	//...
}

var str: String? = "abc"
str = null //允许为null
var str2: String = "abc"
str2 = null //不允许为null 编译错误
str2.length //可以调用，不可能为null
str.length  //不能调用，可能为null

//使用安全操作符，?.
//使用安全操作符 如果str不为空则返回长度,否则返回空。这个表达式的的类型是 Int?
str?.length
bob?.department?.head?.name //链式调用

//Elvis 操作符，?:
val l = str2.length ?: -1 //如果?:左边表达式不为空则返回，否则返回右边的表达式。注意右边的表带式只有在左边表达式为空是才会执行

//可以用 str!! ，这会返回一个非空的str或者抛出一个str为空的 NPE
val l = str !!.length()

//安全转换
val aInt: Int? = a as? Int
```
#### 类型检查并自动转换
```
//类型检查 返回值允许为null
fun getLength(obj: Any): Int? {
    if (obj is String) {
        //在检查类型时 obj会自动转换为String类型
        return obj.length
    }
    return null
}
//is !is 表达式 智能转换
//为了避免抛出异常，可以用 as? 这个安全转换符，这样失败就会返回 null
val x: String ?= y as? String
```
#### 循环
```
//循环
var arr = listOf<String>("a", "b", "c", "d")
//循环
fun <T> each(arr: List<T>) {
    //indices下标
    for (it in arr.indices) {
        println("${it} is ${arr[it]}")
    }

    for (it in arr) {
        println(it)
    }
}

```
#### while 循环
```
//while循环
fun whileTest(arr: List<String>) {
    var index = 0
    while (index < arr.size) {
        println("while: " + arr[index])
        index++
    }
}
```
#### when 表达式
```
//when表达式
fun translate(obj: Any): String = when (obj) {
    1 -> "one"
    2 -> "two"
    3 -> "three"
    else -> "unkonw"
}
```
#### ranges
区间表达式由具有操作符形式 .. 的 rangeTo 函数辅以 in 和 !in 形成
```
//ranges检查数值是否在某个范围内
fun rangeTest1(a: Int) {
    var list = listOf<Int>(1, 2, 3, 4, 5, 6, 7, 8)
    if (a in 0..list.lastIndex) {
        println("yes")
    } else {
        println("no")
    }
}

//ranges在范围内迭代：
fun rangeTest2(a: Int) {
    var list = listOf<Int>(1, 2, 3, 4, 5, 6, 7, 8)
    for (it in 0..a) {
        println("rangeTest2-->it:${it}")
    }
}

//使用步进 步长2
fun rangeTest3(a: Int) {
    var list = listOf<Int>(1, 2, 3, 4, 5, 6, 7, 8)
    for (it in 0..a step 2) {
        println("rangeTest3-->it:${it}")
    }
}

//倒序迭代
fun rangeTest4() {
    var list = listOf<Int>(1, 2, 3, 4, 5, 6, 7, 8)
    for (it in list.size downTo 1) {
        println("rangeTest4-->it:${it}")
    }
}

//until不包含
fun rangeTest5() {
    var list = listOf<Int>(1, 2, 3, 4, 5, 6, 7, 8)
    for (it in 1 until 4) {
        println("rangeTest5-->it:${it}")
    }
}
```
#### 集合
```
//list集合
fun listTest1() {
    var list2 = listOf<String>("aa", "bb", "cc", "dd")
    for (it in list2) {
        print(it + ",")
    }
}

//in操作符检查集合中是否包含某个对象
fun listTest2() {
    var set2 = setOf<String>("aa", "bb", "cc", "dd")
    if ("aa" in set2) {
        println("yes")
    } else {
        print("no")
    }
}

//lambda表达式过滤和映射集合
fun listTest3() {
    val fruits = listOf("banana", "avocado", "apple", "kiwi")
    fruits
            .filter { it.startsWith("a") }
            .sortedBy { it }
            .map { it.toUpperCase() }
            .forEach { println(it) }
}
```

## 学习链接
Kotlin 官方网站
http://kotlinlang.org/docs/reference/

Kotlin 官方网站 - 中文翻译
https://www.kotlincn.net/docs/reference/

《Kotlin for android Developers》中文翻译
https://www.gitbook.com/book/wangjiegulu/kotlin-for-android-developers-zh/details

Getting started with Android and Kotlin
https://www.kotlincn.net/docs/tutorials/kotlin-android.html

Get Started with Kotlin on Android
https://developer.android.google.cn/kotlin/get-started.html

awesome-kotlin-cn
https://github.com/xitu/awesome-kotlin-cn

anko
https://github.com/Kotlin/anko

http://www.runoob.com/kotlin/kotlin-tutorial.html























