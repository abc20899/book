
# Android编码规范
术语
---
1. class 可表示一个普通类，枚举类，接口或是annotation类型(@interface)
2. comment 只用来指代实现的注释(implementation comments)，我们不使用”documentation comments”一词，而是用 Javadoc。
<!--more-->
源文件基础
---
1. 文件名，源文件以其最顶层的类名来命名，大小写敏感，文件扩展名为.java。
2. 文件编码，所有源文件编码必须是`UTF-8`

注释
---

`Java`程序有两类注释：实现注释`(implementation comments)`和文档注释`(document comments)`。
实现注释是使用/*...*/和//界定的注释。文档注释(被称为"doc comments")由/**...*/界定。文档注释可以通过javadoc 工具转换成HTML 文件。

1. 类注释
	每一个类都要包含如下格式的注释，以说明当前类的功能等。
	/**
	 * 类名
	 * @author 作者 <br/>
	 *	实现的主要功能。
	 *	创建日期
	 *	修改者，修改日期，修改内容。
	 */

2. 方法注释
	每一个方法都要包含 如下格式的注释 包括当前方法的用途，当前方法参数的含义，当前方法返回值的内容和抛出异常的列表。
	/**
	 * 
	 * 方法的一句话概述
	 * <p>方法详述（简单方法可不必详述）</p>
	 * @param s 说明参数含义
	 * @return 说明返回值含义
	 * @throws IOException 说明发生此异常的条件
	 * @throws NullPointerException 说明发生此异常的条件
	 */

3. 类成员变量和常量注释
	成员变量和常量需要使用`java doc`形式的注释，以说明当前变量或常量的含义
	/**
	 * XXXX含义
	 */

4. 其他注释
	方法内部的注释 如果需要多行 使用/*…… */形式，如果为单行是用//……形式的注释。
	不要再方法内部使用 java doc 形式的注释“/**……*/”


类声明
---
1. 类成员顺序
不同的类对成员的排序可能是不同的。
最重要的一点，每个类应该以某种逻辑去排序它的成员，维护者应该要能解释这种排序逻辑。比如， 新的方法不能总是习惯性地添加到类的结尾，因为这样就是按时间顺序而非某种逻辑来排序的。
2. 区块划分
 * 常量声明区
 * UI控件成员变量声明区
 * 普通成员变量声明区
 * 内部接口声明区
 * 初始化相关方法区
 * 事件响应方法区
 * 普通逻辑方法区
 * 重载的逻辑方法区
 * 发起异步任务方法区
 * 异步任务回调方法区
 * 生命周期回调方法区（除去onCreate()方法）
 * 内部类声明区
3. 类成员排列通用规则
 * 按照发生的先后顺序排列
 * 常量按照使用先后排列
 * UI控件成员变量按照layout文件中的先后顺序排列
 * 普通成员变量按照使用的先后顺序排列
 * 方法基本上都按照调用的先后顺序在各自区块中排列
 * 相关功能作为小区块放在一起（或者封装掉）

命名约定
---
### 基本原则
1. 代码部分不允许使用中文，注释部分不建议使用中文。
2. 代码部分不允许使用hardcode的方式使用数字、字符串等，必须以常量的形式定义之后再用。例如：textview.setText(“data”)的写法是不允许的。
3. 英文单词尽量避免拼写错误，便于以后的维护和查找代码。如果一个单词或词组有通用的缩写方式可以使用缩写，但不要自己创造难懂的缩写。
4. 命名的描述尽量见名知意，不要太过笼统，也不要过于冗余。

##### 包名
1.包名全部小写，连续的单词只是简单地连接起来，不使用下划线。
采用反域名命名规则，全部使用小写字母。一级包名为com，二级包名为xx（可以是公司或则个人的随便），三级包名根据应用进行命名，四级包名为模块名或层级名。
如：cn.junechiu.movieinfo
Android工程的分包通常按照不同的模块、功能进行分包，分包时根据系统模块+项目功能模块灵活进行分包
包命名必须以`com.domain`开始,后面跟有项目名称（或者缩写）,再后面为模块名或层级名称。           
		如：`com.domain.项目缩写.模块名` `com.domain.xx.bookmark`        
		如：`com.domain.项目缩写.层级名` `com.domain.xx.activity`
		
