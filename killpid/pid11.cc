#include<iostream>
#include<unistd.h>
int main()
{
    int i = 0;
    while(1)
    {
        i++;
        sleep(1);
        std::cout<<i<<std::endl;
    }
    return 0;
}