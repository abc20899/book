### 一、自绘控件
自绘控件的意思就是，这个View上所展现的内容全部都是我们自己绘制出来的。绘制的代码是写在onDraw()方法中的。调用invalidate()更新<br>
自定义一个计数器View，这个View可以响应用户的点击事件，并自动记录一共点击了多少次。新建一个CounterView继承自View

```
public class CounterView extends View implements OnClickListener {  
  
    private Paint mPaint;  
      
    private Rect mBounds;  
  
    private int mCount;  
      
    public CounterView(Context context, AttributeSet attrs) {  
        super(context, attrs);  
        mPaint = new Paint(Paint.ANTI_ALIAS_FLAG);  
        mBounds = new Rect();  
        setOnClickListener(this);  
    }  
  
    @Override  
    protected void onDraw(Canvas canvas) {  
        super.onDraw(canvas);  
        mPaint.setColor(Color.BLUE);  
        canvas.drawRect(0, 0, getWidth(), getHeight(), mPaint);  
        mPaint.setColor(Color.YELLOW);  
        mPaint.setTextSize(30);  
        String text = String.valueOf(mCount);  
        mPaint.getTextBounds(text, 0, text.length(), mBounds);  
        float textWidth = mBounds.width();  
        float textHeight = mBounds.height();  
        canvas.drawText(text, getWidth() / 2 - textWidth / 2, getHeight() / 2  
                + textHeight / 2, mPaint);  
    }  
  
    @Override  
    public void onClick(View v) {  
        mCount++;  
        invalidate();  
    }  
```

### 二、组合控件
组合控件的意思就是，我们并不需要自己去绘制视图上显示的内容，而只是用系统原生的控件就好了，但我们可以将几个系统原生的控件组合到一起，这样创建出的控件就被称为组合控件。<br>
举个例子来说，标题栏就是个很常见的组合控件，很多界面的头部都会放置一个标题栏，标题栏上会有个返回按钮和标题，点击按钮后就可以返回到上一个界面。那么下面我们就来尝试去实现这样一个标题栏控件。

```
<?xml version="1.0" encoding="utf-8"?>  
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"  
    android:layout_width="match_parent"  
    android:layout_height="50dp"  
    android:background="#ffcb05" >  
  
    <Button  
        android:id="@+id/button_left"  
        android:layout_width="60dp"  
        android:layout_height="40dp"  
        android:layout_centerVertical="true"  
        android:layout_marginLeft="5dp"  
        android:background="@drawable/back_button"  
        android:text="Back"  
        android:textColor="#fff" />  
  
    <TextView  
        android:id="@+id/title_text"  
        android:layout_width="wrap_content"  
        android:layout_height="wrap_content"  
        android:layout_centerInParent="true"  
        android:text="This is Title"  
        android:textColor="#fff"  
        android:textSize="20sp" />  
  
</RelativeLayout>  
```
接下来创建一个TitleView继承自FrameLayout

```
public class TitleView extends FrameLayout {  
  
    private Button leftButton;  
  
    private TextView titleText;  
  
    public TitleView(Context context, AttributeSet attrs) {  
        super(context, attrs);  
        LayoutInflater.from(context).inflate(R.layout.title, this);  
        titleText = (TextView) findViewById(R.id.title_text);  
        leftButton = (Button) findViewById(R.id.button_left);  
        leftButton.setOnClickListener(new OnClickListener() {  
            @Override  
            public void onClick(View v) {  
                ((Activity) getContext()).finish();  
            }  
        });  
    }  
  
    public void setTitleText(String text) {  
        titleText.setText(text);  
    }  
  
    public void setLeftButtonText(String text) {  
        leftButton.setText(text);  
    }  
  
    public void setLeftButtonListener(OnClickListener l) {  
        leftButton.setOnClickListener(l);  
    }  
} 
```
```
<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"  
    xmlns:tools="http://schemas.android.com/tools"  
    android:layout_width="match_parent"  
    android:layout_height="match_parent" >  
  
    <com.example.customview.TitleView  
        android:id="@+id/title_view"  
        android:layout_width="match_parent"  
        android:layout_height="wrap_content" >  
    </com.example.customview.TitleView>  
  
</RelativeLayout>  
```
### 三、继承控件
继承控件的意思就是，我们并不需要自己重头去实现一个控件，只需要去继承一个现有的控件，然后在这个控件上增加一些新的功能，就可以形成一个自定义的控件了。这种自定义控件的特点就是不仅能够按照我们的需求加入相应的功能，还可以保留原生控件的所有功能<br>
对ListView进行扩展，加入在ListView上滑动就可以显示出一个删除按钮，点击按钮就会删除相应数据的功能。<br>
delete_button.xml文件

