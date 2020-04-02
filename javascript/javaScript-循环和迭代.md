你可以把循环想成一种计算机化的游戏，告诉某人在一个方向上走X步，然后在另一个方向上走Y步；例如，“向东走5步”可以用一个循环来这样表达：

```
var step;
for (step = 0; step < 5; step++) {
  // Runs 5 times, with values of step 0 through 4.
  console.log('Walking east one step');
}
```

循环有很多种类，但本质上它们都做的是同一件事：它们把一个动作重复了很多次（实际上重复的次数有可能为0）。各种循环机制提供了不同的方法去确定循环的开始和结束。不同情况下，某一种类型循环会比其它的循环用起来更简单。
JavaScript中提供了这些循环语句：

* for statement
* do...while statement
* while statement
* label statement
* break statement
* continue statement
* for...in statement
* for...of statement

### for 语句
一个for循环会一直重复执行，直到指定的循环条件为fasle。 JavaScript的for循环和Java与C的for循环是很相似的。一个for语句是这个样子的：

```
for ([initialExpression]; [condition]; [incrementExpression])
  statement
```
当一个for循环执行的时候，会发生以下事件：

1. 如果有初始化表达式initialExpression，它将被执行。这个表达式通常会初始化一个或多个循环计数器，但语法上是允许一个任意复杂度的表达式的。这个表达式也可以声明变量。
2. 计算condition表达式的值。如果condition的值是true，循环中的statement会被执行。如果condition的值是false，for循环终止。如果condition表达式整个都被省略掉了，condition的值会被认为是true。
3. 循环中的statement被执行。如果需要执行多条语句，可以使用块 ({ ... })来包裹这些语句。
4. 如果有更新表达式incrementExpression，执行它，然后流程回到步骤2。

### 例子

下面的函数包含一个含有for循环去计算一个滑动列表中被选中项目的个数（一个 <select> 元素允许选择多项）。for循环声明了变量i并将它的初始值设为0。它检查i比 <select> 元素中的选项数量少，执行了随后的if语句，然后在每次完成循环以后i的值增加1。

```html
<form name="selectForm">
  <p>
    <label for="musicTypes">Choose some music types, then click the button below:</label>
    <select id="musicTypes" name="musicTypes" multiple="multiple">
      <option selected="selected">R&B</option>
      <option>爵士</option>
      <option>布鲁斯</option>
      <option>新纪元</option>
      <option>古典</option>
      <option>戏剧</option>
    </select>
  </p>
  <p><input id="btn" type="button" value="选择了多少个选项?" /></p>
</form>

<script>
function howMany(selectObject) {
  var numberSelected = 0;
  for (var i = 0; i < selectObject.options.length; i++) {
    if (selectObject.options[i].selected) {
      numberSelected++;
    }
  }
  return numberSelected;
}

var btn = document.getElementById("btn");
btn.addEventListener("click", function(){
  alert('选择选项的数量是: ' + howMany(document.selectForm.musicTypes))
});
</script>
```

### do...while 语句
do...while 语句一直重复直到指定的条件求值得到假（false）。 一个 do...while 语句看起来像这样：

```
do
  statement
while (condition);
```
statement 在检查条件之间会执行一次。要执行多条语句（语句块），要使用块语句 ({ ... }) 包括起来。 如果 condition 为真（true），statement 将再次执行。 在每个执行的结尾会进行条件的检查。当 condition 为假（false），执行会停止并且把控制权交回给 do...while 后面的语句。

### 例子
在下面的例子中， 这个 do 循环将至少重复一次并且一直重复直到 i 不再小于 5。

```
do {
  i += 1;
  console.log(i);
} while (i < 5);
```

### while 语句
一个 while 语句只要指定的条件求值为真（true）就会一直执行它的语句块。一个 while 语句看起来像这样：

```
while (condition)
  statement
```
如果这个条件变为假，循环里的 statement 将会停止执行并把控制权交回给 while 语句后面的代码。

条件检测会在每次 statement 执行之前发生。如果条件返回为真， statement 会被执行并紧接着再次测试条件。如果条件返回为假，执行将停止并把控制权交回给 while 后面的语句。

要执行多条语句（语句块），要使用块语句 ({ ... }) 包括起来。

### 例子 1
下面的 while 循环只要 n 小于 3就会一直执行：

```
var n = 0;
var x = 0;
while (n < 3) {
  n++;
  x += n;
}
```
在每次循环里， n 会增加1并被加到 x 上。所以， x 和 n 的变化是：

第一次完成后： n = 1 和 x = 1
第二次完成后： n = 2 和 x = 3
第三次完成后： n = 3 和 x = 6
在三次完成后， 条件 n < 3 结果不再为真，所以循环终止了。

### 例子 2
避免无穷循环（无限循环）。保证循环的条件结果最终会变成假；否则，循环永远不会停止。下面这个 while 循环会永远执行因为条件永远不会变成假：

