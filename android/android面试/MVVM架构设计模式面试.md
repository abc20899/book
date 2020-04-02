1.Model层：实体模型。

2.View层：对应Activity和XML，负责View的绘制以及与用户交互。

3.ViewModel层：负责完成View与Model间的交互，负责业务逻辑。

View层不能做业务逻辑有关的事情，只能更新UI；ViewModel层只能做业务逻辑有关的事情，同时会根据View所提供的接口做数据交互。

![](img/mvvm.png)