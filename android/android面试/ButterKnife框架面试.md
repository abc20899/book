### 一、Butterknife使用简介

Butterknife是一个依托Java的注解机制来实现辅助代码生成的框架，不通过反射机制。

在Android Studio中引入Butterknife需在build.gradle中加入如下代码：

```
dependencies {
  compile 'com.jakewharton:butterknife:8.8.1'
  annotationProcessor 'com.jakewharton:butterknife-compiler:8.8.1'
}
```
使用步骤：

1.绑定一个View

2.给一个View添加点击事件

3.给多个View添加点击事件

4.给ListView setItemClickListener

```
public class MainActivity extends AppCompatActivity {

    //1.绑定一个View（View不能为private 或者 static）
    @BindView(R.id.textview)
    TextView mTextView;

    //1.绑定一个View（View不能为private 或者 static）
    @BindView(R.id.mlistview)
    ListView mListView;

    //1.绑定一个View（View不能为private 或者 static）
    @BindView(R.id.imageview)
    ImageView mImageView;

    //2.给一个view添加点击事件
    @OnClick({R.id.textview, R.id.imageview})
    public void onTextViewClick() {
        Toast.makeText(this, "onTextViewClick", Toast.LENGTH_SHORT).show();
    }

    //3.给ListView setItemClickListener
    @OnItemClick(R.id.mlistview)
    public void onItemClick() {
        Toast.makeText(this, "onItemClick", Toast.LENGTH_SHORT).show();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this); //绑定
    }
}
```
### 二、Butterknife原理

java注解处理机制

1.开始回扫描Java代码中所有的Butterknife注解

2.ButterKnifeProcessor会生成<className>$$ViewBinder内部类

3.调用bind方法加载生成的ViewBinder类

view变量不能为private或者static  只能通过反射