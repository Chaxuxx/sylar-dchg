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
```
WSL:Ubuntu
gcc 9.4.0
gdb 9.2
cmake 3.16.3
mysql 8.0.32
```

# 模块结构

## 日志系统

Log4J 用C++复现

支持流式日志风格写日志和格式化风格写日志，支持日志格式自定义，日志级别，多日志分离等等功能

流式日志使用：SYLAR_LOG_INFO(g_logger) << “this is a log”;

格式化日志使用：SYLAR_LOG_FMT_INFO(g_logger, “%s”, “this is a log”);

支持时间,线程id,线程名称,日志级别,日志名称,文件名,行号等内容的自由配置

## 配置系统

使用yaml  yaml-cpp

采用约定由于配置的思想。

定义即可使用。不需要单独去解析。

支持变更通知功能。

使用YAML文件做为配置内容。

支持级别格式的数据类型，支持STL容器(vector,list,set,map等等),支持自定义类型的支持（需要实现序列化和反序列化方法）

## 线程模块

    线程库选择:
    C++11中提供了std::thread, std::mutex, std::condition_variable等线程相关的类。但是还是不够完善，比如没有提供读写锁。没有提供spinlock，虽然c++11里面的atomic可以用来实现CAS锁。
    对于高并发服务器来说，很多数据，大多数时候，都是写少读多的场景。如果没有读写锁的话，那么性能上的损失会非常大。
    我们开发的这个框架定位是高并发的服务器框架，因此我们还是使用pthread库来开发（其实c++11里面的thread也是pthread提供的）

线程类、信号量、互斥量

封装了pthread里面的一些常用功能，Thread,Semaphore,Mutex,RWMutex,Spinlock等对象，可以方便开发中对线程日常使用

为什么不适用c++11里面的thread

本框架是使用C++11开发，不使用thread，是因为thread其实也是基于pthread实现的。并且C++11里面没有提供读写互斥量，RWMutex，Spinlock等，在高并发场景，这些对象是经常需要用到的。所以选择了自己封装pthread

## 协程、协程调度
协程：用户态的线程，相当于线程中的线程，更轻量级。后续配置socket hook，可以把复杂的异步调用，封装成同步操作。降低业务逻辑的编写复杂度。

目前该协程是基于ucontext_t来实现的，后续将支持采用boost.context里面的fcontext_t的方式实现

协程调度器，管理协程的调度，内部实现为一个线程池，支持协程在多线程中切换，也可以指定协程在固定的线程中执行。是一个N-M的协程调度模型，N个线程，M个协程。重复利用每一个线程。

## IO协程调度模块

继承与协程调度器，封装了epoll（Linux），并支持定时器功能（使用epoll实现定时器，精度毫秒级）,支持Socket读写时间的添加，删除，取消功能。支持一次性定时器，循环定时器，条件定时器等功能

## Hook模块

hook系统底层和socket相关的API，socket io相关的API，以及sleep系列的API。hook的开启控制是线程粒度的。可以自由选择。通过hook模块，可以使一些不具异步功能的API，展现出异步的性能。如（mysql）

## Socket模块

封装了Socket类，提供所有socket API功能，统一封装了地址类，将IPv4，IPv6，Unix地址统一起来。并且提供域名，IP解析功能。

## ByteArry序列化模块
ByteArray二进制序列化模块，提供对二进制数据的常用操作。读写入基础类型int8_t,int16_t,int32_t,int64_t等，支持Varint,std::string的读写支持,支持字节序转化,支持序列化到文件，以及从文件反序列化等功能

## TCPserver模块
基于Socket类，封装了一个通用的TcpServer的服务器类，提供简单的API，使用便捷，可以快速绑定一个或多个地址，启动服务，监听端口，accept连接，处理socket连接等功能。具体业务功能更的服务器实现，只需要继承该类就可以快速实现

## Stream模块
封装流式的统一接口。将文件，socket封装成统一的接口。使用的时候，采用统一的风格操作。基于统一的风格，可以提供更灵活的扩展。目前实现了SocketStream

## HTTP模块
采用Ragel（有限状态机，性能媲美汇编），实现了HTTP/1.1的简单协议实现和uri的解析。基于SocketStream实现了HttpConnection(HTTP的客户端)和HttpSession（HTTP服务器端的链接）。基于TcpServer实现了HttpServer。提供了完整的HTTP的客户端API请求功能，HTTP基础API服务器功能

## Servlet模块
仿照java的servlet，实现了一套Servlet接口，实现了ServletDispatch，FunctionServlet。NotFoundServlet。支持uri的精准匹配，模糊匹配等功能。和HTTP模块，一起提供HTTP服务器功能