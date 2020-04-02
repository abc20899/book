### 定义函数(Defining function)

一个函数的定义（也称为函数的声明）由一系列的函数关键词组成, 依次为：

* 函数的名称。
* 函数参数列表，包围在括号( )中并由逗号( , )区隔。
* 函数功能，包围在花括号{ }中，用于定义函数功能的一些JavaScript语句。

```
function square(number) {
  return number * number;
}
```

原始参数（比如一个具体的数字）被作为值传递给函数(pass to function by value)；值被传递给函数，如果被调用函数改变了这个参数的值，这样的改变不会影响到全局或调用的函数。

如果你传递一个对象(pass an object)（即一个非原始值(non-primitive value)，例如Array或用户自定义的其它对象）作为参数，而函数改变了这个对象的属性，这样的改变对函数外部是可见的，如下面的例子所示：

```
function myFunc(theObject) {
  theObject.make = "Toyota";
}

var mycar = {make: "Honda", model: "Accord", year: 1998},
var x, y;

x = mycar.make;     // x 获取的值为 "Honda"

myFunc(mycar);
y = mycar.make;     // y 获取的值为 "Toyota"
                    // (make属性的值在函数中被改变了)
```
### 函数表达式(function expression)

当然上述函数定义都用的是语法语句，函数也同样可以由函数表达式创建。这样的函数可以是匿名的；它不必有名称。例如，上面提到的函数square也可这样来定义：

```
var square = function(number) {
  return number * number
};
var x = square(4); // x 得到的值为16
```
然而，函数表达式也可以提供函数名，并且可以用于在函数内部使用来代指其本身，或者在调试器堆栈跟踪中鉴别该函数：

```
var factorial = function fac(n) {return n<2 ? 1 : n*fac(n-1)};

console.log(factorial(3));
```
函数表达式在将函数作为一个引数传递给其它函数时十分方便。下面的例子演示了一个叫map的函数如何被定义，而后调用一个匿名函数作为其第一个参数：

```
function map(f,a) {
  var result = [], // 创建一个新的数组
      i;

  for (i = 0; i != a.length; i++)
    result[i] = f(a[i]);
  return result;
}
```
下面的代码：

```
map(function(x) {return x * x * x}, [0, 1, 2, 5, 10]);
```
返回 [0, 1, 8, 125, 1000]。

在JavaScript中，可以根据条件来定义一个函数。 比如下面的代码，当num等于0的时候才会定义 myFunc ：

```
var myFunc;
if (num == 0){
  myFunc = function(theObject) {
    theObject.make = "Toyota"
  }
}
```
除了上述的定义函数方法外，你也可以在运行时用 Function 构造器由一个字符串来创建一个函数 ，很像 eval() 函数。

当一个对象的属性是函数时，其称之为方法。

### 调用函数(Calling function)

定义一个函数并不会自动的执行它。定义了函数仅仅是赋予函数以名称并明确函数被调用时该做些什么。调用函数才会以给定的参数真正执行这些动作。例如，一旦你定义了函数square，你可以如下这样调用它

square(5);
函数一定要处于调用它们的域中，但是函数的声明可以在它们的调用语句之后，如下例：

```
console.log(square(5));
/* ... */
function square(n) { return n*n }
```
函数域是指函数声明时的所在的地方，或者函数在顶级被声明时指整个程序。

注意： 注意只有使用如上的语法形式（即如function funcName(){}）才可以。而下面的代码是无效的。

```
console.log(square(5)); // square is not defined
square = function (n) {
  return n * n;
}
```
函数可以被递归；就是说函数可以调用其本身。例如，下面这个函数计算递归的阶乘值：

```
function factorial(n){
  if ((n == 0) || (n == 1))
    return 1;
  else
    return (n * factorial(n - 1));
}
```
你可以在其后计算下面5个阶乘值：

```
var a, b, c, d, e;

a = factorial(1); // 1赋值给a
b = factorial(2); // 2赋值给b
c = factorial(3); // 6赋值给c
d = factorial(4); // 24赋值给d
e = factorial(5); // 120赋值给e
```
还有其它的方式来调用函数。常见的一些情形是某些地方需要动态调用函数，或者函数的实参数量是变化的，或者在运行时(runtime)调用函数的上下文(context)需要指定为特定的对象。显然，函数本身就是对象，因此这些对象也有方法（参考Function ）。作为此中情形之一，apply()方法可以实现这些目的。

### 函数的作用域(Function scope)

在函数内定义的变量不能从函数之外的任何地方取得，因为变量仅仅在该函数的域的内部有定义。相对应的，一个函数可以取得在它的域中定义的任何变量和子函数。换言之，定义在全局域中的函数可以取得所有定义在全局域中的变量。而定义在一个函数内部的子函数可以取得定义在其父函数内的，或其父函数取得的任何变量。

