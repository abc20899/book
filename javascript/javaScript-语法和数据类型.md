### 基础知识(Basics)
JavaScript 的很多语法借鉴自 Java，但也受 Awk，Perl 和 Python 影响。 

JavaScript 是大小写敏感的，使用 Unicode 字符集。

在JavaScript中，语句被称为 statements，并用分号（;）分隔。空格、制表符和换行符被称为空白。 
JavaScript的脚本的源文本从左到右扫描，并转换成由tokens（不可分割的词法单位），控制字符，行结束符，注释或空白组成的输入元素序列。 

### 注释（Comments）
注释语法跟 C++ 和许多其他语言相同：

```
// 单行注释

/* 这是一个多行注释
   多行注释
*/

/* 但是, 你不能, /* 嵌套注释 */ 语法错误 */
```
### 声明(Declarations)
* var

  声明变量，可选择将其初始化为一个值。
* let

  声明块范围局部变量(block scope local variable)，可选择将其初始化为一个值。
* const
  
  声明一个只读(read-only)的有名字的常量。

### 变量(Variables)

在应用程序中，使用变量来为值命名。变量的名称称为 identifiers，需要遵守一定的规则。

在 JavaScript 语言中，一个标识符(identifier)必须以字母、下划线（_）或者美元（$）符号开头；后续的字符可以包含数字（0-9）。因为 JavaScript 语言是区分大小写的，这里所指的字母可以是（大写的）“A”到“Z”和（小写的）“a”到“z”。

### 声明变量(Declaring variables)

你可以用以下三种方式声明变量：

* 使用关键词 var。例如，var x = 42。这个语法可以同时用来声明局部和全局变量。
* 直接赋值。例如，x = 42。这样就声明了一个全局变量并会导致JavaScript编译时产生一个严格警告。因而你应避免使用这种非常规格式。
* 使用关键词let。例如，let y = 13。这个语法可以用来声明语句块代码段的局部变量(block scope local variable)。

### 对变量求值(Evaluating variables)

用 var 或 let 声明的未赋初值的变量，值会被设定为undefined（译注：即未定义值，本身也是一个值）。

试图访问一个未初始化的变量会导致一个 ReferenceError 异常被抛出：

```
var a;
console.log("The value of a is " + a); // logs "的值未定义"
console.log("The value of b is " + b); // 抛出ReferenceError异常
```
你可以使用undefined来确定变量是否已赋值。以下的代码中，变量input未被赋值，因而if条件语句的求值结果是true。

```
var input;
if(input === undefined){
  doThis();
} else {
  doThat();
}
```
undefined值在布尔类型环境中会被当作false。例如，下面的代码将运行函数myFunction，因为数组myArray中的元素未被赋值：

```
var myArray = new Array();
if (!myArray[0]) myFunction();
```
数值类型环境中undefined值会被转换为NaN（译注：NaN为“Not a Number”，不是一个数字 的缩写）。

```
var a;
a + 2; // Evaluates to NaN
```
当你对一个空变量求值时，空值 null 在数值类型环境中会被当作0来对待，而布尔类型环境中会被当作false
。例如：

```
var n = null;
console.log(n * 32); // logs 0
```
### 变量的域(Variable scope)

在所有函数之外声明的变量，叫做全局变量，因为它可被当前文档中的其他代码所访问。在函数内部声明的变量，叫做局部变量，因为它只能在该函数内部访问。

ECMAScript 6 之前的JavaScript没有 语句块 作用域；相反，语句块中声明的变量将成为语句块所在代码段的局部变量。例如，如下的代码将在控制台输出 5，因为 x 的作用域是声明了 x 的那个函数（或全局范围），而不是 if 语句块。

```
if (true) {
  var x = 5;
}
console.log(x); // 5
```
如果使用 ECMAScript 6 中的 let 声明，上述行为将发生变化。
从 ECMAScript 6 开始，使用 let 定义的变量是块作用域的

```
if (true) {
  let y = 5;
}
console.log(y); // ReferenceError: y is not defined
```
### 变量声明提升(Variable hoisting)

