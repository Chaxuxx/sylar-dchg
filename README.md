# sylar-dchg
copy and try to add sth on sylar 

在sylar网络框架的基础上尝试添加一些无伤大雅的功能。
当然，首先是copy并且理解sylar。
一些理解的笔记，就写在obsidian\findwork\sylar-dchg里了

- 按照sylar视频顺序逐步进行代码迁移和单元测试。
- 利用sylar搭建tinywebserver
- 添加线程池？（虽然有协程了）
- 添加时间轮

首先，整理大体的代码框架。复制一些博客中的内容过来。

[sylar的博客](http://www.sylar.top/blog/?p=94)

## 项目路径安排
```
bin              — 二进制文件
build            — 中间文件路径
cmake            — cmake函数文件夹
CMakeLists.txt
lib              — 库的输出路径
Makefile
sylar-dchg       — 源代码路径
tests            — 测试代码
```

## 开发环境
WSL:Ubuntu
gcc
cmake 

# 模块结构

## 日志系统

Log4J 用C++复现

## 配置系统

使用yaml
yaml-cpp

## 线程模块

    线程库选择:
    C++11中提供了std::thread, std::mutex, std::condition_variable等线程相关的类。但是还是不够完善，比如没有提供读写锁。没有提供spinlock，虽然c++11里面的atomic可以用来实现CAS锁。
    对于高并发服务器来说，很多数据，大多数时候，都是写少读多的场景。如果没有读写锁的话，那么性能上的损失会非常大。
    我们开发的这个框架定位是高并发的服务器框架，因此我们还是使用pthread库来开发（其实c++11里面的thread也是pthread提供的）


## 协程库封装


## socket函数库
## http协议开发
## 分布协议
## 推荐系统