```
// 下面的变量定义在全局作用(global scope)域中
var num1 = 20,
    num2 = 3,
    name = "Chamahk";

// 本函数定义在全局作用域
function multiply() {
  return num1 * num2;
}

multiply(); // Returns 60

// 嵌套函数的例子
function getScore () {
  var num1 = 2,
      num2 = 3;
  
  function add() {
    return name + " scored " + (num1 + num2);
  }
  
  return add();
}

getScore(); // Returns "Chamahk scored 5"
```
### 嵌套函数和闭包(nested functions and closures)

你可以在一个函数里面嵌套另外一个函数。嵌套(nest)（内部, inner）函数是容器(containing)（外部, outer）函数的私有成员。它自身也形成了一个闭包(closure)。一个闭包是一个可以自己拥有独立的环境与变量的的表达式（通常是函数）。

既然嵌套函数是一个闭包，就意味着一个嵌套函数可以继承容器函数的参数和变量。换句话说，内部函数包含外部函数的作用域。

可以总结如下：

* 内部函数只可以在外部函数中访问
* 内部函数形成了一个闭包：它可以访问外部函数的参数和变量，但是外部函数却不能使用它的参数和变量

下面的例子展示了嵌套函数：

```
function addSquares(a,b) {
  function square(x) {
    return x * x;
  }
  return square(a) + square(b);
}
a = addSquares(2,3); // returns 13
b = addSquares(3,4); // returns 25
c = addSquares(4,5); // returns 41
```
因为内部函数形成了闭包，你可以调用外部函数并且指定外部和内部函数的参数：

```
function outside(x) {
  function inside(y) {
    return x + y;
  }
  return inside;
}
// Think of it like: give me a function that adds 3 to whatever you give it
fn_inside = outside(3); 
result = fn_inside(5); // returns 8

result1 = outside(3)(5); // returns 8
```
### 多层嵌套函数(multiply-nested functions)

函数可以被多层嵌套。例如，函数A可以包含函数B，函数B可以再包含函数C。B和C都形成了闭包，所以B可以访问A，C可以访问B和A。因此，闭包可以包含多个作用域；他们递归式的包含了所有包含它的函数作用域。这个称之为域链(scope chaining)。（稍后会详细解释）

思考一下下面的例子：

```
function A(x) {
  function B(y) {
    function C(z) {
      console.log(x + y + z);
    }
    C(3);
  }
  B(2);
}
A(1); // 控制台输出 6 (1 + 2 + 3)
```
在这个例子里面，C可以访问B的y和A的x。这是因为：

1.B形成了一个包含A的闭包，B可以访问A的参数和变量

2.C形成了一个包含B的闭包

3.B包含A，所以C也包含A，C可以访问B和A的参数和变量。换言之，C用这个顺序链接了B和A的作用域

反过来却不是这样。A不能访问C，因为A看不到B中的参数和变量，C是B中的一个变量，所以C是B私有的。

### 命名冲突
当同一个闭包作用域下两个参数或者变量同名时，就会产生命名冲突。更近的作用域有更高的优先权，所以最近的优先级最高，最远的优先级最低。这就是作用域链。链的第一个元素就是最里面的作用域，最后一个元素便是最外层的作用域。

看以下的例子：

```
function outside() {
  var x = 10;
  function inside(x) {
    return x;
  }
  return inside;
}
result = outside()(20); // returns 20 instead of 10
```
命名冲突发生在return x上，inside的参数x和外部变量x发生了冲突。这里的作用链域是{inside, outside, 全局对象}。因此inside具有最高优先权，返回了传入的20而不是外部函数的变量值10。

### 闭包(Closures)

闭包是JavaScript中最强大的特性之一。JavaScript允许函数嵌套，并且内部函数可以访问定义在外部函数中的所有变量和函数，以及外部函数能访问的所有变量和函数。但是，外部函数却不能够访问定义在内部函数中的变量和函数。这给内部函数的变量提供了一定的安全性。而且，当内部函数生存周期大于外部函数时，由于内部函数可以访问外部函数的作用域，定义在外部函数的变量和函数的生存周期就会大于外部函数本身。当内部函数以某一种方式被任何一个外部函数作用域访问时，一个闭包就产生了。

```
var pet = function(name) {          //外部函数定义了一个变量"name"
  var getName = function() {            
    //内部函数可以访问 外部函数定义的"name"
    return name; 
  }
  //返回这个内部函数，从而将其暴露在外部函数作用域
  return getName;               
};
myPet = pet("Vivie");
    
myPet();                            // 返回结果 "Vivie"
```
实际上可能会比上面的代码复杂的多。在下面这种情形中，返回了一个包含可以操作外部函数的内部变量方法的对象。

