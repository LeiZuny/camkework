#include<string.h>
#include<stdio.h>
#include<stdlib.h>
void getpidnum(char** str1)
{
    FILE* op;
    op = popen("pidof pid11", "r");
    fread(*str1, sizeof(*str1), 1, op);

    pclose(op);

    printf("the str1 value is %s", *str1);
}


int main()
{
    while(1)
    {
        char* str1 = (char*) malloc(10*sizeof(char));
        getpidnum(&str1);
        if(strlen(str1) == 0)
        {
            printf("the pid has been killed\n");
            break;
        } 
        system("kill $(pidof pid11)");
    }
    
    return 0;
}