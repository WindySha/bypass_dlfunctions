#include <jni.h>
#include <string>
#include <vector>
#include <android/log.h>
#include "bypass_dlfcn.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "Test_DlFunctions", __VA_ARGS__)

template<typename ...Args>
inline std::string format_string(const char *format, Args... args) {
    constexpr size_t oldlen = BUFSIZ;
    char buffer[oldlen];
    size_t newlen = snprintf(&buffer[0], oldlen, format, args...);
    newlen++;
    if (newlen > oldlen) {
        std::vector<char> newbuffer(newlen);
        snprintf(newbuffer.data(), newlen, format, args...);
        return std::string(newbuffer.data());
    }
    return buffer;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_bypass_dlfunctions_MainActivity_test_1bypass_1dlfcn(
    JNIEnv *env, jclass clazz) {

    std::string so_file_name = "libart.so";
    std::string target_function_name = "_ZN3art10ObjectLockINS_6mirror6ObjectEED2Ev";

    void *handle = bp_dlopen(so_file_name.c_str(), RTLD_NOW);

    void *func_address = bp_dlsym(handle, target_function_name.c_str());

    LOGD(" bypass dlopen, dlopen result: %p,  dlsym result: %p", handle, func_address);

    Dl_info info;
    bp_dladdr(func_address, &info);

    std::string result;
    result += info.dli_fname;
    result += format_string(" dlopen result: %p", handle);
    result += "\n";
    result += "function name: ";
    result += info.dli_sname;
    result += "\n";
    result += format_string(" dlsym result: %p", func_address);

    LOGD(" result: \n %s", result.c_str());

    return env->NewStringUTF(result.c_str());
}