```
while (true) {
  console.log("Hello, world");
}
```
### label 语句
一个 label 提供了一个可以让你引用到您程序别的位置的标识符。例如，你可以用 label 标识一个循环， 然后使用 break 或者 continue 来指出程序是否该停止循环还是继续循环。

label 语句的语法看起来像这样：

```
label :
   statement
```
label 的值可以是任何的非保留字的 JavaScript 标识符， statement 可以是任意你想要标识的语句（块）。

### 例子
在这个例子里，标记 markLoop 标识了一个 while 循环。

```
markLoop:
while (theMark == true) {
   doSomething();
}
```
### break 语句
使用 break 语句来终止循环，switch， 或者是链接到 label 语句。

当你使用不带 label 的 break 时， 它会立即终止当前所在的 while，do-while，for，或者 switch 并把控制权交回这些结构后面的语句。
当你使用带 label 的 break 时，它会终止指定的标记（label）了的语句。
break 语句的语法看起来像这样：

break;
break label;
第一种形式的语法终止当前所在的循环或 switch； 第二种形式的语法终止指定的 label 语句。

### 例子 1
下面的例子循环数组里的元素直到找到一个值是等于 theValue 的：

```
for (i = 0; i < a.length; i++) {
  if (a[i] == theValue) {
    break;
  }
}
```
### 例子 2: 终止一个 label

```
var x = 0;
var z = 0
labelCancelLoops: while (true) {
  console.log("外部循环: " + x);
  x += 1;
  z = 1;
  while (true) {
    console.log("内部循环: " + z);
    z += 1;
    if (z === 10 && x === 10) {
      break labelCancelLoops;
    } else if (z === 10) {
      break;
    }
  }
}
```
### continue 语句
这个 continue 语句可以用来重新开始一个 while， do-while， for， 或者 label 语句。

* 当你使用不带 label 的 continue 时， 它终止当前 while，do-while，或者 for 语句到结尾的这次的循环并且继续执行下一次循环。
* 当你使用带 label 的 continue 时， 它会应用被 label 标识的循环语句。
continue 的语法看起来像这样：

1. continue;
2. continue label;

### 例子 1
下面的例子展示了带有一个当 i 等于 3的 continue 语句的循环。 于是， n 取到的值是 1， 3， 7， 12。

```
var i = 0;
var n = 0;
while (i < 5) {
  i++;
  if (i == 3) {
    continue;
  }
  n += i;
}
```
### 例子 2
一个被标签为checkiandj 的语句包含了一个标签为checkj 的语句。如果遇到continue语句，程序会结束当前chechj的迭代并开始下一轮的迭代。每次遇到continue语句，checkj 语句会一直重复执行直到checkj语句的条件为false。. 当返回false后，checkiandj的剩余语句将会执行，checkiandj会一直执行指导checkiandj的条件为false。当checkiandj的返回值为false时，将会执行checkiandj 的下面的语句。

如果 continue 有一个标记 checkiandj， 程序将会从 checkiandj 语句块的顶部继续执行。

```
checkiandj:
  while (i < 4) {
    console.log(i);
    i += 1;
    checkj:
      while (j > 4) {
        console.log(j);
        j -= 1;
        if ((j % 2) == 0) {
          continue checkj;
        }
        console.log(j + " is odd.");
      }
      console.log("i = " + i);
      console.log("j = " + j);
  }
```
### for...in 语句
这个 for...in 语句循环一个指定的变量来循环一个对象所有可枚举的属性。JavaScript 会为每一个不同的属性执行指定的语句。

```
for (variable in object) {
  statements
}
```
### 例子
下面的函数通过它的参数得到一个对象和这个对象的名字。然后循环这个对象的所有属性并且返回一个列出属性名和该属性值的字符串。

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
对于一个对象拥有 make 和 model 属性的 car 对象来说，执行结果是：

```
car.make = Ford
car.model = Mustang
```

### 数组
虽然用for...in来迭代Array元素很诱人，但是它返回的除了数字索引外还有可能是你自定义的属性名字。因此还是用带有数字索引的传统的for 循环来迭代一个数组比较好，因为如果你想改变数组对象，比如添加属性或者方法，for...in 语句迭代的是 自定义的属性而不是数组的元素。

for...of statement
该新特性属于 ECMAScript 2015（ES6）规范，在使用时请注意浏览器兼容性。

for...of语句在可迭代的对象上创建了一个循环(包括Array, Map, Set, 参数对象（ arguments） 等等)，对值的每一个独特的属性调用一个将被执行的自定义的和语句挂钩的迭代。

```
for (variable of object) {
  statement
}
```
下面的这个例子展示了 for...of 和 for...in 两种循环语句之间的区别。与 for...in 循环遍历的结果是数组元素的下标不同的是， for...of 遍历的结果是元素的值：

```javaSctipt
let arr = [3, 5, 7];
arr.foo = "hello";

for (let i in arr) {
   console.log(i); // logs "0", "1", "2", "foo"
}

for (let i of arr) {
   console.log(i); // logs "3", "5", "7" // 注意这里没有 hello
}
```

















