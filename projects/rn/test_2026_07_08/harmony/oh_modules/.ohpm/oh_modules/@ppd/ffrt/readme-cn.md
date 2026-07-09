# ffrt

## 简介

ffrt 是 FFRT C++ 接口的封装，提供 FFRT C++ 接口和接口使用文档说明。

## 使用指南

FFRT C++ 接口使用指南可以参考开源社区文档（[Function Flow Runtime C++ API](https://gitee.com/openharmony/resourceschedule_ffrt/blob/master/docs/ffrt-api-guideline-cpp.md)）。

## 下载安装

```shell
ohpm install @ppd/ffrt
```

OpenHarmony ohpm 环境配置等更多内容，请参考[如何安装 OpenHarmony ohpm 包](https://gitee.com/openharmony-tpc/docs/blob/master/OpenHarmony_har_usage.md)

## 接口列表

- cpp/pattern/job_partner.h
- cpp/condition_variable.h
- cpp/mutex.h
- cpp/queue.h
- cpp/shared_mutex.h
- cpp/sleep.h
- cpp/task.h

## 使用示例

### 一、设置三方包依赖信息

在 Terminal 窗口中，切换到需要引入三方包的模块，执行 `ohpm install @ppd/ffrt` 命令安装三方包，DevEco Studio 会自动在工程的 `oh-package.json5` 中自动添加三方包依赖。

### 二、在 CMakeLists.txt 中增加头文件包含路径

```cmake
include_directories(${MODULES_PATH}/@ppd/ffrt/include)
```

> NOTE
>
> 变量 `MODULES_PATH` 表示三方库安装位置，需要开发者自己定义或者直接替换成绝对路径或者相对路径。
>
> 例如：`${NATIVERENDER_ROOT_PATH}/oh_modules/@ppd/ffrt/include`

### 三、在 CMakeLists.txt 中增加链接依赖

```cmake
target_link_libraries(entry PUBLIC libffrt.z.so)
```

### 四、在 C++ 代码中引入头文件，然后调用对应的 C++ 接口

```cpp
// include all C or C++ header files
#include "ffrt/ffrt.h"

// include specified header files
#include "ffrt/cpp/pattern/job_partner.h"
#include "ffrt/cpp/task.h"
#include "ffrt/cpp/mutex.h"
#include "ffrt/cpp/shared_mutex.h"
#include "ffrt/cpp/condition_variable.h"
#include "ffrt/cpp/sleep.h"
#include "ffrt/cpp/queue.h"
```

## 使用说明

> 最低兼容 SDK 版本：API 12
