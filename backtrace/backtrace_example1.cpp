#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <cxxabi.h>
#include <string.h>


// ��������ӡ�������ö�ջ��Ϣ
void printStackTrace()
{
    const int max_frames = 20;
    void* frames[max_frames];

    // ��ȡ�������ö�ջ��Ϣ
    int numFrames = backtrace(frames, max_frames);

    // ����ջ��Ϣת��Ϊ�ַ���
    char** symbols = backtrace_symbols(frames, numFrames);

    // ��ӡ�������������ö�ջ��Ϣ
    if (symbols != nullptr)
    {
        printf("Function call stack:\n");
        for (int i = 0; i < numFrames; ++i)
        {
            printf("[%d] %s\n", i, symbols[i]);

            // �������������ļ������кŵ���Ϣ
            char* symbol = symbols[i];

            // ������������λ����������֮�䣩
            char* functionNameStart = strchr(symbol, '(');
            char* functionNameEnd = strchr(symbol, '+');
            if (functionNameStart != nullptr && functionNameEnd != nullptr)
            {
                *functionNameEnd = '\0'; // ��ʱ�ض��ַ���
                printf("    Function: %s\n", functionNameStart + 1);
                *functionNameEnd = '+'; // �ָ��ַ���
            }

            // �����ļ������кţ�λ�����������Ĳ��֣�
            char* fileLineNumberStart = strchr(symbol, '(');
            char* fileLineNumberEnd = strrchr(symbol, ')');
            if (fileLineNumberStart != nullptr && fileLineNumberEnd != nullptr)
            {
                *fileLineNumberEnd = '\0'; // ��ʱ�ض��ַ���
                printf("    File: %s\n", fileLineNumberStart + 1);
                *fileLineNumberEnd = ')'; // �ָ��ַ���
            }
        }
        free(symbols);
    }
}

// ����b�������δ���
void funcB()
{
    // int* pointer = nullptr;
    // *pointer = 42;

    printStackTrace();
}

// ����a�����ú���b
void funcA()
{
    funcB();
}

int main()
{
    funcA();
    return 0;
}