---
title: dart_overview
date: 2020-03-17 22:04:45
tags: dart flutter
categories: flutter
---

### dart文档
[中文文档](https://www.dartcn.com/guides/language/language-tour)

### 重要的概念
* 变量即对象，并对应一个类的实例，数字，函数和 null 都是对象。所有对象继承自 Object 类
* 尽管 Dart 是强类型的，但是 Dart 可以推断类型
* Dart 支持泛型，如 List <int> （整数列表）或 List <dynamic> （任何类型的对象列表）
* Dart支持顶级函数，静态函数和实例函数、嵌套或局部函数 
* Dart支持顶级变量，静态变量和实例变量
* 条件表达式 condition ? expr1 : expr2 的值可能是 expr1 或 expr2 
	<!--more-->
### 变量
变量仅存储对象引用

```
//不需要指定变量类型
var name = 'Bob';
//对象不限定为单个类型，可以指定为对象类型或动态类型
dynamic name = 'Bob';
//显式声明可以推断出的类型
String name = 'David';
```

##### 默认值
未初始化的变量默认值是null。 Dart中一切都是对象，数字类型也不例外。

```
int lineCount;
print(lineCount); //null
```
##### Final 和 Const
从来不会被修改的变量,可以使用final或const,Final 变量的值只能被设置一次；Const变量在编译时就已经固定。

* final

```
final String name = 'june';
final age = 11;
name = 'Alice'; // Error: 一个 final 变量只能被设置一次。
```

* const <br>
编译时就固定变量的值,类级别的变量需要使用 static const

```
const pi = 3.14159;
const double circle = 2 * pi * 2;
print(circle);  //12.56636
```
Const 关键字不仅可以用于声明常量变量。 还可以用来创建常量值，以及声明创建常量值的构造函数。 任何变量都可以拥有常量值。

```
var foo = const [];  //常量值
final bar = const [];
const baz = []; //声明const的初始化表达式中const可以被省略
//非Final，非const的变量是可以被修改的,即使这些变量曾经引用过const值。
foo = [1, 2, 3]; // 曾经引用过const []常量值。
```

### 内建类型

```
Number
String
Boolean
List (也被称为 Array)
Map
Set
Rune (用于在字符串中表示 Unicode 字符)
Symbol
```
##### Number
Number有 int 和 double两种类型

```
var x = 1;
var hex = 0xDEADBEEF;
var y = 1.1;
var exponents = 1.42e5;
double x = 1; //int 字面量会自动转换成 double 类型
//String -> int
var one = int.parse('1');
//String -> double
var pointX = double.parse('1.1');
//int -> String
String oneAsStr = 1.toString();
//double -> String
String piAsString = 3.14.toStringAsFixed(2);
```

##### String
* 用' '或者" "创建

```
var s1 = 'Single quotes'
var s2 = "Double quotes"
var s3 = 'It\'s easy to' //转义\
var s4 = "It's even easier"
```
* ${表达式}

```
var s = 'string interpolation';
var s2 = 'ss ${s}';
```
* == 运算符用来测试两个对象是否相等

```
var ss1 = 'String concatenation';
print(ss1 == 'String concatenation'); //true
```

* 三个单引号或者三个双引号实现多行字符串对象的创建

```
var sss1 = '''
you can create
multi-line strings like this one.
''';
print(sss1);
```
* 使用 r 前缀，可以创建 “原始 raw” 字符串：

```
var s = r"In a raw string, even \n isn't special.";

```

##### Boolean
使用bool类型表示布尔值 true flase

##### List

```
var list = [1,2,3]; //推断为 List<int>
print(list.length);
print(list[1]);
//在 List 字面量之前添加 const 关键字，可以定义 List 类型的编译时常量
var constantList = const [1,2,3];
//constantList[1] = 1; //错误
```

##### Set
set 唯一、无序的集合

```
var setStr = {'book','desk','door'}; //推断为Set<String> 类型
//创建一个空集
var names1 = <String>{} //{}前必须指定类型
Set<String> names2 = {}; //指定类型
var names3 = {}; //此创建了一个map类型 Map<dynamic, dynamic> 
//add  addAll 添加元素
var elements = <String>{};
elements.add('hello');
//const 创建运行时常量
final constanstSet = const {
 'flo',
 'wer',
 'wey'
};
```

##### Map

```
//创建并初始化
var gifts = {
    'first': 'apple',
    'second': 'cup',
    'fifth': 'car'
}; //Map<String,String>
var weeks = {
  1:'Monday',
  2:'Tuesday'
};//Map<int, String> 

//使用Map构造函数创建
var gifts2 = Map();
gifts2['11'] = 'AA';
gifts2['22'] = 'BB';

var weeks2 = Map();
weeks2[1] = 'Monday';
weeks2[2] = 'Tuesday';

//添加键值对、获取键值对
gifts2['fourth'] = 'bike';
var gift1 = gifts2['first'];

//如果map不包所要查找的key，则返回null
//length获取长度
//创建map运行时常量
final constantMap = const {
	2:'Two',
	3:'Three'
};
```

### 函数 Function类型
* 函数可以被赋值给变量或者作为参数传递给其他函数。 也可以把 Dart 类的实例当做方法来调用。

```
int sum(int a,int b){
  return a + b;
}
//如果函数中只有一句表达式，可以使用简写语法
int sum2(int a, int b) => a + b;

```
##### 参数
* 函数有两种参数类型: required 和 optional。 required 类型参数在参数最前面， 随后是 optional 类型参数。 

1、 可选命名参数

```
//可选命名参数 使用"{}"包围的参数属于可选命名参数
void _buildThree(int num, {String name, int range}) {
}

//可选参数设置默认值
void _buildThree(int num, {String name, int range = 10}) {
}

//调用时，使用paramName:value的形式指定为哪个可选参数赋值
_buildThree(10,range: 1);
```

2、 可选位置参数<br>
在方法参数中，使用"[]"包围的参数属于可选位置参数

```
void _buildHouse(int num, [String where, int range]) {
}
  
void _buildHouseAndDefaultValue(int num, 
[String where = 'Shanghai', int range]) {

}
//调用包含可选位置参数的方法时，无需使用paramName:value的形式
_buildHouse(10,10); //不可行的
_buildHouse(10,'shenzhen',10); //可行的
_buildHouseAndDefaultValue(10,10); //不可行的
_buildHouseAndDefaultValue(10,'shenzhen',10); //可行的
```

3、默认参数值

```
//list或map可以作为默认值传递
void doStuff(
    {List<int> list = const [1, 2, 3],
    Map<String, String> gifts = const {
      'first': 'paper',
      'second': 'cotton',
      'third': 'leather'
    }}) {
  print('list:  $list');
  print('gifts: $gifts');
}
```

##### main() 函数
任何应用都必须有一个顶级 main() 函数，作为应用服务的入口。 main() 函数返回值为空，参数为一个可选的 List<String> 。

```
//命令行应用的 main() 函数  运行应用： dart main.dart 1 test
void main(List<String> arguments){
  print(arguments);
  
  assert(arguments.length == 2);
  assert(int.parse(arguments[0]) == 1);
  assert(arguments[1] == 'test');
}
```
##### 函数是一等对象

```
//函数作为参数
void printElement(int element) {
  print(element);
}
var list1 = [1, 2, 3, 4, 5, 6];
list1.forEach(printElement);

//函数赋值给变量  匿名函数
var upLitter = (msg) => '!!! ${msg.toUpperCase()} !!!';
print(upLitter('hello')); //!!! HELLO !!!
```
##### 匿名函数
也被称为 lambda 或者 closure

```
var list2 = ['apple', 'bananas', 'oranges'];
list2.forEach((item) {
  print('${list2.indexOf(item)} : ${item}');
});
list2.forEach(
    (item) => print('${list.indexOf(item)}: $item'));
/**
0 : apple
1 : bananas
2 : oranges
*/
```
### 运算符

```
a++
a + b
a = b
a == b
c ? a : b
a is T

a = 0;
b = ++a; // a自加后赋值给b。
assert(a == b); // 1 == 1

a = 0;
b = a++; // a先赋值给b后，a自加。
assert(a != b); // 1 != 0

a = 0;
b = --a; // a自减后赋值给b。
assert(a == b); // -1 == -1

a = 0;
b = a--; // a先赋值给b后，a自减。
assert(a != b); // -1 != 0
```
##### as
将对象强制转换为特定类型
##### is
obj is Object 总是true。 但是只有obj实现了T的接口时，obj is T 才是true。
##### is!
##### ??=
只有当被赋值的变量为 null 时才会赋值给它

```
// 如果b为空时，将变量赋值给b，否则，b的值保持不变。
b ??= value;
```
##### ??
expr1 ?? expr2
如果 expr1 是 non-null， 返回 expr1 的值； 否则, 执行并返回 expr2 的值。

```
String playerName(String name) => name ?? 'Guest';
```

##### 级联运算符 (..)
可以实现对同一个对像进行一系列的操作。 除了调用函数， 还可以访问同一对象上的字段属性。 这通常可以节省创建临时变量的步骤， 同时编写出更流畅的代码。

```
querySelector('#confirm') // 获取对象。
  ..text = 'Confirm' // 调用成员变量。
  ..classes.add('important')
  ..onClick.listen((e) => window.alert('Confirmed!'));
//上面的代码等价于  
var button = querySelector('#confirm');
button.text = 'Confirm';
button.classes.add('important');
button.onClick.listen((e) => window.alert('Confirmed!'));  

//sb.write() 函数调用返回 void， 
var sb = StringBuffer();
sb.write('foo')
  ..write('bar'); // Error: 不能在 void 对象上创建级联操作。
```
### 流程控制语句
##### if 和 else
##### for 循环   for in
##### while 和 do-while
##### break 和 continue
##### switch 和 case
### 异常
##### throw
```
throw FormatException('Expected at least 1 section');
throw 'Out of llamas!'; //抛出任意的对象
```
##### catch

```
try {
  breedMoreLlamas();
} on OutOfLlamasException {
  buyMoreLlamas();
}

//捕获语句中可以同时使用 on 和 catch ，也可以单独分开使用。 使用 on 来指定异常类型， 使用 catch 来 捕获异常对象。
try {
  breedMoreLlamas();
} on OutOfLlamasException {
  // 一个特殊的异常
  buyMoreLlamas();
} on Exception catch (e) {
  // 其他任何异常
  print('Unknown exception: $e');
} catch (e) {
  // 没有指定的类型，处理所有异常
  print('Something really unknown: $e');
}

//catch() 函数可以指定1到2个参数， 第一个参数为抛出的异常对象， 第二个为堆栈信息 
try {
  // ···
} on Exception catch (e) {
  print('Exception details:\n $e');
} catch (e, s) {
  print('Exception details:\n $e');
  print('Stack trace:\n $s');
}
```
##### finally

```
try {
  breedMoreLlamas();
} finally {
  // Always clean up, even if an exception is thrown.
  cleanLlamaStalls();
}

try {
  breedMoreLlamas();
} catch (e) {
  print('Error: $e'); // Handle the exception first.
} finally {
  cleanLlamaStalls(); // Then clean up.
}
```
### 类
Dart 是一种基于类和 mixin 继承机制的面向对象的语言
##### 使用 (.) 来引用实例对象的变量和方法
##### 使用 ?. 来代替 . ， 可以避免因为左边对象可能为 null
##### 实例变量会生成隐式getter方法，非final会生成setter方法

```
class Point{
  var x = 0.0;
  var y = 0.0;
}

void testPoint(){
  var p = Point();
  p.x = 1.1;
  //使用 ?. 来代替 . ， 可以避免因为左边对象可能为 null
  // 如果 p 为 non-null，设置它变量 y 的值为 4。
  p?.y = 4;
}
```
##### 构造函数
* 默认构造函数 默认构造函数没有参数并会调用父类的无参构造函数。
* 构造函数不被继承
* 命名构造函数  使用命名构造函数可为一个类实现多个构造函数
* 构造函数不能够被继承， 这意味着父类的命名构造函数不会被子类继承。 如果希望使用父类中定义的命名构造函数创建子类， 就必须在子类中实现该构造函数。*

```
class Point {
  var x = 0.0;
  var y = 0.0;

  Point(this.x, this.y);

  //命名构造函数
  Point.formJson(Map json) {
    x = json['x'];
    y = json['y'];
  }
}

void testPoint() {
  var p = Point(0, 0);
  p.x = 1.1;
  p?.y = 2.0;

  var p2 = Point.formJson({'x': 1.2, 'y': 2.3});
}
```
##### 常量构造函数
如果你的类提供一个状态不变的对象，你可以把这些对象 定义为编译时常量。要实现这个功能，需要定义一个 const 构造函数,并且声明所有类的变量为 final。

```
class ImmutablePoint {
  //变量定义为final
  final x;
  final y;

  //常量构造函数
  const ImmutablePoint(this.x, this.y);

  static final origin = const ImmutablePoint(0.0, 0.0);
}

void testConstPoint() {
  //创建一个常量对象
  const a = ImmutablePoint(1, 1);
  const b = ImmutablePoint(1, 1);
  print(a == b); //true

  //创建一个非常量对象
  var aa = ImmutablePoint(2, 2);
  var bb = ImmutablePoint(2, 2);
  print(aa == bb); //false
}
```
##### 获取对象的类型
使用对象的 runtimeType 属性，可以在运行时获取对象的类型,返回一个Type对象。

```
void getClassType() {
  var p = Point(0, 0);
  print(p.runtimeType); //Point
}
```
##### 调用父类非默认构造函数
默认情况下，子类的构造函数会自动调用父类的默认构造函数（匿名，无参数）。 父类的构造函数在子类构造函数体开始执行的位置被调用。 如果提供了一个 initializer list （初始化参数列表）， 则初始化参数列表在父类构造函数执行之前执行。<br>

1、initializer list （初始化参数列表）<br>
2、superclass’s no-arg constructor （父类的无名构造函数）<br>
3、main class’s no-arg constructor （主类的无名构造函数）<br>

```
//如果父类中没有匿名无参的构造函数， 则需要手工调用父类的其他构造函数
class Person {
  Person.fromJson(Map data) {
    print('in person');
  }
}

class Student extends Person {
  Student.fromJson(Map data) : super.fromJson(data) {
    print('in student');
  }
}

void testSuper() {
  var li = Student.fromJson({});
  //in person
  //in student
}
```
##### 初始化列表
在构造函数体执行之前初始化实例变量。 各参数的初始化用逗号分隔。

```
class Point2 {
  num x, y;

  Point2.fromJson(Map data)
      : x = data['x'],
        y = data['y'] {
    print('In Point.fromJson(): ($x, $y)');
  }

  Point2.withAssert(this.x, this.y) : assert(x > 0) {
    print('In Point.withAssert(): ($x, $y)');
  }
}

//使用初始化列表可以很方便的设置 final 字段
class Point3 {
  final num x;
  final num y;
  final num distanceFromOrigin;

  Point3(x, y, distanceFromOrigin)
      : x = x,
        y = y,
        distanceFromOrigin = sqrt(x * x + y * y);
}
```
##### 重定向构造函数
有时构造函数的唯一目的是重定向到同一个类中的另一个构造函数,重定向构造函数的函数体为空， 构造函数的调用在冒号 (:) 之后。

```
class Point4 {
  num x, y;

  //主构造函数
  Point4(this.x, this.y);

  //重定向函数 指向主构造函数
  Point4.alongXAxis(num x) : this(x, 0);
}
```
##### 工厂构造函数
当执行构造函数并不总是创建这个类的一个新实例时，则使用 factory 关键字<br>
工厂构造函数无法访问 this

```
class Logger {
  final String name;

  static final _cache = Map<String, Logger>();

  bool mute = false;

  Logger._internal(this.name); //命名构造函数

  factory Logger(String name) {
    //工厂构造函数
    if (_cache.containsKey(name)) {
      return _cache[name];
    } else {
      final logger = Logger._internal(name);
      _cache[name] = logger;
      return logger;
    }
  }

  void log(String msg) {
    if (!mute) print(msg);
  }
}

var logger = Logger('UI');
logger.log('Button click');
```

##### Getter 和 Setter
```
class Rectangle {
  num left, top, width, height;

  Rectangle(this.left, this.top, this.width, this.height);

  //两个计算属性 right bottom
  num get right => left + width;

  num get bottom => top + height;

  set right(num value) => left = value - width;

  set bottom(num value) => top = value - height;
}

void testRectangle() {
  var rect = Rectangle(3, 4, 15, 20);
  print(rect.left); // 3
  rect.right = 13;
  print(rect.left); // -2
}
```

##### 抽象类
抽象类不能实例化。 抽象类通常用来定义接口，以及部分实现。 如果希望抽象类能够被实例化，那么可以通过定义一个 工厂构造函数 来实现。

```
abstract class Doer {
  void doSomething(); //抽象方法
}

class EffectiveDoer extends Doer {
  void doSomething() {
    print('');
  }
}
```



