### 语句块（Block Statement）

大多数程序都使用语句块来给语句分组，这样可以使语句的结构清晰明了。我们使用一对花括号（ {} ）来分组语句块，如下所示：

```
{
   statement_1;   statement_2;
   statement_3;
   ...
   statement_n;
}
```

语句块通常用于流程控制，如 if, for, while等等。

```
while (x < 10){
  x++;
}
```
注意：在ECMAScript 6标准之前，Javascript没有块作用域。如果你在块的外部声明了一个变量，然后在块中声明了一个相同变量名的变量，并赋予不同的值。那么在程序执行中将会使用块中的值，这样做虽然是合法的，但是这不同于JAVA与C。示例：

```
var x = 1;
{
  var x = 2;   //块中用let声明
}
alert(x); // 输出的结果为 2
```
这段代码的输出是2，这是因为 var x = 2 的作用范围与 var x = 1 的作用范围相同，在C语言或是Java语言中，同样的代码输出的结果是1。

从 ECMAScript 6 开始，使用 let 定义的变量是块作用域的。 

<!--more-->

### 条件判断语句（Conditional Statements）

条件判断语句指的是根据指定的条件所返回的结果（真或假或其它预定义的），来执行特定的语句。JavaScript提供了两种条件判断语句：if...else 和 switch。

if...else 语句

当一个逻辑条件为真，用if语句执行一个语句。当这个条件为假，使用可选择的else从句来执行这个语句。if语句如下所示：

```
if (condition) {
  statement_1;
}
[else {
  statement_2;
}] //推荐使用严格的语句块模式，语句else可选
```
条件可以是任何返回结果是 true 或 false的表达式。如果条件表达式返回的是 true，statement_1 会被执行；否则，statement_2 被执行。statement_1 和 statement_2 可以是任何语句，甚至你可以将另一个if语句嵌套其中。 

你也可以组合语句通过使用 else if 来测试连续的多种条件判断，就像下面这样:

```
if (condition_1) {
  statement_1;
}
[else if (condition_2) {
  statement_2;
}]
...
[else if (condition_n_1) {
  statement_n_1;
}]
[else {
  statement_n;
}]
```

要执行多个语句，可以使用语句块({ ... }) 来分组这些语句。一般情况下，总是使用语句块是一个好的习惯，特别是在代码涉及比较多的 if 语句时:

```
if (condition) {
  statement_1_runs_if_condition_is_true;
  statement_2_runs_if_condition_is_true;
} else {
  statement_3_runs_if_condition_is_false;
  statement_4_runs_if_condition_is_false;
}
```
在条件表达式中最好不要使用“=”来判断条件是否相等，因为这会产生非预期结果。不要使用下面的代码：

```
if (x = y) {
  /* do the right thing */
}
```
如果你需要在条件表达式中使用赋值，通常在赋值语句前后额外添加一对括号。例如：

```
if ((x = y)) {
  /* do the right thing */
}
```
下面这些值将被计算出 false (also known as Falsy values):

false
undefined
null
0
NaN
空字符串 ("")

当传递给条件语句时，所有其他值，包括所有对象会被计算为 true 。

请不要混淆原始的布尔值true和false 与 布尔对象的值true和false（译者注：下例中b属于对象，会被计算为true！）。例如：

```
var b = new Boolean(false);
if (b) // this condition evaluates to true
if (b == true) // this condition evaluates to false
```
例如
在下面的例子中，如果一个文本对象中的字符串长度是3，函数checkData返回true；否则，函数显示一个alert的弹出框消息并返回false。

```
function checkData() {
  if (document.form1.threeChar.value.length == 3) {
    return true;
  } else {
    alert("Enter exactly three characters. " +
      document.form1.threeChar.value + " is not valid.");
    return false;
  }
}
```
### switch 语句（Switch Statement）

switch语句允许一个程序求一个表达式的值并且尝试去匹配表达式的值到一个case 标签。如果匹配成功，这个程序执行相关的语句。 switch 语句如下所示：

```
switch (expression) {
   case label_1:
      statements_1
      [break;]
   case label_2:
      statements_2
      [break;]
   ...
   default:
      statements_def
      [break;]
}
```
程序首先查找一个与 expression 匹配的 case 语句，然后将控制权转移到该子句，执行相关的语句。如果没有匹配值， 程序会去找 default 语句，如果找到了，控制权转移到该子句，执行相关的语句。如果没有找到 default，程序会继续执行 switch 语句后面的语句。default 语句通常出现在switch语句里的最后面，当然这不是必须的。