包名                        |   包含
----------------------------|----------------------------
com.xx.应用名称缩写.activity	  | 页面用到的Activity类 (activitie层级名用户界面层)
com.xx.应用名称缩写.base	     | 基础共享的类
com.xx.应用名称缩写.adapter	  | 页面用到的Adapter类 (适配器的类)
com.xx.应用名称缩写.util	     | 此包中包含：公共工具方法类（util模块名）
com.xx.应用名称缩写.bean	     | 下面可分：vo、po、dto 此包中包含：JavaBean类
com.xx.应用名称缩写.model	     | 此包中包含：模型类
com.xx.应用名称缩写.db 	     | 数据库操作类
com.xx.应用名称缩写.view      | (或者 com.xx.应用名称缩写.widget )	自定义的View类等
com.xx.应用名称缩写.service	 | Service服务
com.xx.应用名称缩写.receiver	 | BroadcastReceiver服务

##### 类和接口命名
命名规则：类名是个一名词，采用大小写混合的方式，每个单词的首字母大写。尽量使你的类名简洁而富于描述。使用完整单词，
	避免缩写词(除非该缩写词被更广泛使用，像 URL，HTML)        
	接口一般要使用`able`,`ible`,`er`等后缀              
	类名必须使用**驼峰规则**，即首字母必须大写，如果为词组，则每个单词的首字母也必须要大写，类名必须使用名词，或名词词组。
	要求类名简单，不允许出现无意义的单词。
	
类	                       | 描述	                   | 例如
--------------------------|-------------------------|------------------
Activity 类	             | Activity为后缀标识        | 欢迎页面类WelcomeActivity
Adapter类	Adapter         | 为后缀标识	    | 新闻详情适配器NewDetailAdapter
工具方法类	| Util或Manager为后缀标识（与系统或第三方的Utils区分）或功能+Util	| 线程池管理类：ThreadPoolManager日志工具类：LogUtil（Logger也可）打印工具类：PrinterUtil
数据库类	| 以DBHelper后缀标识	| 新闻数据库：NewDBHelper
Service类	| 以Service为后缀标识	| 时间服务TimeServiceBroadcast
Receiver类	| 以Receiver为后缀标识	| 推送接收JPushReceiver
ContentProvider	| 以Provider为后缀标识	
自定义的共享基础类	| 以Base开头	| BaseActivity,BaseFragment

测试类的命名以它要测试的类的名称开始，以Test结束。
例如：HashTest 或 HashIntegrationTest。

##### 方法名
方法名都以 LowerCamelCase 风格编写。方法名通常是动词或动词短语。

方法	    |   说明
-----------|--------------------------------
initXX()	| 初始化相关方法,使用init为前缀标识，如初始化布局initView()
isXX() checkXX()	| 方法返回值为boolean型的请使用is或check为前缀标识
getXX()	| 返回某个值的方法，使用get为前缀标识
handleXX()	| 对数据进行处理的方法，尽量使用handle为前缀标识
displayXX()/showXX()	| 弹出提示框和提示信息，使用display/show为前缀标识
saveXX()	| 与保存数据相关的，使用save为前缀标识
resetXX()	| 对数据重组的，使用reset前缀标识
clearXX()	| 清除数据相关的
removeXXX()	| 清除数据相关的
drawXXX()	| 绘制数据或效果相关的，使用draw前缀标识

##### 变量命名
命名规则：第一个单词的首字母小写，其后单词的首字母大写。变量名不应以下划线或美元符号开头，尽管这在语法上是允许的。变量名应简短且富于描述。
	变量名的选用应该易于记忆，即，能够指出其用途。尽量避免单个字符的变量名，除非是一次性的临时变量。临时变量通常被取名为 `i,j,k,m,n`它们一般用于整型；
	`c,d,e` 它们一般用于字符型。         
	在`Android`中成员变量
	非`public`非`static`的变量可以使用`m`开头
	非常量的`static`变量可以使用`s`开头
	变量命名也必须使用**驼峰规则**，但是首字母必须小写，变量名尽可能的使用名词或名词词组。同样要求简单易懂，不允许出现无意义的单词。
	例如：`private String mBookName; ` 

##### 常量命名
命名规则：类常量的声明，应该全部大写，单词间用下划线隔开。
例如：`private static final int MIN_WIDTH = 4;`
	
##### 异常命名
自定义异常的命名必须以`Exception`为结尾。已明确标示为一个异常。
	