JavaScript 变量的另一特别之处是，你可以引用稍后声明的变量而不会引发异常。这一概念称为变量声明提升(hoisting)；JavaScript 变量感觉上是被“提升”或移到了所有函数和语句之前。然而提升后的变量将返回 undefined 值。所以在使用或引用某个变量之后进行声明和初始化操作，这个被提升的引用仍将得到 undefined 值。

```
/**
 * Example 1
 */
console.log(x === undefined); // logs "true"
var x = 3;


/**
 * Example 2
 */
// will return a value of undefined
var myvar = "my value";

(function() {
  console.log(myvar); // undefined
  var myvar = "local value";
})();
```
上面的例子，也可写作：

```
/**
 * Example 1
 */
var x;
console.log(x === undefined); // logs "true"
x = 3;
 
/**
 * Example 2
 */
var myvar = "my value";
 
(function() {
  var myvar;
  console.log(myvar); // undefined
  myvar = "local value";
})();
```
由于存在变量声明提升，一个函数中所有的var语句应尽可能地放在接近函数顶部的地方。这将大大提升程序代码的清晰度。

在 ECMAScript 2015 中，let（const）将不会提升变量到代码块的顶部。因此，在变量声明之前引用这个变量，将抛出错误ReferenceError。这个变量将从代码块一开始的时候就处在一个“暂时性死区”，直到这个变量被声明为止。

```
console.log(x); // ReferenceError
let x = 3;
```
### 函数提升（Function hoisting）

对于函数，只有函数声明会被提升到顶部，而不包括函数表达式。

```
/* 函数声明 */

foo(); // "bar"

function foo() {
  console.log("bar");
}


/* 函数表达式   表达式定义的函数，成为匿名函数。匿名函数没有函数提升。*/

baz(); // TypeError: baz is not a function
//此时的"baz"相当于一个声明的变量，类型为undefined。
由于baz只是相当于一个变量，因此浏览器认为"baz()"不是一个函数。
var baz = function() {
  console.log("bar2");
};
```
### 全局变量(Global variables)

全局变量实际上是全局对象的属性。在网页中，（译注：缺省的）全局对象是 window，所以你可以用形如 window.variable的语法来设置和访问全局变量。

因此，你可以通过指定 window 或 frame 的名字，从一个 window 或 frame 访问另一个 window 或 frame 中声明的变量。例如，在文档里声明一个叫 phoneNumber 的变量，那么你就可以在子框架里使用 parent.phoneNumber 来引用它。

### 常量(Constants)

你可以用关键字 const 创建一个只读(read-only)的常量。常量标识符的命名规则和变量相同：必须以字母、下划线或美元符号开头并可以包含有字母、数字或下划线。

```
const prefix = '212';
```
常量不可以通过赋值改变其值，也不可以在脚本运行时重新声明。它必须被初始化为某个值。

常量的作用域规则与 let 块级作用域变量相同。若省略const关键字，则该标识符将被视为变量。

在同一作用域中，不能使用与变量名或函数名相同的名字来命名常量。例如：

```
// THIS WILL CAUSE AN ERROR
function f() {};
const f = 5;

// THIS WILL CAUSE AN ERROR ALSO
function f() {
  const g = 5;
  var g;

  //statements
}
```
然而,对象属性是不受保护的,所以可以使用如下语句来执行。

```
const MY_OBJECT = {"key": "value"};
MY_OBJECT.key = "otherValue";
```
### 数据结构和类型

数据类型

JavaScript语言可以识别下面 7 种不同类型的值：

* 六种 原型 数据类型:
   
   1.Boolean.  布尔值，true 和 false.
   
   2.null. 一个表明 null 值的特殊关键字。 JavaScript 是大小写敏感的，因此 null 与 Null、NULL或其他变量完全不同。
   
   3.undefined.  变量未定义时的属性。
   
   4.Number.  表示数字，例如： 42 或者 3.14159。
   
   5.String.  表示字符串，例如："Howdy"
   
   6.Symbol ( 在 ECMAScript 6 中新添加的类型).。一种数据类型，它的实例是唯一且不可改变的。
 
 * 以及 Object 对象
 