```
var createPet = function(name) {
  var sex;
  
  return {
    setName: function(newName) {
      name = newName;
    },
    
    getName: function() {
      return name;
    },
    
    getSex: function() {
      return sex;
    },
    
    setSex: function(newSex) {
      if(typeof newSex == "string" 
        && (newSex.toLowerCase() == "male" || newSex.toLowerCase() == "female")) {
        sex = newSex;
      }
    }
  }
}

var pet = createPet("Vivie");
pet.getName();                  // Vivie

pet.setName("Oliver");
pet.setSex("male");
pet.getSex();                   // male
pet.getName();                  // Oliver
```
在上面的代码中，外部函数的name变量对内嵌函数来说是可取得的，而除了通过内嵌函数本身，没有其它任何方法可以取得内嵌的变量。内嵌函数的内嵌变量就像内嵌函数的保险柜。它们会为内嵌函数保留“稳定”——而又安全——的数据参与运行。而这些内嵌函数甚至不会被分配给一个变量，或者不必一定要有名字。

```
var getCode = (function(){
  var secureCode = "0]Eal(eh&2";    // A code we do not want outsiders to be able to modify...
  
  return function () {
    return secureCode;
  };
})();

getCode();    // Returns the secret code
```
尽管有上述优点，使用闭包时仍然要小心避免一些陷阱。如果一个闭包的函数用外部函数的变量名定义了同样的变量，那在外部函数域将再也无法指向该变量。

```
var createPet = function(name) {  // Outer function defines a variable called "name"
  return {
    setName: function(name) {    // Enclosed function also defines a variable called "name"
      name = name;               // ??? How do we access the "name" defined by the outer function ???
    }
  }
}
```
闭包中的神奇变量this是非常诡异的。使用它必须十分的小心，因为this指代什么完全取决于函数在何处被调用，而不是在何处被定义。一篇绝妙而详尽的关于闭包的文章可以在这里找到。

### 使用arguments对象

函数的实际参数会被保存在一个类似数组的arguments对象中。在函数内，你可以按如下方式找出传入的引数：

arguments[i]

其中i是引数的序数编号，以0开始。所以第一个传来的参数会是arguments[0]。参数的数量由arguments.length表示。

使用arguments对象，你可以处理比声明的更多的参数来调用函数。这在你事先不知道会需要将多少参数传递给函数时十分有用。你可以用arguments.length来获得实际传递给函数的参数的数量，然后用arguments对象来取得每个参数。

例如，设想有一个用来连接字符串的函数。唯一事先确定的参数是在连接后的字符串中用来分隔各个连接部分的字符（译注：比如例子里的分号“；”）。该函数定义如下：

```
function myConcat(separator) {
   var result = "", // initialize list
       i;
   // iterate through arguments
   for (i = 1; i < arguments.length; i++) {
      result += arguments[i] + separator;
   }
   return result;
}
```
你可以给这个函数传递任意数量的参数，它会将各个参数连接成一个字符串“列表”：

```
// returns "red, orange, blue, "
myConcat(", ", "red", "orange", "blue");

// returns "elephant; giraffe; lion; cheetah; "
myConcat("; ", "elephant", "giraffe", "lion", "cheetah");

// returns "sage. basil. oregano. pepper. parsley. "
myConcat(". ", "sage", "basil", "oregano", "pepper", "parsley");
```
注意： arguments 变量只是 ”类数组对象“，并不是一个数组。称其为类数组对象是说它有一个索引编号和Length属性。尽管如此，它并不拥有全部的Array对象的操作方法。

### 函数参数(Function parameter)

从ECMAScript 6开始，有两个新的类型的参数：默认参数(default parameters)，剩余参数(rest parameters)。

* 默认参数(default parameter)

  在JavaScript中，函数参数的默认值是undefined。然而，在某些情况下设置不同的默认值是有用的。这时默认参数可以提供帮助。

  在过去，用于设定默认的一般策略是在函数的主体测试参数值是否为undefined，如果是则赋予一个值。如果在下面的例子中，调用函数时没有实参传递给b，那么它的值就是undefined，于是计算a*b得到、函数返回的是 NaN：

```
function multiply(a, b) {
  b = typeof b !== 'undefined' ?  b : 1;

  return a*b;
}

multiply(5); // 5
```
使用默认参数，在函数体的检查就不再需要了。现在，你可以在函数头简单地把1设定为b的默认值：