##### layout命名
`layout.xml`的命名必须以全部单词小写，单词间以下划线分割，并且使用名词或名词词组，即使用 模块名_功能名称_所属页面类型 来命名。
	如：`video_controller_player_activity`     视频模块下的-控制栏-属于播放器的-Activity页
	
##### id命名
·layout`中所使用的`id`必须以全部单词小写，单词间以下划线分割，并且使用名词或名词词组，并且要求能够通过`id`直接理解当前组件要实现的功能。       
	如：某`TextView @+id/tv_book_name_show`         
	如：某`EditText @+id/`et_book_name_edit`  
	
##### 资源文件命名规范
1. 资源布局文件（XML文件（layout布局文件））：全部小写，采用下划线命名法
	* contentview 命名
	必须以全部单词小写，单词间以下划线分割，使用名词或名词词组。
	所有Activity或Fragment的contentView必须与其类名对应，对应规则为：
	将所有字母都转为小写，将类型和功能调换（也就是后缀变前缀）。
	例如：activity_main.xml
   * Dialog命名：dialog_描述.xml
	例如：dialog_hint.xml
	
   * PopupWindow命名：ppw_描述.xml
	例如：ppw_info.xml
	
	* 列表项命名：item_描述.xml
	例如：item_city.xml
	
	* 包含项命名：模块_(位置)描述.xml
	例如：activity_main_head.xml、activity_main_bottom.xml
	注意：通用的包含项命名采用：项目名称缩写_描述.xml
	例如：xxxx_title.xml
2. 资源文件（图片drawable文件夹下）：全部小写，采用下划线命名法	用途_模块名_逻辑名称</br>
	用途_模块名_颜色</br>
	用途_逻辑名称</br>
	用途_颜色</br>
	说明：用途也指控件类型（具体见UI控件缩写表）</br>
	例如：</br>
	btn_main_home.png 按键</br>
	divider_maket_white.png 分割线</br>
	ic_edit.png 图标</br>
	bg_main.png 背景</br>
	btn_red.png 红色按键</br>
	btn_red_big.png 红色大按键</br>
	ic_head_small.png 小头像</br>
	bg_input.png 输入框背景</br>
	divider_white.png 白色分割线</br>
	如果有多种形态如按钮等除外如 btn_xx.xml（selector）</br>
	
代码风格
---

