#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cxxabi.h>
void printStackTrace()
{
    const int max_frames = 20;
    void* frames[max_frames];
    
    // 获取函数调用堆栈信息
    int numFrames = backtrace(frames, max_frames);
    
    // 将堆栈信息转换为字符串
    char** symbols = backtrace_symbols(frames, numFrames);
    
    if (symbols != nullptr)
    {
        printf("Function call stack:\n");
        
        for (int i = 0; i < numFrames; ++i)
        {
            Dl_info info;
            printf("[%d] %s\n", i, symbols[i]);


            // 解析函数符号信息
            if (dladdr(frames[i], &info) && info.dli_sname != nullptr)
            {
                char* demangledName = nullptr;
                int status = 0;
                
                // 对函数名进行解码
                demangledName = abi::__cxa_demangle(info.dli_sname, nullptr, nullptr, &status);
                
                if (status == 0 && demangledName != nullptr)
                {
                    printf("[%d] Function: %s\n", i, demangledName);
                    printf("    File: %s\n", info.dli_fname);
                    int value = (char*)(info.dli_saddr) - (char*)frames[i];

                    printf("    Line: %d\n", value);
                    free(demangledName);
                }
            }
            
            
        }
        
        free(symbols);
    }
}

void funcC()
{
    printStackTrace();



}

void funcB()
{
    funcC();
}

void funcA()
{
    funcB();


}

int main()
{
    funcA();


    return 0;
}