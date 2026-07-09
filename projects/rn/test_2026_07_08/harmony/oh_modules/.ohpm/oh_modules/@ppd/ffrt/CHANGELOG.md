# Changelog

## v1.0.0

对外提供FFRT C++接口，具体接口如下：

- cpp/condition_variable.h
- cpp/mutex.h
- cpp/queue.h
- cpp/sleep.h
- cpp/task.h

## v1.0.1

- 指定接口文件目录headerPath

## v1.0.2

- 更新README.md文件中的使用方法。

## v1.0.3

- README.md中新增适用SDK版本信息。

## v1.0.4

- cpp/queue.h新增获取主队列接口`get_main_queue()`

## v1.0.5

- 统一路径为`"ffrt/cpp/xxx.h"`

## v1.0.6

- ffrt.h新增loop.h头文件

## v1.0.7

- 修改最低兼容SDK版本为API 12。
- C++头文件增加doxygen注释。
- 更改`@ppd/ffrt`为纯头文件har包，去除二进制内容，建议从此版本开始使用。

## v1.0.8

- 增加cpp/shared_mutex.h读写锁头文件。

## v1.0.9

- 增加FFRT C++接口使用指南文档链接。

## v1.1.0

- 增加FFRT JobPartner并发范式C++接口。

## v1.1.1

- 队列任务支持以线程模式运行。

## v1.1.2

- 增加FFRT JobRing并发范式C++接口。
- JobPartner代码优化。

## v1.1.3

- 增加FFRT task_handle拷贝构造和拷贝赋值接口。

## v1.1.4

- 修改`useNormalizedOHMUrl`配置。

## v1.1.5

- 增加动态加载so功能，适配二进制前向兼容。
- 增加so适配ohpm递归依赖解析。