```
function multiply(a, b = 1) {
  return a*b;
}

multiply(5); // 5
```
* 剩余参数(rest parameters)
  剩余参数语法允许将不确定数量的参数表示为数组。在下面的例子中，使用剩余参数收集从第二个到最后参数。然后，我们将这个数组的每一个数与第一个参数相乘。这个例子是使用了一个箭头函数，这将在下一节介绍。
  
  ```
  function multiply(multiplier, ...theArgs) {
     return theArgs.map(x => multiplier * x);
  }

   var arr = multiply(2, 1, 2, 3);
   console.log(arr); // [2, 4, 6]
```
### 箭头函数(Arrow functions)

箭头函数表达式（也称胖箭头函数, fat arrow function）具有较短的语法相比函数表达式和词法绑定此值。箭头函数总是匿名的。也看到这个hacks.mozilla.org 博客文章：“深度了解ES6：箭头函数”。

有两个因素会影响介绍箭头函数：更简洁的函数和this。

* 更简洁的函数

  在一些功能性的模式，更简洁的函数是受欢迎的。比如下面：

  ```
  var a = [
  "Hydrogen",
  "Helium",
  "Lithium",
  "Beryl­lium"
   ];

   var a2 = a.map(function(s){ return s.length });

   var a3 = a.map( s => s.length );
```
 * this的词法  
   在箭头函数出现之前，每一个新函数都重新定义了自己的this值（在严格模式下，一个新的对象在构造函数里是未定义的，通过上下文对象调用的函数被称为“对象方法”等）。面向对象的编程风格着实有点恼人。

 ```
 function Person() {
  // The Person() constructor defines `this` as itself.
  this.age = 0;

  setInterval(function growUp() {
    // In nonstrict mode, the growUp() function defines `this` 
    // as the global object, which is different from the `this`
    // defined by the Person() constructor.
    this.age++;
  }, 1000);
}

var p = new Person();
```
在ECMAScript 3/5里，通过把this的值赋值给一个变量可以修复这个问题。

```
function Person() {
  var self = this; // Some choose `that` instead of `self`. 
                   // Choose one and be consistent.
  self.age = 0;

  setInterval(function growUp() {
    // The callback refers to the `self` variable of which
    // the value is the expected object.
    self.age++;
  }, 1000);
}
```
另外，创建一个约束函数(bound function)可以使得this值被正确传递给growUp()函数。

箭头功能捕捉闭包上下文的this值，所以下面的代码工作正常。

```
function Person(){
  this.age = 0;

  setInterval(() => {
    this.age++; // |this| properly refers to the person object
  }, 1000);
}

var p = new Person();
```
### 预定义函数(Predefined functions)

JavaScript语言有好些个顶级的内建函数：

eval()
eval()方法会对一串字符串形式的JavaScript代码字符求值。

uneval() 
uneval()方法创建的一个Object的源代码的字符串表示。

isFinite()
isFinite()函数判断传入的值是否是有限的数值。 如果需要的话，其参数首先被转换为一个数值。

isNaN()
isNaN()函数判断一个值是否是NaN。注意： isNaN函数内部的强制转换规则十分有趣； 另一个可供选择的是ECMAScript 6 中定义Number.isNaN() , 或者使用 typeof 来判断数值类型。

parseFloat()
parseFloat() 函数解析字符串参数，并返回一个浮点数。

parseInt()
parseInt() 函数解析字符串参数，并返回指定的基数（基础数学中的数制）的整数。

decodeURI()
decodeURI() 函数对先前经过encodeURI函数或者其他类似方法编码过的字符串进行解码。

decodeURIComponent()
decodeURIComponent()方法对先前经过encodeURIComponent函数或者其他类似方法编码过的字符串进行解码。

encodeURI()
encodeURI()方法通过用以一个，两个，三个或四个转义序列表示字符的UTF-8编码替换统一资源标识符（URI）的某些字符来进行编码（每个字符对应四个转义序列，这四个序列组了两个”替代“字符）。

encodeURIComponent()
encodeURIComponent() 方法通过用以一个，两个，三个或四个转义序列表示字符的UTF-8编码替换统一资源标识符（URI）的每个字符来进行编码（每个字符对应四个转义序列，这四个序列组了两个”替代“字符）。

escape() 
已废弃的 escape() 方法计算生成一个新的字符串，其中的某些字符已被替换为十六进制转义序列。使用 encodeURI或者encodeURIComponent替代本方法。

unescape() 
已废弃的 unescape() 方法计算生成一个新的字符串，其中的十六进制转义序列将被其表示的字符替换。上述的转义序列就像escape里介绍的一样。因为 unescape 已经废弃，建议使用decodeURI()或者decodeURIComponent 替代本方法。

https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Guide/Numbers_and_dates



                    
