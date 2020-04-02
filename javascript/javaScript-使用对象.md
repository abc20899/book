### 对象综述
javascript 中的对象(物体)，和其它编程语言中的对象一样，可以比照现实生活中的对象(物体)来理解它。 javascript 中对象(物体)的概念可以比照着现实生活中实实在在的物体来理解。

在javascript中，一个对象可以是一个单独的拥有属性和类型的实体。我们拿它和一个杯子做下类比。一个杯子是一个对象(物体)，拥有属性。杯子有颜色，图案，重量，由什么材质构成等等。同样，javascript对象也有属性来定义它的特征。

### 对象和属性
一个 javascript 对象有很多属性。一个对象的属性可以被解释成一个附加到对象上的变量。对象的属性和普通的 javascript 变量基本没什么区别，仅仅是属性属于某个对象。属性定义了对象的特征(译注：动态语言面向对象的鸭子类型)。你可以通过点符号来访问一个对象的属性。

```
objectName.propertyName
```
和其他 javascript 变量一样，对象的名字(可以是普通的变量)和属性的名字都是大小写敏感的。你可以在定义一个属性的时候就给它赋值。例如，我们创建一个myCar的对象然后给他三个属性，make，model，year。具体如下所示：

```
var myCar = new Object();
myCar.make = "Ford";
myCar.model = "Mustang";
myCar.year = 1969;
```
对象中未赋值的属性的值为undefined（而不是null）。

```
myCar.noProperty; // undefined
```
JavaScript 对象的属性也可以通过方括号访问或者设置（更多信息查看 property accessors）. 对象有时也被叫作关联数组, 因为每个属性都有一个用于访问它的字符串值。例如，你可以按如下方式访问 myCar 对象的属性：

```
myCar["make"] = "Ford";
myCar["model"] = "Mustang";
myCar["year"] = 1969;
```
一个对象的属性名可以是任何有效的 JavaScript 字符串,，或者可以被转换为字符串的任何类型，包括空字符串。然而，一个属性的名称如果不是一个有效的 JavaScript 标识符（例如，一个由空格或连字符，或者以数字开头的属性名），就只能通过方括号标记访问。这个标记法在属性名称是动态判定（属性名只有到运行时才能判定）时非常有用。例如：

```
var myObj = new Object(),
    str = "myString",
    rand = Math.random(),
    obj = new Object();
myObj.type              = "Dot syntax";
myObj["date created"]   = "String with space";
myObj[str]              = "String value";
myObj[rand]             = "Random Number";
myObj[obj]              = "Object";
myObj[""]               = "Even an empty string";
console.log(myObj);
```
你也可以通过存储在变量中的字符串来访问属性：

```
var propertyName = "make";
myCar[propertyName] = "Ford";
propertyName = "model";
myCar[propertyName] = "Mustang";
```
你可以在  for...in 语句中使用方括号标记以枚举一个对象的所有属性。为了展示它如何工作，下面的函数当你将对象及其名称作为参数传入时，显示对象的属性：

```
function showProps(obj, objName) {
  var result = "";
  for (var i in obj) {
    if (obj.hasOwnProperty(i)) {
        result += objName + "." + i + " = " + obj[i] + "\n";
    }
  }
  return result;
}
```
因而，对于函数调用 showProps(myCar, "myCar") 将返回以下值：

```
myCar.make = Ford
myCar.model = Mustang
myCar.year = 1969
```
### 枚举一个对象的所有属性
从 ECMAScript 5 开始，有三种原生的方法用于列出或枚举对象的属性：

* for...in 循环
该方法依次访问一个对象及其原型链中所有可枚举的属性。
* Object.keys(o)
该方法返回一个对象 o 自身包含（不包括原型中）的所有属性的名称的数组。
* Object.getOwnPropertyNames(o)
该方法返回一个数组，它包含了对象 o 所有拥有的属性（无论是否可枚举）的名称。

在 ECMAScript 5 之前，没有原生的方法枚举一个对象的所有属性。然而，可以通过以下函数完成：