仅凭这些为数不多的数据类型，你就可以在你的应用程序中执行有用的功能。

Objects 和 functions 是本语言的其他两个基本要素。你可以将对象视为存放值的命名容器，而将函数视为你的应用程序能够执行的过程(procedures)。

### 数据类型的转换(Data type conversion)

JavaScript是一种动态类型语言(dynamically typed language)。这意味着你声明变量时可以不必指定数据类型，而数据类型会在脚本执行时根据需要自动转换。因此，你可以这样来定义变量：

```
var answer = 42; 
```
然后，你还可以给同一个变量赋予一个字符串值，例如：

```
answer = "Thanks for all the fish...";
```
因为 JavaScript 是动态类型的，这样赋值并不会提示出错。

在涉及加法运算符(+)的数字和字符串表达式中，JavaScript 会把数字值转换为字符串。例如，假设有如下的语句：

```
x = "The answer is " + 42 // "The answer is 42"
y = 42 + " is the answer" // "42 is the answer"
```
在涉及其它运算符（译注：如下面的减号'-'）时，JavaScript语言不会把数字变为字符串。例如（译注：第一例是数学运算，第二例是字符串运算）：

```
"37" - 7 // 30
"37" + 7 // "377"
```
* 字符串转换为数字(converting strings to numbers)

  有一些方法可以将内存中表示一个数字的字符串转换为对应的数字

  parseInt()和parseFloat()

  parseInt 仅能够返回整数，所以使用它会丢失小数部分。另外，调用     parseInt 时最好总是带上进制(radix) 参数，这个参数用于指定使用哪一种进制。
  
* 单目加法运算符
  
  将字符串转换为数字的另一种方法是使用单目加法运算符。
  
  ```
  "1.1" + "1.1" = "1.11.1"
(+"1.1") + (+"1.1") = 2.2   // 注：加入括号为清楚起见，不是必需的。
```  

### 字面值(Literals)

（译注：字面值是由语法表达式定义的常量；或，通过由一定字词组成的语词表达式定义的常量）

在JavaScript中，你可以使用各种字面值。这些字面值是脚本中按字面意思给出的固定的值，而不是变量。（译注：字面值是常量，其值是固定的，而且在程序脚本运行中不可更改，比如false，3.1415，thisIsStringOfHelloworld ，invokedFunction: myFunction("myArgument")。本节将介绍以下类型的字面值：

* 数组字面值(Array literals)

  数组字面值是一个封闭在方括号对([])中的包含有零个或多个表达式的列表，其中每个表达式代表数组的一个元素。当你使用数组字面值创建一个数组时，该数组将会以指定的值作为其元素进行初始化，而其长度被设定为元素的个数。

下面的示例用3个元素生成数组coffees，它的长度是3。

```
var coffees = ["French Roast", "Colombian", "Kona"];

var a=[3];

console.log(a.length); // 1

console.log(a[0]); // 3
```
注意 这里的数组字面值也是一种对象初始化器。

若在顶层（全局）脚本里用字面值创建数组，JavaScript语言将会在每次对包含该数组字面值的表达式求值时解释该数组。另一方面，在函数中使用的数组，将在每次调用函数时都会被创建一次。

数组字面值同时也是数组对象。

* 数组字面值中的多余逗号
  
  （译注：声明时）你不必列举数组字面值中的所有元素。若你在同一行中连写两个逗号（,），数组中就会产生一个没有被指定的元素，其初始值是undefined。以下示例创建了一个名为fish的数组：

```
var fish = ["Lion", , "Angel"];
```

在这个数组中，有两个已被赋值的元素，和一个空元素（fish[0]是"Lion"，fish[1]是undefined，而fish[2]是"Angel"；译注：此时数组的长度属性fish.length是3)。

如果你在元素列表的尾部添加了一个逗号，它将会被忽略。在下面的例子中，数组的长度是3，并不存在myList[3]这个元素（译注：这是指数组的第4个元素噢，作者是在帮大家复习数组元素的排序命名方法）。元素列表中其它所有的逗号都表示一个新元素（的开始）。

