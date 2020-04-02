### 安装
[官网](https://www.tensorflow.org/)<br>
四种方式 <br>
1. virtualenv  <br>
2. "native" pip <br>
3. Docker <br>
4. installing from sources <br>

#### "native" pip方式安装
当您安装python时，pip或pip3可能安装在您的系统上。你也可以访问如下地址进行安装pip：<br>
https://pip.pypa.io/en/latest/installing/<br>

```
curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py

python get-pip.py

```
要确定您的系统上是否实际安装了pip或pip3，请输入以下命令之一查看版本：

```
pip -V  # for Python 2.7
pip3 -V # for Python 3.n 

```
**pip版本最好在8.1以上**<br>
##### 升级pip 

```
sudo easy_install --upgrade pip
sudo easy_install --upgrade six 
```

#####安装 tensorflow

```
pip install tensorflow      # Python 2.7; CPU support
pip3 install tensorflow     # Python 3.n; CPU support
```

**如果安装失败,进行如下方式安装**

```
sudo pip  install --upgrade tfBinaryURL   # Python 2.7
sudo pip3 install --upgrade tfBinaryURL   # Python 3.n 
```
其中tfbinaryurl标识tensorflow python包的url，tfbinaryurl的适当值取决于操作系统和python版本，Python 3.4, 3.5, or 3.6 的tfbinaryurl如下：<br>
https://storage.googleapis.com/tensorflow/mac/cpu/tensorflow-1.4.1-py3-none-any.whl

##### 卸载tensorflow

```
pip uninstall tensorflow
pip3 uninstall tensorflow 
```


##### 验证安装
在python交互式shell中输入下面的短程序：

```
# Python
import tensorflow as tf
hello = tf.constant('Hello, TensorFlow!')
sess = tf.Session()
print(sess.run(hello))
```
输出:<br>
Hello, TensorFlow!


```
➜  ~ python3
Python 3.6.4 (default, Dec 25 2017, 14:57:46)
[GCC 4.2.1 Compatible Apple LLVM 9.0.0 (clang-900.0.39.2)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> # Python
... import tensorflow as tf
/usr/local/Cellar/python3/3.6.4/Frameworks/Python.framework/Versions/3.6/lib/python3.6/importlib/_bootstrap.py:219: RuntimeWarning: compiletime version 3.5 of module 'tensorflow.python.framework.fast_tensor_util' does not match runtime version 3.6
  return f(*args, **kwds)
>>> hello = tf.constant('Hello, TensorFlow!')
>>> sess = tf.Session()
2018-01-18 20:22:59.680810: I tensorflow/core/platform/cpu_feature_guard.cc:137] Your CPU supports instructions that this TensorFlow binary was not compiled to use: SSE4.1 SSE4.2 AVX AVX2 FMA
>>> print(sess.run(hello))
b'Hello, TensorFlow!'
>>>
```