```
function listAllProperties(o){     
	var objectToInspect;     
	var result = [];
	for(objectToInspect = o; objectToInspect !== null; objectToInspect = Object.getPrototypeOf(objectToInspect)){  
		result = result.concat(Object.getOwnPropertyNames(objectToInspect));  
	}
	return result; 
}
```
这在展示 “隐藏”（在原型中的不能通过对象访问的属性，因为另一个同名的属性存在于原型链的早期）的属性时很有用。可以通过在数组中去除同名元素即可轻松地列出访问的属性。

### 创建新对象
JavaScript 拥有一系列预定义的对象。另外，你可以创建你自己的对象。从  JavaScript 1.2 之后，你可以通过对象初始化器（Object Initializer）创建对象。或者你可以创建一个构造函数并使用该函数和 new 操作符初始化对象。

1.使用对象初始化器

```
var obj = { property_1:   value_1,   // property_# may be an identifier...
            2:            value_2,   // or a number...
            // ...,
            "property n": value_n }; // or a string
```
这里 obj 是新对象的名称，每一个 property_i 是一个标识符（可以是一个名称、数字或字符串字面量），并且每个 value_i 是一个其值将被赋予 property_i 的表达式。obj 与赋值是可选的；如果你不需要在其他地方引用对象，你就不需要将它赋给一个变量。（注意在接受一条语句的地方，你可能需要将对象字面量括在括号里，从而避免将字面量与块语句相混淆）

如果一个对象是通过在顶级脚本的对象初始化器创建的，则 JavaScript 在每次遇到包含该对象字面量的表达式时都会创建对象。同样的，在函数中的初始化器在每次函数调用时也会被创建。

下面的语句只有当 cond 表达式的值为 true 时创建对象并将其赋给变量 x。

```
if (cond) var x = {hi: "there"};
```
下例创建了有三个属性的 myHonda 对象。注意它的 engine 属性也是一个拥有自己属性的对象。

```
var myHonda = {color: "red", wheels: 4, engine: {cylinders: 4, size: 2.2}};
```
你也可以用对象初始化器来创建数组。

2.使用构造函数
作为另一种方式，你可以通过两步来创建对象：

通过创建一个构造函数来定义对象的类型。首字母大写是非常普遍而且很恰当的惯用法。
通过 new 创建对象实例。
为了定义对象类型，为对象类型创建一个函数以声明类型的名称、属性和方法。例如，你想为汽车创建一个类型，并且将这类对象称为 car ，并且拥有属性 make, model, 和 year，你可以创建如下的函数：

```
function Car(make, model, year) {
  this.make = make;
  this.model = model;
  this.year = year;
}
```
注意通过使用 this 将传入函数的值赋给对象的属性。
现在你可以象这样创建一个 mycar 对象：

```
var mycar = new Car("Eagle", "Talon TSi", 1993);
```
该创建了 mycar 并且将指定的值赋给它的属性。因而 mycar.make 的值是字符串 "Eagle"， mycar.year 的值是整数 1993，依此类推。
你可以通过调用 new 创建任意数量的 car 对象。例如：

```
var kenscar = new Car("Nissan", "300ZX", 1992);
var vpgscar = new Car("Mazda", "Miata", 1990);
```
一个对象的属性值可以是另一个对象。例如，假设你按如下方式定义了 person 对象:

```
function Person(name, age, sex) {
  this.name = name;
  this.age = age;
  this.sex = sex;
}
```
然后按如下方式创建了两个 person 实例:

```
var rand = new Person("Rand McKinnon", 33, "M");
var ken = new Person("Ken Jones", 39, "M");
```
那么，你可以重写 car 的定义以包含一个拥有它的 owner 属性，如：

```
function Car(make, model, year, owner) {
  this.make = make;
  this.model = model;
  this.year = year;
  this.owner = owner;
}
```
你可以按如下方式创建新对象：

```
var car1 = new Car("Eagle", "Talon TSi", 1993, rand);
var car2 = new Car("Nissan", "300ZX", 1992, ken);
```
注意在创建新对象时，上面的语句将 rand 和 ken 作为 owner 的参数值，而不是传入字符串字面量或整数值。接下来你如果想找出 car2 的拥有者的姓名，你可以访问如下属性：