1. 缩进
    除了换行符之外，ASCII空格（0x20）是唯一合法的空格字符。这意味着
    不允许使用`Tab`进行缩进，应该使用空格进行缩进，推荐缩进为4个空格		
	`Eclipse`中将`Tab`替换为4个空格的设置方法(很多人都习惯直接按4次空格，感觉不设置习惯了也挺好)
		- 代码设置
			`Window->Preferences->General->Editors->Text Editors->`勾选`Insert spaces for tabs``
		- XML文件的Tab配置
			`Window->Preferences->XML->XML Files->Editor>`选择右侧区域的`Indent using spaces`


2. 空行
	空行将逻辑相关的代码段分隔开，以提高可读性。       
	
 	下列情况应该总是使用空行： 
	- 一个源文件的两个片段之间
 	- 类声明和接口声明之间
	- 两个方法之间
	- 方法内的局部变量和方法的第一条语句之间
	- 一个方法内的两个逻辑段之间，用以提高可读性  

    通常在 变量声明区域之后要用空行分隔，常量声明区域之后要有空行分隔，方法声明之前要有空行分隔。

3. 方法
 	- 一个方法尽量不要超过15行(可能会有难度，但是尽量不要太多，弄个方法几千行这是绝对不允许的)，如果方法太长，说明当前方法业务逻辑已经非常复杂，
		那么就需要进行方法拆分，保证每个方法只作一件事。
	- 不要使用`try catch`处理业务逻辑！！！！

4. 参数和返回值
    - 一个方法的参数尽可能的不要超过4个(根据情况可能也会有些难度)
    - 如果一个方法返回的是一个错误码，请使用异常！！
    - 尽可能不要使用`null`替代为异常

5. 神秘数字
	代码中不允许出现单独的数字，字符！如果需要使用数字或字符，则将它们按照含义封装为静态常量!(`for`语句中除外)
	
6. 控制语句
	判断中如有常量，则应将常量置于判断式的右侧。如： 
	`if (true == isAdmin())...`
	尽量不要使用三目条件的嵌套。

	在`if`、`else`、`for`、`do`和`while`语句中，即使没有语句或者只有一行，也不得省略花括号：
	```java
	if (true){
		//do something......
	}
	```
	不要使用下面的方式:
	```java
	if (true)
		i = 0; //不要使用这种
	```
	
	对于循环：
	//将操作结构保存在临时变量里，减少方法调用次数
	```java
	final int count = products.getCount();
	while(index < count){
		// ...
	}
	```
	而不是
	```java
	while(index < products.getCount()){
		//每此都会执行一次getCount()方法，
		//若此方法耗时则会影响执行效率
		//而且可能带来同步问题，若有同步需求，请使用同步块或同步方法
	}
	```


7. 访问控制
	若没有足够理由，不要把实例或类变量声明为公有。
	
8. 变量赋值
	不要使用内嵌(embedded)赋值运算符试图提高运行时的效率，这是编译器的工作。例如： 
	 `d = (a = b + c) + r;`
	应该写成 
	```java
	a = b + c; 
	d = a + r; 
	```
	
9. 圆括号的试用
	一般而言，在含有多种运算符的表达式中使用圆括号来避免运算符优先级问题，是个好方法。
	即使运算符的优先级对你而言可能很清楚，但对其他人未必如此。你不能假设别的程序员和你一样清楚运算符的优先级。 
	不要这样写：
	`if (a == b && c == d)`
	正确的方式为： 
	`if ((a == b) && (c == d))`

10. 返回值
	设法让你的程序结构符合目的。例如： 
	```java
	if (booleanExpression) { 
		return true; 
	} else { 
		return false; 
	} 
	```
	应该代之以如下方法： 
	`return booleanExpression`

	类似地： 
	```java
	if (condition) { 
		return x; 
	} 
	return y; 
	```
	应该写做： 
    `return (condition ? x : y);`

11. 条件运算符`?`前的表达式    
	如果一个包含二元运算符的表达式出现在三元运算符" ? : "的"?"之前，那么应该给表达式添上一对圆括号。例如：  
	`(x >= 0) ? x : -x`

12.  所有未使用的import语句应该被删除。	

13. 重载（Overload）方法必须放在一起

14. 非空块中花括号的使用
	在非空代码块中使用花括号时要遵循`K&R`风格`(Kernighan and Ritchie Style)：
	左花括号（{）前不能换行，在其后换行。
	在右花括号（}）前要有换行。
	
15. 空代码块中花括号的使用	
	如果一个代码块是空的，可以直接使用`{}`。除了`if/else-if/else`和`try/catch/finally`这样的多块语句.
	
16. 列宽
	列宽必须为120字符，以下情况可以不遵守列宽限制：
	无法限制宽度的内容，比如注释里的长`URL`
	`package`和`import`语句
	注释中需要被粘贴到`Shell`里去执行的命令

17. 枚举
	用逗号分割每个枚举变量，并且变量要单独在一行
	```java
	enum Color {
		RED,
		GREEN,
		YELLOW
	}
	```
	
18. 长整形数字
	长整型数字必须使用大写字母`L`结尾，不能使用小写字母`l`，以便和数字1进行区分。例如使用3000000000L而不是3000000000l

代码严谨性
---

1. `ArrayList`通过`get`方法使用下标获取元素，如果使用的下标不在`ArrayList`大小范围内，将产生`java.lang.IndexOutOfBoundsException`的异常，导致`app`出现`Crash`。

2. 方法中存在`return null`返回对象直接进行方法调用隐患, 在使用时需要先判断是否为`null`，一般尽量不要在方法中直接`return null`，最好用异常代替。

3. 销毁`Dialog`前是否`isShowing`未判断隐患
	调用`Android.app.Dialog.cancel()`方法前，如果这个`dialog`不处于`showing`状态时，会抛出`java.lang.IllegalArgumentException`的异常，导致`app`出现`Crash`。

4. 使用`String.split`结果未判断长度隐患
	在使用`String.split`得到的结果数组前，未对数组进行长度检查，取字段的时候可能发生越界而导致`Crash`。
	```java
	String source = "<br/>";
	String[] infos = source.split("<br/>");
	if(0 < infos.length){
	   String poiName = infos[0];
	}
	```	
5. switch语句,每个switch语句都包含一个default语句组，即使它什么代码也不包含。	
	
























