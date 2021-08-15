
### 简介

在Android7.0以及以上的版本中，dlfcn.h头文件中dlopen, dlsym函数已经无法在系统库上使用。

比较常见的规避方法是，先通过maps文件找到so文件对应起始地址，然后通过解析elf 文件，得到函数的偏移量，起始地址加上偏移量就算出函数的真实地址。

不过，这种方法搜索整个so文件，有时效率比较低。

这里提出另一个方案，是通过修改入口函数的LR寄存器的值，欺骗系统认为这是从系统库里发起调用的，从而实现绕过系统的限制。

### 支持版本

系统：Android 4-11

架构：Arm32和Arm64

### 使用
在cmake文件中引入：
```
set(bypass_dlfcn_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../../../lib)
add_subdirectory(${bypass_dlfcn_root_dir} bypasss_dlfcn)
include_directories(${bypass_dlfcn_root_dir}/include/)
target_link_libraries(
        your_lib
        bypass_dlfcn)
```
在代码中导入头文件:
```
#include "bypass_dlfcn.h"
```
使用头文件中的接口代替dlfcn.h中的接口:
```
void *bp_dlopen(const char *filename, int flag);
int bp_dlclose(void *handle);
const char *bp_dlerror(void);
void *bp_dlsym(void *handle, const char *symbol);
int bp_dladdr(const void *ddr, Dl_info *info);
```
### License
MIT License

### 实现原理
[另一种绕过Android系统库访问限制的方法](https://windysha.github.io/2021/05/26/%E5%8F%A6%E4%B8%80%E7%A7%8D%E7%BB%95%E8%BF%87Android%E7%B3%BB%E7%BB%9F%E5%BA%93%E8%AE%BF%E9%97%AE%E9%99%90%E5%88%B6%E7%9A%84%E6%96%B9%E6%B3%95/)

### 致谢

1. [Nougat_dlfunctions](https://github.com/avs333/Nougat_dlfunctions)
2. [ndk_dlopen](https://github.com/Rprop/ndk_dlopen)
