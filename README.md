
### 简介

在Android7.0以及以上的版本中，dlfcn.h头文件中dlopen, dlsym函数已经无法在系统库上使用。
比较常见的规避方法是，先通过maps文件找到so文件对应起始地址，然后通过解析elf 文件，得到函数的偏移量，起始地址加上偏移量就算出函数的真实地址。
具体实现方式是：[Nougat_dlfunctions](https://github.com/avs333/Nougat_dlfunctions)。不过，这种方法偶尔会不太靠谱，要么是起始地址计算错误，要么是偏移量计算不准确。

这里，通过修改入口函数的LR寄存器的值，欺骗系统这是从系统库里发起调用的，从而实现绕过调用的限制。

### 支持版本

Android 4,5,6,7,8,9,10,11

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

### 致谢

1. [Nougat_dlfunctions](https://github.com/avs333/Nougat_dlfunctions)