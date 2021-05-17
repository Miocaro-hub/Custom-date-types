#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//3.结构体变量的定义和初始化
struct Point
{
	int x;
	int y;
}p1;             //声明类型的同时定义变量p1
struct Point p2; //定义结构体变量p2

//初始化:定义变量的同时进行赋值
struct T
{
	double weight;
	short age;
};

struct S
{
	char c;
	struct T st;
	int a;
	double d;
	char arr[20];
};

int main()
{
	struct S s = { 'c',{55.6,30},100,3.14,"hello world" };
	printf("%c %d %lf %s\n", s.c, s.a, s.d, s.arr); //结构体类型成员变量访问:s.(.表示访问)
	printf("lf\n", s.st.weight); //可以打印结构体中的结构体类型中的数据
	return 0;
}


//4.结构体内存对齐
//结构体的对齐规则:
//1.第一个成员在结构体变量偏移量为0的地址处
//2.其他成员变量要对齐到某个数字(对齐数)的整数倍的地址处
//对齐数 = 编译器默认的一个对齐数 与 该成员大小的较小值(VS默认的值为8)
//3.结构体总大小为最大对齐数(每个成员变量都有一个对齐数)的整数倍
//4.如果嵌套了结构体的情况,嵌套的结构体对齐到自己的最大对齐数的整数倍处,结构体的整体大小就是所有最大对齐数(含嵌套结构体的对齐数)的整数倍
struct S1
{
	char c1; //存放的位置为偏移量为0的地址,占1个字节
	int a;   //占4个字节,与VS默认的对齐数8对比取小的,所以对齐数为4
	         //又要存放到对齐数整数倍的地址,所以存放的偏移量地址4开始,占4个字节
	char c2; //同理,对齐数取1,下面任意一个地址都是1的倍数,存放的偏移量地址为9,占1个字节
	         //此时所占的空间为9个字节,但因为最大对齐数为4,9不是4的倍数,下一个4的倍数为偏移量地址12,所以又浪费3个字节,所占总内存大小为12
};

struct S1
{
	char c1; //存放的位置为偏移量为0的地址,占1个字节
	char c2; //对齐数取1,从偏移量为2的地址开始存放,占1个字节
	int a;   //对齐数取4,从偏移量为4的地址开始,占4个字节   //此时内存占的总字节为8,最大对齐数为4,8正好是4的倍数,不用再浪费空间,这是内存总大小就是8个字节
};

int main()
{
	struct S1 s1 = { 0 };
	printf("%d\n", sizeof(s1)); //12
	struct S1 s2 = { 0 };
	printf("%d\n", sizeof(s2)); //8
	return 0;
}
//并不是所有编译器都有对齐数(gcc没有对齐数),没有默认对齐数的情况下,该成员的大小就是对齐数

//练习1:
struct S3
{
	double d; //8个字节
	char c;
	int i;
};
printf("%d\n", sizeof(struct S3)); //16

//练习2:
struct S4 
{
	char c1;
	struct S3 s3;
	double d;
};
printf("%d\n", sizeof(struct s4)); //32

//存在内存对齐的意义
//1.平台原因:不是所有的硬件平台都能访问任意地址上的任意数据的;某些硬件平台只能在某些地址处取得特定类型的数据,否则抛出硬件异常
//2.性能原因:数据结构(尤其是栈)应该尽可能地在自然边界上对齐.原因在于,为了访问未对齐地内存,处理器需要作两次内存访问;而对齐的内存访问仅需要一次访问
//总体来说:结构体的内存对齐是拿空间来换取时间的做法


//那在设计结构体的时候,我们既要满足对齐,又要节省空间:
//可以让占用空间小的成员尽量集中在一起


//修改默认对齐数
//#pragma预处理指令,可以改变默认对齐数
#pragma pack(4) //表示设置默认对齐数为4
struct S
{
	char c1;
	double d;
};
#pragma pack()  //表示取消设置的默认对齐数
printf("%d\n", sizeof(struct S));
//结论:结构在对齐方式不合适的时候,我们可以自己更改默认对齐数


#include<stddef.h>
struct S
{
	char c;
	int i;
	double d;
};
int main()
{
	//offsetof(); 计算偏移量(offsetof不是函数,是一种宏)
	printf("%d\n", offsetof(struct S, c));  //0
	printf("%d\n", offsetof(struct S, i));  //4
	printf("%d\n", offsetof(struct S, d));  //8
	return 0;
}
//此处可以引申出一个百度的面试题:写一个宏,计算结构体中某变量相对于首地址的偏移,并给出说明
//考察的就是offsetof宏的实现
