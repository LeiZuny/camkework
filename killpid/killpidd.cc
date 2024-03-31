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
    char comd[20] = "kill ";
    char* str1 = (char*) malloc(10*sizeof(char));
    getpidnum(&str1);
    if(strlen(str1) == 0)
    {
        printf("the pid has been killed\n");
        return 0;
    } 
    printf("the ss1 is %s\n", str1);
    strcat(comd, str1);
    printf("the comd is %s\n", comd);
    system(comd);
    return 0;

}