```
car2.owner.name
```
注意你总是可以为之前定义的对象增加新的属性。例如，语句

```
car1.color = "black";
```
为 car1 增加了 color 属性，并将其值设为 "black." 然而，这并不影响其他的对象。想要为某个类型的所有对象增加新属性，你必须将属性加入到 car 对象类型的定义中。

3.使用 Object.create 方法

对象也可以用 Object.create() 方法创建。该方法非常有用，因为它允许你为创建的对象选择其原型对象，而不用定义一个构造函数。

```
// Animal properties and method encapsulation
var Animal = {
  type: "Invertebrates", // Default value of properties
  displayType : function() {  // Method which will display type of Animal
    console.log(this.type);
  }
}
// Create new animal type called animal1 
var animal1 = Object.create(Animal);
animal1.displayType(); // Output:Invertebrates
// Create new animal type called Fishes
var fish = Object.create(Animal);
fish.type = "Fishes";
fish.displayType(); // Output:Fishes
```
### 继承
所有的 JavaScript 对象继承于至少一个对象。被继承的对象被称作原型，并且继承的属性可通过构造函数的 prototype 对象找到。

### 对象属性索引
在 JavaScript 1.0 中，你可以通过名称或序号访问一个属性。但是在 JavaScript 1.1 及之后版本中，如果你最初使用名称定义了一个属性，则你必须通过名称来访问它；而如果你最初使用序号来定义一个属性，则你必须通过索引来访问它。

这个限制发生在你通过构造函数创建一个对象和它的属性（就象我们之前通过 Car 对象类型所做的那样）并且显式地定义了单独的属性（如 myCar.color = "red"）之时。如果你最初使用索引定义了一个对象属性，例如 myCar[5] = "25"，则你只可能通过 myCar[5] 引用它。

这条规则的例外是从与HTML对应的对象，例如 forms 数组。对于这些数组的元素，你总是既可以通过其序号（依据其在文档中出现的顺序），也可以按照其名称（如果有的话）访问它。举例而言，如果文档中的第二个 <form> 标签有一个 NAME 属性且值为 "myForm"，访问该 form 的方式可以是 document.forms[1]，document.forms["myForm"]或 document.myForm。

### 为对象类型定义属性
你可以通过 prototype 属性为之前定义的对象类型增加属性。这为该类型的所有对象，而不是仅仅一个对象增加了一个属性。下面的代码为所有类型为 car 的对象增加了 color 属性，然后为对象 car1 的 color 属性赋值：

```
Car.prototype.color = null;
car1.color = "black";
```
### 定义方法
一个方法 是关联到某个对象的函数，或者简单地说，一个方法是一个值为某个函数的对象属性。定义方法就像定义普通的函数，除了它们必须被赋给对象的某个属性。

```
objectName.methodname = function_name;
var myObj = {
  myMethod: function(params) {
    // ...do something
  }
};
```
这里 objectName 是一个已经存在的对象，methodname 是方法的名称，而 function_name 是函数的名称。
你可以在对象的上下文中象这样调用方法：

```
object.methodname(params);
```
你可以在对象的构造函数中包含方法定义来为某个对象类型定义方法。例如，你可以为之前定义的 car 对象定义一个函数格式化并显示其属性：

```
function displayCar() {
  var result = "A Beautiful " + this.year + " " + this.make
    + " " + this.model;
  pretty_print(result);
}
```
这里 pretty_print 是一个显示横线和一个字符串的函数。注意使用 this 指代方法所属的对象。
你可以在对象定义中通过增加下述语句将这个函数变成 car 的方法：

```
this.displayCar = displayCar;
```
因此，car 的完整定义看上去将是：