注意：尾部的逗号在早期版本的浏览器中会产生错误，因而编程时的最佳实践方式就是移除它们。

(译注：而“现代”的浏览器似乎鼓励这种方式，因为好多网页中都这么写？)

```
var myList = ['home', , 'school', ];
```

在下面的例子中，数组的长度是4，元素myList[0]和myList[2]缺失（译注：没被赋值，因而是undefined）。

```
var myList = [ , 'home', , 'school'];
```

再看一个例子。在这里，该数组的长度是4，元素myList[1]和myList[3]被漏掉了。（但是）只有最后的那个逗号被忽略。

```
var myList = ['home', , 'school', , ];
```

理解多余的逗号（在脚本运行时会被如何处理）的含义，对于从语言层面理解JavaScript是十分重要的。但是，在你自己写代码时：显式地将缺失的元素声明为undefined，将大大提高你的代码的清晰度和可维护性。

* 布尔字面值(Boolean literals)

  （译注：即逻辑字面值）

布尔类型有两种字面值：true和false。

不要混淆作为布尔对象的真和假与布尔类型的原始值true和false。布尔对象是原始布尔数据类型的一个包装器。

* 整数(Intergers)

  （译注：原文如此，没写成“整数字面值”，这里指的是整数字面值。）

整数可以被表示成十进制（基数为10）、十六进制（基数为16）以及八进制（基数为8）。

    1.十进制整数字组成的数字序列，不带前导0。

    2.带前导0、0O、0o 的整数字面值表明它是八进制。八进制整数只能包括数字0-7。

    3.前缀0x或0X表示十六进制。十六进制整数，可以包含数字（0-9）和字母a~f或A~F。

    4.前缀0b或0B表示二进制。二进制整数，可以包含的只有0和1。

八进制整数字面值。在ECMA-262，第3版标准（严格模式下） 中被弃用并移除。不过JavaScript 1.5为了后向兼容仍然保留了支持。

整数字面值例子如下：

```
0, 117 and -345 (decimal, base 10)
015, 0001 and -077 (octal, base 8) 
0x1123, 0x00111 and -0xF1A7 (hexadecimal, "hex" or base 16)
```
* 浮点数字面值(Floating-point literals)

  浮点数字面值可以有以下的组成部分：

  1. 一个十进制整数，它可以带符号（即前面的“+”或“ - ”号），

  2.一个小数点（“.”），

  3.一个小数部分（由一串十进制数表示），
  
  4.一个指数部分。
指数部分是以“e”或“E”开头后面跟着一个整数，可以有正负号（即前面写“+”或“-”）。一个浮点数字面值必须至少有一位数字，后接小数点或者“e”（大写“E”也可）组成。

一些浮点数字面值的例子，如3.1415，-3.1E13，.1e12以及2E-12。

简言之，其语法是：

```
[(+|-)][digits][.digits][(E|e)][(+|-)]digits]
```
例如：

