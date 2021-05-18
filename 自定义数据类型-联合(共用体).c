#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//联合
//1.联合类型的定义
//2.联合的特点
//3.联合大小的计算


//1.联合类型的定义
//联合也是一种特殊的自定义类型,这种类型定义的变量也包含一系列的成员,特征是这些成员共用同一块空间(所以联合也叫共用体)
//例如:

union Un
{
	char c;
	int i;
};
int main()
{
	union Un u;
	printf("%d\n", sizeof(u)); //打印的结果为4个字节

	printf("%p\n", &(u.c));
	printf("%p\n", &(u.i));  //此时三个地址的打印结果为一致的
	printf("%p\n", &u);
	return 0;
}


//2.联合的特点
//联合的成员是共用同一块内存空间的,这样一个联合变量的大小,至少是最大成员的大小(因为联合至少得有能力保存最大的那个成员)

union Un
{
	char c;
	int i;
};
int main()
{
	union Un un;

	//下面的输出结果是什么
	un.i = 0x11223344;
	un.c = 0x55;
	printf("%x\n", un.i); //11223344
	printf("%x\n", un.c); //55
	return 0;
}

//还是那道面试题:判断当前计算机的大小端存储
int check_sys()
{
	int a = 1;
	return *(char*)&a;
}
int main()
{
	int a = 1;
	int ret = check_sys();
	if (ret == 1)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	//int a = 0x11 22 33 44;
	//低地址-------------------------高地址
	//....[][][][][11][22][33][44][][][][]....  大端字节序存储模式(数据的低位存在高地址,数据的高位存在低地址)
	//....[][][][][44][33][22][11][][][][]....  小端
	//讨论一个数据存放在内存中的字节顺序
	//大小端字节序问题

	return 0;
}


//如何利用联合体类型实现
int check_sys()
{
	union Un
	{
		int i;
		char c;
	}u;
	u.i = 1; //此时会涉及到大小端的存储问题
	return u.c; // 返回1表示小端,返回0表示大端
}
int main()
{
	int a = 1;
	int ret = check_sys();
	if (ret == 1)
	{
		printf("小端\n");
	}
	else
	{
		printf("大端\n");
	}
	return 0;
}



//3.联合大小的计算
//联合的大小至少是最大成员的大小
//当最大成员不是最大对齐数的整数倍的时候,就要对齐到最大对齐数的整数倍

//例如:
union Un
{
	int a; //4个字节,对齐数为4
	char arr[5]; //5个字节,对齐数不是以数组来算,是以数组中每个元素的大小来算,所以对齐数为1
};
int main()
{
	union Un u;
	printf("%d\n", sizeof(u)); //大小是至少最大成员的大小,且要对齐到最大对齐数的整数倍,所以最终打印的结果为8
	return 0;
}