```
function Car(make, model, year, owner) {
  this.make = make;
  this.model = model;
  this.year = year;
  this.owner = owner;
  this.displayCar = displayCar;
}
```
### 通过 this 引用对象
JavaScript 有一个特殊的关键字 this，它可以在方法中使用以指代当前对象。例如，假设你有一个名为 validate 的函数，它根据给出的最大与最小值检查某个对象的 value 属性：

```
function validate(obj, lowval, hival) {
  if ((obj.value < lowval) || (obj.value > hival))
    alert("Invalid Value!");
}
```
### 定义 getters 与 setters
一个 getter 是一个获取某个特定属性的值的方法。一个  setter 是一个设定某个属性的值的方法。你可以为预定义的或用户定义的对象定义 getter 和 setter 以支持新增的属性。定义 getter 和 setter 的语法采用对象字面量语法。

下面例子描述了getters 和 setters 是如何为用户定义的对象 o 工作的。

```
var o = {
  a: 7,
  get b() { 
    return this.a + 1;
  },
  set c(x) {
    this.a = x / 2
  }
};
console.log(o.a); // 7
console.log(o.b); // 8
o.c = 50;
console.log(o.a); // 25
```
o 对象的属性如下：
* o.a — 数字
* o.b — 返回 o.a + 1 的 getter
* o.c — 由  o.c 的值所设置 o.a 值的 setter

请注意在一个对象字面量语法中定义getter和setter使用"[gs]et property()"的方式（相比较于__define[GS]etter__)时，并不是获取和设置某个属性自身，容易让人误以为是"[gs]et propertyName(){ }"这样错误的使用方法。定义一个getter或setter函数使用语法"[gs]et property()"，定义一个已经声明的函数作为的getter和setter方法，使用Object.defineProperty(或者 Object.prototype.__defineGetter__ 旧语法回退)

下面这个例子展示使用getter和setter方法扩展 Date原型，为预定义好的Date类添加一个year的属性。定义属性year的getter和setter方法用到了Date类中已存在的getFullYear和setFullYear方法。

定义属性year的getter和setter：

```
var d = Date.prototype;
Object.defineProperty(d, "year", {
  get: function() { return this.getFullYear() },
  set: function(y) { this.setFullYear(y) }
});
```
通过一个Date对象使用getter和setter:

```
var now = new Date();
console.log(now.year); // 2000
now.year = 2001; // 987617605170
console.log(now);
// Wed Apr 18 11:13:25 GMT-0700 (Pacific Daylight Time) 2001
```
```
var o = {
  a: 7,
  get b() { return this.a + 1; },
  set c(x) { this.a = x / 2; }
};
```
```
ar o = { a:0 }
Object.defineProperties(o, {
    "b": { get: function () { return this.a + 1; } },
    "c": { set: function (x) { this.a = x / 2; } }
});
o.c = 10 // Runs the setter, which assigns 10 / 2 (5) to the 'a' property
console.log(o.b) // Runs the getter, which yields a + 1 or 6
```
### 删除属性
你可以用 delete 操作符删除一个不是继承而来的属性。下面的例子说明如何删除一个属性：

```
//Creates a new object, myobj, with two properties, a and b.
var myobj = new Object;
myobj.a = 5;
myobj.b = 12;
//Removes the a property, leaving myobj with only the b property.
delete myobj.a;
```
如果一个全局变量不是用 var 关键字声明的话，你也可以用 delete 删除它：

```
g = 17;
delete g;
```
### 比较对象
在 JavaScript 中 objects 是一种引用类型。两个独立声明的对象永远也不会相等，即使他们有相同的属性，只有在比较一个对象和这个对象的引用时，才会返回true.

```
// Two variables, two distinct objects with the same properties
var fruit = {name: "apple"};
var fruitbear = {name: "apple"};
fruit == fruitbear // return false
fruit === fruitbear // return false
```
注意: "===" 运算符用来检查数值是否相等: 1 === "1" // return false and 1 == "1" // return true

```
// Two variables, a single object
var fruit = {name: "apple"};
var fruitbear = fruit;  // assign fruit object reference to fruitbear
// here fruit and fruitbear are pointing to same object
fruit == fruitbear // return true
fruit === fruitbear // return true
```