```
3.14      
-.2345789 // -0.23456789
-3.12e+12  // -3.12*1012
.1e-23    // 0.1*10-23=10-24=1e-24
```
* 对象字面值(Object literals)

  对象字面值是封闭在花括号对({})中的一个对象的零个或多个"属性名-值"对的（元素）列表。你不能在一条语句的开头就使用对象字面值，这将导致错误或产生超出预料的行为， 因为此时左花括号（{）会被认为是一个语句块的起始符号。（译者：这 里需要对语句statement、块block等基本名词的解释）

以下是一个对象字面值的例子。对象car的第一个元素（译注：即一个属性/值对）定义了属性myCar；第二个元素，属性getCar，引用了一个函数（即CarTypes("Honda")）；第三个元素，属性special，使用了一个已有的变量（即Sales）。

```
var Sales = "Toyota";

function CarTypes(name) {
  return (name === "Honda") ?
    name :
    "Sorry, we don't sell " + name + "." ;
}

var car = { myCar: "Saturn", getCar: CarTypes("Honda"), special: Sales };

console.log(car.myCar);   // Saturn
console.log(car.getCar);  // Honda
console.log(car.special); // Toyota
```
更进一步的，你可以使用数字或字符串字面值作为属性的名字，或者在另一个字面值内嵌套上一个字面值。如下的示例中使用了这些可选项。

```
var car = { manyCars: {a: "Saab", "b": "Jeep"}, 7: "Mazda" };

console.log(car.manyCars.b); // Jeep
console.log(car[7]); // Mazda
```
对象属性名字可以是任意字符串，包括空串。如果对象属性名字不是合法的javascript标识符，它必须用""包裹。属性的名字不合法，那么便不能用.访问属性值，而是通过类数组标记("[]")访问和赋值。

```
var unusualPropertyNames = {
  "": "An empty string",
  "!": "Bang!"
}
console.log(unusualPropertyNames."");   // 语法错误: Unexpected string
console.log(unusualPropertyNames[""]);  // An empty string
console.log(unusualPropertyNames.!);    // 语法错误: Unexpected token !
console.log(unusualPropertyNames["!"]); // Bang!
```
请注意：

```
var foo = {a: "alpha", 2: "two"};
console.log(foo.a);    // alpha
console.log(foo[2]);   // two
//console.log(foo.2);  // Error: missing ) after argument list
//console.log(foo[a]); // Error: a is not defined
console.log(foo["a"]); // alpha
console.log(foo["2"]); // two
```
在ES2015，对象字面值扩展支持在创建时设置原型，简写foo：foo分配，定义方法，加工父函数（super calls），计算属性名(动态)。总之，这些也带来了对象字面值和类声明紧密联系起来，让基于对象的设计得益于一些同样的便利。

```
var obj = {
    // __proto__
    __proto__: theProtoObj,
    // Shorthand for ‘handler: handler’
    handler,
    // Methods
    toString() {
     // Super calls
     return "d " + super.toString();
    },
    // Computed (dynamic) property names
    [ 'prop_' + (() => 42)() ]: 42
};
```
* RegExp 字面值

  一个正则表达式是字符被斜线（译注：正斜杠“/”）围成的表达式。下面是一个正则表达式文字的一个例子。
  
  ```
  var re = /ab+c/;
  ```
* 字符串字面值(String literals)
  
  字符串字面值是由双引号（"）对或单引号（‘）包围的零个或多个字符。字符串被限定在同种引号之间；也即，必须是成对单引号或成对双引号。下面的例子都是字符串字面值：
  
  ```
  "foo"
'bar'
"1234"
"one line \n another line"
"John's cat"
```
你可以在字符串字面值上使用字符串对象的所有方法——JavaScript会自动将字符串字面值转换为一个临时字符串对象，调用该方法，然后废弃掉那个临时的字符串对象。你也能用对字符串字面值使用类似String.length的属性：

```
console.log("John's cat".length) 
// 将打印字符串中的字符个数（包括空格） 
// 结果为：10
```
除非有特别需要使用字符串对象，否则,你应当始终使用字符串字面值。

在字符串中使用的特殊字符

作为一般字符的扩展，你可以在字符串中使用特殊字符，如下例所示。

```
"one line \n another line"
```
转义字符

通过在引号前加上反斜线'\'，可以在字符串中插入引号，这就是引号转义。例如:

```
var quote = "He read \"The Cremation of Sam McGee\" by R.W. Service.";
console.log(quote);
```
代码的运行结果为:

```
He read "The Cremation of Sam McGee" by R.W. Service.
```
要在字符串中插入'\'字面值，必须转义反斜线。例如，要把文件路径 c:\temp 赋值给一个字符串，可以采用如下方式:

```
var home = "c:\\temp";
```
也可以在换行之前加上反斜线以转义换行（译注：实际上就是一条语句拆成多行书写），这样反斜线和换行都不会出现在字符串的值中。

```
var str = "this string \
is broken \
across multiple\
lines."
console.log(str);   // this string is broken across multiplelines.
```
Javascript没有“heredoc”语法，但可以用行末的换行符转义和转义的换行来近似实现 

```
var poem = 
"Roses are red,\n\
Violets are blue.\n\
I'm schizophrenic,\n\
And so am I."
```





   