可选的 break 语句与每个 case 语句相关联， 保证在匹配的语句被执行后程序可以跳出 switch 并且继续执行 switch 后面的语句。如果break被忽略，则程序将继续执行switch语句中的下一条语句。

示例
在如下示例中, 如果 fruittype 等于 "Bananas", 程序匹配到对应 "Bananas" 的case 语句，并执行相关语句。 当执行到 break 时，程序结束了 switch 并执行 switch 后面的语句。 如果不写 break ，那么程序将会执行 case "Cherries" 下的语句。

```
switch (fruittype) {
   case "Oranges":
      document.write("Oranges are $0.59 a pound.<br>");
      break;
   case "Apples":
      document.write("Apples are $0.32 a pound.<br>");
      break;
   case "Bananas":
      document.write("Bananas are $0.48 a pound.<br>");
      break;
   case "Cherries":
      document.write("Cherries are $3.00 a pound.<br>");
      break;
   case "Mangoes":
   case "Papayas":
      document.write("Mangoes and papayas are $2.79 a pound.<br>");
      break;
   default:
      document.write("Sorry, we are out of " + fruittype + ".<br>");
}
document.write("Is there anything else you'd like?<br>");
```
### 循环语句（Loop Statement）

循环语句是一系列反复执行直到符合特定条件的命令。JavaScript 支持 for, do while, while这些循环语句，还有Label (label 本身不是一个循环语句，但是经常和这些语句一起使用)。另外，你可以在循环语句中使用break和continue 语句 。

另一个语句：for...in也反复执行语句，但它是用来操作对象的。
for语句（for Statement）

for 反复循环直到一个特定的条件计算为假。JavaScript中的循环和Java以及C中的循环相似。for语句如下所示：

```
for ([initialExpression]; [condition]; [incrementExpression])
   statement
```
在一个for 执行的过程中，会发生以下事情：

1.[initialExpression]：初始化表达式，若存在则执行。此表达式通常初始化了一个或多个循环用计数器，语法上也允许设定一个任意复杂度的表达式。表达式里还可以声明变量。

2.[condition]：条件表达式。如果表达式的值为true，将执行循环语句；若为flase，循环终止。若要完全忽略此条件表达式，则设此表达式的值为true。

3.statement：需执行的语句。如果要执行多条语句，就要用中括号（{...}）把语句括起来。

4.[incrementExpression]：累计表达式。若存在则执行，然后会回到第2步执行语句。

下面的这个函数包含了一个for语句，用来计算一个选择列表（一个可以多选的选择列表）中被选择项目的数量。这个for语句定义了一个初始化值为0的变量i，它检查i小于选择列表的项目数量，然后执行了for循环里面的if语句，每次循环后i则自动加 1。 

```
<script type="text/javascript">

function howMany(selectObject) {
   var numberSelected = 0;
   for (var i = 0; i < selectObject.options.length; i++) {
      if (selectObject.options[i].selected)
         numberSelected++;
   }
   return numberSelected;
}

</script>
<form name="selectForm">
   <p>
      <strong>Choose some music types, then click the button below:</strong>
      <br/>
      <select name="musicTypes" multiple="multiple">
         <option selected="selected">R&B</option>
         <option>Jazz</option>
         <option>Blues</option>
         <option>New Age</option>
         <option>Classical</option>
         <option>Opera</option>
      </select>
   </p>
   <p>
      <input type="button" value="How many are selected?"
         onclick="alert ('Number of options selected: ' + howMany(document.selectForm.musicTypes))"/>
   </p>
</form>
```
### do...while 语句

do...while 语句反复直到一个特定条件计算为假。do...while 语句如下所示：

```
do
   statement
while (condition);
```
在下面的例子中，do循环至少迭代一次，然后重复执行直到i不再小于5。

```
do {
   i += 1;
   document.write(i);
} while (i < 5);
```
### while 语句

while语句只要一个特定条件计算为真就执行语句。如下所示：

```
while (condition)
   statement
```
下面的while循环只在n小于3的时候反复执行：

```
n = 0;
x = 0;
while (n < 3) {
   n++;
   x += n;
}
```
避免死循环。 确保循环里的条件最终会变为false; 否则，这个循环将永远不会停止。下面的语句将一直循环，因为它的条件永远不会变为false:

```
while (true) {
   alert("Hello, world");
}
```
### 标签语句（label Statement）
标签语句提供一种使你同一程序的在另一处找到它的标识。例如，你可以用一个标签来识别一个循环，并用break或continue语句来说明一个程序是否要中断这个循环或是继续执行。如下所示：

```
label :
   statement
```
label 的值可以是js的任何非保留字标识符。 用label 标识的语句可以是任何语句。

例如

在这个示例中，markLoop这个标签定义了一个while循环。

```
markLoop:
while (theMark == true) {
   doSomething();
}
```
### 中断语句（break Statement）

使用中断语句终止循环、开关或与标签语句连接。

* 当你使用没有带标签语句的中断语句（break）时，while，do-while，for或者switch封闭的内部语句将立即终止，并转移到后面的语句执行。
* 当你使用带有标签语句的中断语句（break）时，将终止在特定的标签语句。

中断语句的语法如下：

1.break;

2.break label;

第一种语法形式用于终止在循环体或者switch的封闭内部；第二种语法形式用于在特定的封闭标签语句。

下面的例子中，对一个数组里的元素进行循环处理，直到数组元素下标等于theValue的值：

```
for (i = 0; i < a.length; i++) {
   if (a[i] == theValue)
      break;
}
```
中断跳到标签语句

```
var x = 0;
var z = 0
labelCancelLoops: while (true) {
    console.log("Outer loops: " + x);
    x += 1;
    z = 1;
    while (true) {
        console.log("Inner loops: " + z);
        z += 1;
        if (z === 10 && x === 10) {
            break labelCancelLoops;
        } else if (z === 10) {
            break;
        }
    }
}
```
### 连续语句（continue Statement）

连续语句用于重新开始 while, do-while, for语句，或者标签语句（label statement）。

* 当你使用没有带标签语句的连续语句（continue Statement）时，将在当前的while，do-while或者for循环体封闭的内部语句中止执行，然后进入下一次循环继续执行。与中断语句（break Statement）相比，连续语句不会把整个循环终止。在while循环里，将跳回条件判断（condition）；在for循环里，则跳回累计表达式（increment-expression）。
* 当你使用带有标签语句的连续语句时，用于识别循环体中的标签语句。
连续语句的语法如下：

1.continue

2.continue label

下面的例子实现了一个带有连续语句的while循环，当i的值为3时，该连续语句执行。因此，n的值分别为1、3、7和12。

```
i = 0;
n = 0;
while (i < 5) {
   i++;
   if (i == 3)
      continue;
   n += i;
}
```
一个标签语句checkiandj包含了一个标签语句checkj。如果连续语句被触发，程序会中止在当前循环中的checkj然后开始下一轮循环。每次连续语句被触发，checkj会重复直到该条件判断返回false值。当返回false值时，会完成剩下的checkiandj语句，然后checkiandj会重复直到其条件判断返回false值。当返回false值时，程序会继续执行在checkiandj后面的语句。

如果连续语句包含的是checkiandj标签，那么程序会在checkiandj语句的顶层继续执行。

```
checkiandj :
   while (i < 4) {
      document.write(i + "<br/>");
      i += 1;
      checkj :
         while (j > 4) {
            document.write(j + "<br/>");
            j -= 1;
            if ((j % 2) == 0)
               continue checkj;
            document.write(j + " is odd.<br/>");
         }
      document.write("i = " + i + "<br/>");
      document.write("j = " + j + "<br/>");
   }
   ```
### 对象操作语句（Object Manipulation Statements）

javaScript 用 for...in, for each...in和 with语句来操作对象。

* 对象操作语句

   for...in 语句迭代一个指定的变量去遍历这个对象的属性，每个属性，javascript 执行指定的语句。一个for...in 语句示例如下：

```
for (variable in object) {
   statements
}
```
如下的函数中传递了两个参数：一个对象和这个对象的名称，然后循环了这个对象的属性，最后得到一个列出了这个对象所有的属性名称和值的字符串。

```
function dump_props(obj, obj_name) {
   var result = "";
   for (var i in obj) {
      result += obj_name + "." + i + " = " + obj[i] + "<br>";
   }
   result += "<hr>";
   return result;
}
```
比如一个car对象，有make和model属性，结果就是这样的:

