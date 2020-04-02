---
title: Python虚拟环境
date: 2018-04-05 14:46:45
tags: python
categories: python
---

#### 安装 virtualenv
Python 3 中还自带了虚拟环境管理包。

```
pip3 install virtualenv
virtualenv --version
```

#### 基本用法
虚拟环境中不会包含也无法使用系统环境的global site-packages。比如系统环境里安装了 requests 模块，在虚拟环境里import requests会提示ImportError。如果想使用系统环境的第三方软件包，可以在创建虚拟环境时使用参数–system-site-packages

```
#创建虚拟环境
cd project_dir
virtualenv venv #venv虚拟环境名称
#使用系统的环境包创建
virtualenv --system-site-packages venv 
#进入虚拟环境并启动
cd venv
source bin/activate
python -V
#退出虚拟环境
deactivate
#如果项目开发完成后想删除虚拟环境，直接删除虚拟环境目录即可
```

#### virtualenvwrapper
