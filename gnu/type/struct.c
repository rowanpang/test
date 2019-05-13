#include<stdio.h>

/*
 *pangwz
 *    if arg... is none,'##'remove the pre ',',so dprintf("---\n") is ok!!! and '..,st' is also ok!!!
 */
#define dprintf(fmt,arg...) printf("pangwz"fmt,##arg)
/*
 *pangwz,
 *    after spread out there is a ',' so need one more arg,just dprintf("---\n") is error!!!.need dprintf("---\n",st);
 *#define dprintf(fmt,arg...) printf("pangwz "fmt,arg)
 *#define dprintf(fmt,...) printf("pangwz "fmt,__VA_ARGS__)
 */

typedef enum hostStatus {
    linked=0,
    agentRunning
} hostStatus_t;

#define stStr(st) #st

int hello(int ok){
    int doit=ok;
    printf("hello from the other side\n");
}

#define UPRINT(n) printf("%10s: %p, %#x\n",#n,&n,n)

/*
 *ref
 *    https://gcc.gnu.org/onlinedocs/gcc-9.1.0/gcc/Structure-Layout-Pragmas.html#Structure-Layout-Pragmas
 */
#pragma pack(4)		    //修改编译器对struct默认对齐规则.
#pragma pack(1)		    //same as -fpack-struct[=n]
struct alignTest{
    int a;
    char b;
    int c;
};

#pragma pack()		    //改回最早定义的pack(4)
struct alignTest2{
    int a;
    char b;
    int c;
};

int main(int argc,char** argv)
{
    struct st{
        char* str1;
        char* str2;
        char* str3;
    }st={
        "pangwz",
        "rowan",
        "inspur"
        };

    struct st_2{
        char str1[10];
        char str2[10];
        char str3[10];
    }st_2={
        "pangwz",
        "rowan",
        "inspur"
        };

    printf("sizeof(st_2):%d\n",sizeof(st_2));

    dprintf("---\n");
    dprintf("---\n",st);
    dprintf("---%s\n","macro test");

    printf("sizeof(long):%d\n",sizeof(long));
    printf("sizeof(long long):%d\n",sizeof(long long));
    printf("sizeof(unsigned long):%d\n",sizeof(unsigned long));
    printf("sizeof(unsigned long int):%d\n",sizeof(unsigned long int));
    printf("sizeof(unsigned short int):%d\n",sizeof(unsigned short int));
    printf("sizeof(unsigned int):%d\n",sizeof(unsigned int));
    printf("sizeof(void*):%d\n",sizeof(void*));

    st = st;

    union u_1{
        unsigned int sp_32;

        struct u_s_1{
            unsigned char a;
            unsigned char b;
            unsigned char c;
            unsigned char d;
            unsigned char e;
            unsigned char f;
        }sp_8;

        struct u_s_2{
            unsigned short int a;
            unsigned short int b;
            unsigned short int c;
        }sp_16;
    }u;

    u.sp_32 = 0x12345678;
    u.sp_16.c = 0x9abc;
    printf("sizeof(union u):%d\n",sizeof(u));
    printf("sizeof(union u.sp_8):%d\n",sizeof(u.sp_8));
    printf("sizeof(union u.sp_16):%d\n",sizeof(u.sp_16));
    printf("u.sp_8:%p\n",&u.sp_8);
    printf("u.sp_16:%p\n",&u.sp_16);

    printf("byteOrder:%s\n",u.sp_8.a == 0x78?"little endin":"big endin");
    UPRINT(u.sp_32);
    UPRINT(u.sp_8.a);
    UPRINT(u.sp_8.b);
    UPRINT(u.sp_8.c);
    UPRINT(u.sp_8.d);
    UPRINT(u.sp_8.e);
    UPRINT(u.sp_8.f);
    UPRINT(u.sp_16.a);
    UPRINT(u.sp_16.b);
    UPRINT(u.sp_16.c);

    char* pArray[]={ "a","b"};
    printf("sizeof(pArray):%d\n",sizeof(pArray)/sizeof(char*));

    int a = 2;
    _Bool testBool=3;
    _Bool testBool2=a;
    printf("sizeof(testBool):%d,value:%d\n",sizeof(testBool),testBool);
    printf("sizeof(testBool2):%d,value:%d\n",sizeof(testBool2),testBool2);

    hostStatus_t hst=agentRunning;
    printf("enum type status:%s,%d\n",stStr(agentRunning),agentRunning);


    hello(1);

    int S123 = 3;
    int $123 = 4;
    printf("$123:%d,S123:%d\n",$123,S123);
    int \u0024a = 5;
    printf("\u0024a:%d\n",\u0024a);
    printf("It's a !\n");

    char ca=200;
    printf("char-as-d:%d\n",ca);


    printf("-pack(4)-pack(1)---align Test---------\n");
    struct alignTest algin;
    printf("sizeof(alignTest):%d\n",sizeof(struct alignTest));
    UPRINT(algin.a);
    UPRINT(algin.b);
    UPRINT(algin.c);

    printf("-pack(4)-pack(1)-pack()-align Test---------\n");
    struct alignTest2 algin2;
    printf("sizeof(alignTest2):%d\n",sizeof(struct alignTest2));
    UPRINT(algin2.a);
    UPRINT(algin2.b);
    UPRINT(algin2.c);

    return 0;
}