```
car.make = Ford
car.model = Mustang
```
* 数组（Arrays）
  
  虽然大多趋向于用for...in作为一种遍历数组（Array）元素的方式，因为除了遍历数组元素，for...in语句也遍历了用户自定义属性。如果你修改了数组对象，比如添加了通用属性或者方法，for...in语句还会返回除了数字索引（index）外的自定义属性的名称（name）。因此还是用带有数字索引的传统for循环来遍历数组会比较好。
  
  for each...in 语句
  for each...in 是一种在 JavaScript 1.6介绍过的循环语句。它和for...in相似，但是让对象属性的值递回取得，而不是作用于它们的名字。
  
  ```
  var sum = 0;
var obj = {prop1: 5, prop2: 13, prop3: 8};
for each (var item in obj) {
  sum += item;
}
print(sum); // prints "26", which is 5+13+8
```
### 异常处理语句(Exception Handling Statements)

你可以用throw 语句抛出一个异常并且用try...catch 语句捕获处理它。

* 抛出语句（throw Statement）

  使用throw语句抛出一个异常。当你抛出异常，你规定一个含有值的表达式要被抛出。
  
  ```
  throw expression;
  ```
  你可以抛出任意表达式而不是特定一种类型的表达式。下面的代码抛出了几个不同类型的表达式：
  
  ```
  throw "Error2";   // String type
throw 42;         // Number type
throw true;       // Boolean type
throw {toString: function() { return "I'm an object!"; } };
```
笔记：你可以在抛出异常时声明一个对象。那你就可以在捕捉块中查询到对象的属性。下面的例子创建了一个UserException类型的对象myUserException用在抛出语句中。

```
// Create an object type UserException
function UserException (message){
  this.message=message;
  this.name="UserException";
}

// Make the exception convert to a pretty string when used as
// a string (e.g. by the error console)
UserException.prototype.toString = function (){
  return this.name + ': "' + this.message + '"';
}

// Create an instance of the object type and throw it
throw new UserException("Value too high");
```
* try...catch 语句
  try...catch 语句标记一块待尝试的语句，并规定一个以上的响应应该有一个异常被抛出。如果我们抛出一个异常，try...catch语句就捕获它。

try...catch 语句有一个包含一条或者多条语句的try代码块，0个或多个的catch代码块，catch代码块中的语句会在try代码块中抛出异常时执行。 换句话说，如果你在try代码块中的代码如果没有执行成功，那么你希望将执行流程转入catch代码块。如果try代码块中的语句（或者try 代码块中调用的方法）一旦抛出了异常，那么执行流程会立即进入catch 代码块。如果try代码块没有抛出异常，catch代码块就会被跳过。finally 代码块总会紧跟在try和catch代码块之后执行，但会在try和catch代码块之后的其他代码之前执行。

下面的例子使用了try...catch语句。示例调用了一个函数用于从一个数组中根据传递值来获取一个月份名称。如果该值与月份数值不相符，会抛出一个带有"InvalidMonthNo"值的异常，然后在捕捉块语句中设monthName变量为unknown。

