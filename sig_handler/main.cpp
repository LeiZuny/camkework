#include <iostream>
#include <csignal>
#include <signal.h>
#include <vector>
#include <unistd.h>

#include "backtracecxa.h"
// �źŴ�����
void signalHandler(int sig)
{
    std::cout << "Received signal: " << sig << " (Segmentation fault)" << std::endl;

    std::cout <<"-----------backtrace begin ---------<<"<<std::endl;
    
    funcA();
    std::cout <<"-----------backtrace end ---------<<"<<std::endl;
    exit(sig);
}


void  num11()
{
    int *a = nullptr;
    std::vector<int> vec1 (5, 0);
    for(int i = 0; i < 10; i ++)
    {
        std::cout << vec1[i] << std::endl;

        if(i == 5)
        {
            *a = 10;
        }
        sleep(1);
    }
}


int main()
{
    // ע���źŴ�����
    signal(SIGSEGV, signalHandler);  // ����δ����ź�
    signal(SIGINT, signalHandler);
    num11();
    while(1);
    return 0;
}
//g++ -g  -rdynamic  backtracecxa.cpp  main.cpp  -ldl  -o  back_trace_main