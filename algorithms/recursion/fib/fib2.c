#include <stdio.h>

int fib(int i)
{
    int tmp;
    if(i == 0){
        return 0;
    }
    if((i == 1) ||(i==2)){
        return 1;
    }

    return fib(i-1)+fib(i-2);
}


int main(int argc,char** argv)
{
    int i;
    i = fib(10);
    printf("i:%d ",i);

    return 0;
}