#include<iostream>

int a = 3;
int b = 7;

int add()
{
   return a + b;
}


int add_s(int c, int d)
{
    return c + d;
}
int main()
{
    int res = add_s(add(), b);
    std::cout << res<< std::endl;
    return 0;
}