```
function getMonthName(mo) {
  mo = mo - 1; // Adjust month number for array index (1 = Jan, 12 = Dec)
  var months = ["Jan","Feb","Mar","Apr","May","Jun","Jul",
                "Aug","Sep","Oct","Nov","Dec"];
  if (months[mo]) {
    return months[mo];
  } else {
    throw "InvalidMonthNo"; //throw keyword is used here
  }
}

try { // statements to try
  monthName = getMonthName(myMonth); // function could throw exception
}
catch (e) {
  monthName = "unknown";
  logMyErrors(e); // pass exception object to error handler -> your own function
}
```
* 捕捉块（The catch Block）
  
  你可以使用捕捉块来处理所有可能在try代码块中产生的异常。
  
  ```
  catch (catchID) {
     statements
  }
```
  捕捉块指定了一个标识符 (上述语句中的catchID）来存放抛出语句指定的值；你可以用这个标识符来获取抛出的异常信息。在插入捕捉块时JavaScript创建这个标识符；标识符只存在于捕捉块的存续期间里；当捕捉块执行完成时，标识符不再可用。

举个例子，下面代码抛出了一个异常。当异常出现时跳到捕捉块（the catch block）。

```
try {
   throw "myException" // generates an exception
}
catch (e) {
// statements to handle any exceptions
   logMyErrors(e) // pass exception object to error handler
}
```
### 终结块（The finally Block）
终结块包含了在try和catch块完成后、下面接着的try...catch语句之前执行的语句。终结块无论是否抛出异常都会执行。如果抛出了一个异常，就算没有异常处理，终结块里的语句也会执行。

你可以用终结块来令你的脚本在异常发生时优雅地退出；举个例子，你可能需要在绑定的脚本中释放资源。接下来的例子用文件处理语句打开了一个文件（服务端的JavaScript允许你进入文件）。如果在文件打开时一个异常抛出，终结块会在脚本错误之前关闭文件。

```
openMyFile();
try {
    writeMyFile(theData); //This may throw a error
}catch(e){
    handleError(e); // If we got a error we handle it
}finally {
    closeMyFile(); // always close the resource
}
```
如果终结块返回一个值，该值会是整个try-catch-finally流程的返回值，不管在try和catch块中语句返回了什么：

```
function f() {
  try {
    console.log(0);
    throw "bogus";
  } catch(e) {
    console.log(1);
    return true; // this return statement is suspended
                 // until finally block has completed
    console.log(2); // not reachable
  } finally {
    console.log(3);
    return false; // overwrites the previous "return"
    console.log(4); // not reachable
  }
  // "return false" is executed now  
  console.log(5); // not reachable
}
f(); // console 0, 1, 3; returns false
```
嵌套try...catch语句

你可以嵌套一个或多个try...catch语句。如果一个内部的try...catch语句没有捕捉块（catch block），将会启动匹配外部的try...catch语句的捕捉块（catch block）。

### 错误匹配对象（Utilizing Error objects）

根据错误类型，你也许可以用'name'和'message'获取更精炼的信息。'name'提供了常规的错误类(e.g., 'DOMException' or 'Error')，而'message'通常提供了一条从错误对象转换成字符串的简明信息。

在抛出你个人所为的异常时，为了充分利用那些属性（比如你的catch块不能分辨是你个人所为的异常还是系统的异常时），你可以使用错误构造函数（the Error constructor）。比如：

```
function doSomethingErrorProne () {
  if (ourCodeMakesAMistake()) {
    throw (new Error('The message'));
  } else {
    doSomethingToGetAJavascriptError();
  }
}
....
try {
  doSomethingErrorProne();
}
catch (e) {
  console.log(e.name); // logs 'Error'
  console.log(e.message); // logs 'The message' or a JavaScript error message)
}
```
### Promises
从 ECMAScript 6 开始，JavaScript 增加了对 Promise 对象的支持，它允许你对延时和异步操作流进行控制。

Promise 对象有以下几种状态:

* pending (进行中): 初始的状态，即正在执行，不处于 fulfilled 或 rejected 状态。
* fulfilled (已完成): 成功的完成了操作。
* rejected (已失败): 失败，没有完成操作。
* settled (已解决): Promise 处于 fulfilled 或 rejected 二者中的任意一个状态, 不会是 pending。 

### 通过 XHR 加载图片
这个简单的例子，它使用了 Promise 和 XMLHttpRequest 来加载一张图片，同时为了让你更清楚的了解 Promise 和 XHR 的结构，代码中每一个步骤后都附带了注释。

这里有一个未注释的版本，展现了 Promise 的工作流，希望可以对你的理解有所帮助。

```
function imgLoad(url) {
  return new Promise(function(resolve, reject) {
    var request = new XMLHttpRequest();
    request.open('GET', url);
    request.responseType = 'blob';
    request.onload = function() {
      if (request.status === 200) {
        resolve(request.response);
      } else {
        reject(Error('Image didn\'t load successfully; error code:' 
                     + request.statusText));
      }
    };
    request.onerror = function() {
      reject(Error('There was a network error.'));
    };
    request.send();
  });
}
```
下面的这个例子展示了 for...of 和 for...in 两种循环语句之间的区别。与 for...in 循环遍历的结果是数组元素的下标不同的是， for...of 遍历的结果是元素的值：

```
let arr = [3, 5, 7];
arr.foo = "hello";

for (let i in arr) {
   console.log(i); // logs "0", "1", "2", "foo"
}

for (let i of arr) {
   console.log(i); // logs "3", "5", "7" // 注意这里没有 hello
}
```