```
<?xml version="1.0" encoding="utf-8"?>  
<Button xmlns:android="http://schemas.android.com/apk/res/android"  
    android:id="@+id/delete_button"  
    android:layout_width="wrap_content"  
    android:layout_height="wrap_content"  
    android:background="@drawable/delete_button" >  
</Button> 
```
MyListView继承自ListView，这就是我们自定义的View

```
public class MyListView extends ListView implements OnTouchListener,  
        OnGestureListener {  
  
    private GestureDetector gestureDetector;  
  
    private OnDeleteListener listener;  
  
    private View deleteButton;  
  
    private ViewGroup itemLayout;  
  
    private int selectedItem;  
  
    private boolean isDeleteShown;  
  
    public MyListView(Context context, AttributeSet attrs) {  
        super(context, attrs);  
        gestureDetector = new GestureDetector(getContext(), this);  
        setOnTouchListener(this);  
    }  
  
    public void setOnDeleteListener(OnDeleteListener l) {  
        listener = l;  
    }  
  
    @Override  
    public boolean onTouch(View v, MotionEvent event) {  
        if (isDeleteShown) {  
            itemLayout.removeView(deleteButton);  
            deleteButton = null;  
            isDeleteShown = false;  
            return false;  
        } else {  
            return gestureDetector.onTouchEvent(event);  
        }  
    }  
  
    @Override  
    public boolean onDown(MotionEvent e) {  
        if (!isDeleteShown) {  
            selectedItem = pointToPosition((int) e.getX(), (int) e.getY());  
        }  
        return false;  
    }  
  
    @Override  
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX,  
            float velocityY) {  
        if (!isDeleteShown && Math.abs(velocityX) > Math.abs(velocityY)) {  
            deleteButton = LayoutInflater.from(getContext()).inflate(  
                    R.layout.delete_button, null);  
            deleteButton.setOnClickListener(new OnClickListener() {  
                @Override  
                public void onClick(View v) {  
                    itemLayout.removeView(deleteButton);  
                    deleteButton = null;  
                    isDeleteShown = false;  
                    listener.onDelete(selectedItem);  
                }  
            });  
            itemLayout = (ViewGroup) getChildAt(selectedItem  
                    - getFirstVisiblePosition());  
            RelativeLayout.LayoutParams params = new RelativeLayout.LayoutParams(  
                    LayoutParams.WRAP_CONTENT, LayoutParams.WRAP_CONTENT);  
            params.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);  
            params.addRule(RelativeLayout.CENTER_VERTICAL);  
            itemLayout.addView(deleteButton, params);  
            isDeleteShown = true;  
        }  
        return false;  
    }  
  
    @Override  
    public boolean onSingleTapUp(MotionEvent e) {  
        return false;  
    }  
  
    @Override  
    public void onShowPress(MotionEvent e) {  
  
    }  
  
    @Override  
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX,  
            float distanceY) {  
        return false;  
    }  
  
    @Override  
    public void onLongPress(MotionEvent e) {  
    }  
      
    public interface OnDeleteListener {  
  
        void onDelete(int index);  
  
    }  
  
}  
```
这里在MyListView的构造方法中创建了一个GestureDetector的实例用于监听手势，然后给MyListView注册了touch监听事件。然后在onTouch()方法中进行判断，如果删除按钮已经显示了，就将它移除掉，如果删除按钮没有显示，就使用GestureDetector来处理当前手势。

当手指按下时，会调用OnGestureListener的onDown()方法，在这里通过pointToPosition()方法来判断出当前选中的是ListView的哪一行。当手指快速滑动时，会调用onFling()方法，在这里会去加载delete_button.xml这个布局，然后将删除按钮添加到当前选中的那一行item上。注意，我们还给删除按钮添加了一个点击事件，当点击了删除按钮时就会回调onDeleteListener的onDelete()方法，在回调方法中应该去处理具体的删除操作。


**view初始化 构造函数**<br>
**onMeasure 测量view大小**<br>
**onSizeChanged 确定view大小**<br>
**onLayout 确定子view布局**<br>
**onDraw 实际绘制内容**<br>
**invalidate 刷新内容**<br>

https://github.com/GcsSloop/AndroidNote/blob/master/CustomView/Advance/%5B01%5DCustomViewProcess.md
