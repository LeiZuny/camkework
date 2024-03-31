#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <cxxabi.h>
#include <string.h>


// 解析并打印函数调用堆栈信息
void printStackTrace()
{
    const int max_frames = 20;
    void* frames[max_frames];

    // 获取函数调用堆栈信息
    int numFrames = backtrace(frames, max_frames);

    // 将堆栈信息转换为字符串
    char** symbols = backtrace_symbols(frames, numFrames);

    // 打印并解析函数调用堆栈信息
    if (symbols != nullptr)
    {
        printf("Function call stack:\n");
        for (int i = 0; i < numFrames; ++i)
        {
            printf("[%d] %s\n", i, symbols[i]);

            // 解析函数名、文件名和行号等信息
            char* symbol = symbols[i];

            // 解析函数名（位于两个括号之间）
            char* functionNameStart = strchr(symbol, '(');
            char* functionNameEnd = strchr(symbol, '+');
            if (functionNameStart != nullptr && functionNameEnd != nullptr)
            {
                *functionNameEnd = '\0'; // 临时截断字符串
                printf("    Function: %s\n", functionNameStart + 1);
                *functionNameEnd = '+'; // 恢复字符串
            }

            // 解析文件名和行号（位于括号中最后的部分）
            char* fileLineNumberStart = strchr(symbol, '(');
            char* fileLineNumberEnd = strrchr(symbol, ')');
            if (fileLineNumberStart != nullptr && fileLineNumberEnd != nullptr)
            {
                *fileLineNumberEnd = '\0'; // 临时截断字符串
                printf("    File: %s\n", fileLineNumberStart + 1);
                *fileLineNumberEnd = ')'; // 恢复字符串
            }
        }
        free(symbols);
    }
}

// 函数b，触发段错误
void funcB()
{
    // int* pointer = nullptr;
    // *pointer = 42;

    printStackTrace();
}

// 函数a，调用函数b
void funcA()
{
    funcB();
}

int main()
{
    funcA();
    return 0;
}