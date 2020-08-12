#include <stdio.h>
#include <stdlib.h>

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

struct zeroa{
    int a;
    int b;
    int data[];
};

/*
 *int myint(int a,int b)
 *{
 *    return a*b;
 *}
 *const int itmp = myint(1,2);	//error| initializer element is not constant
 */

struct weather {
    int tmp;
    int type;
};

static struct weather __attribute__((__used__)) __attribute__((__aligned__(4)))  myweather_1;

int myweather_1_a;
int myweather_1_a = 3;

static struct weather __attribute__((__used__)) __attribute__((__aligned__(4)))  myweather_1 = {
    .tmp = 10,
    .type = 1,
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

    int *pint;
    printf("sizeof(int):%d\n",sizeof(int));
    printf("sizeof(pint):%d\n",sizeof(pint));
    printf("sizeof(*pint):%d\n",sizeof(*pint));
    printf("sizeof(long):%d\n",sizeof(long));
    printf("sizeof(void*):%d\n",sizeof(void*));
    printf("sizeof(long long):%d\n",sizeof(long long));
    printf("sizeof(unsigned int):%d\n",sizeof(unsigned int));
    printf("sizeof(unsigned long):%d\n",sizeof(unsigned long));
    printf("sizeof(unsigned long int):%d\n",sizeof(unsigned long int));
    printf("sizeof(unsigned short int):%d\n",sizeof(unsigned short int));

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

    printf("sizeof(zeroa):%d\n",sizeof(struct zeroa));
    struct zeroa zeroa_a;
    printf("sizeof(zeroa_a):%d\n",sizeof(zeroa_a));

    struct zeroa *pzeroa;
    printf("sizeof(pzeroa):%d\n",sizeof(pzeroa));
    printf("sizeof(*pzeroa):%d\n",sizeof(*pzeroa));
    pzeroa = malloc(sizeof(*pzeroa)+8*sizeof(int));
    printf("sizeof(pzeroa).2:%d\n",sizeof(pzeroa));
	/*
	 *pzero 无法精确反映size,需要自己记录
	 */
    pzeroa->data[2] = 5;
    printf("pzeroa:%p\n",pzeroa);
    printf("pzeroa->data[2]:%d\n",pzeroa->data[2]);
    printf("&pzeroa->data[2]:%p\n",&pzeroa->data[2]);
	/*
	 *&pzeroa->data[2] = pzeroa+4(int a)+4(intb)+4(int data[0])+4(int data[1])
	 */

/*
 *    unsigned short int ntu=50;
 *    unsigned short int cnt=64;
 *    unsigned short int delt=100;
 *
 */
    int ntu=50;
    int cnt=64;
    int delt=100;

    ntu -= cnt;
    printf("ntu: %d\n",ntu);

    do {
        ntu++;
        if(!ntu){
            break;
        }
    } while(delt--);

    printf("ntu: %d,delt:%d\n",ntu,delt);


    return 0;
}
