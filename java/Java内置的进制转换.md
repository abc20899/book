---
title: Java内置的进制转换
date: 2017-08-19 13:14:59
tags: java
categories: java
---

## Java内置的进制转换

### 十进制→其他进制:
```
//十进制转十六进制
Integer.toHexString(int i)   
//十进制转成八进制     
Integer.toOctalString(int i)   
//十进制转成二进制   
Integer.toBinaryString(int i)   
```

### 其他进制→十进制:
```
//十六进制转成十进制   
Integer.valueOf("FFFF",16).toString()   
//八进制转成十进制   
Integer.valueOf("876",8).toString()   
//二进制转十进制   
Integer.valueOf("0101",2).toString()   
```

