#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

//重点
//结构体
//1.结构体类型的声明
//2.结构的自引用
//3.结构体变量的定义和初始化
//4.结构体内存对齐
//5.结构体传参
//6.结构体实现位段(位段的填充&可移植性)

//枚举
//1.枚举类型的定义
//2.枚举的优点
//3.枚举的使用

//联合
//联合类型的定义
//联合的特点
//联合大小的计算


//自定义数据类型 - 结构体

//1.结构体的声明
//结构体的基本知识:结构是一些值的集合,这些值称为成员变量.结构的每个成员可以是不同类型的变量

//结构的声明
/*struct tag
{
	member - list;
}variable - list;*/


//例:声明一个结构体类型
//声明一个学生类型,是想通过学生类型来创建学生变量(对象)
//描述学生:属性 - 名字+电话+性别+年龄
struct Stu
{
	char name[20];//名字
	char tele[12];//电话
	char sex[10];//性别
	int age;//年龄
}s4,s5,s6;
//s4,s5,s6也是全局变量
struct s3;//全局变量


//特殊的声明
//匿名结构体类型 - 省略了结构体标签(tag)
struct
{
	int a;
	char b;
	float c;
}x; //只有在这里创建的全局变量才可以使用,匿名结构体类型在main()函数里无法再创建局部变量

struct
{
	int a;
	char b;
	float c;
}*p; //此时p就为结构体指针

//若p = &x; 是不合法的,虽然两个结构体类型内容相同,但是编译器会把两个声明当成完全不同的两个类型

int main()
{
	struct Stu s1; //创建的结构体变量(局部变量)
	struct Stu s2;
	return 0;
}



//2.结构体的自引用

struct Node
{
	int data;
	struct Node n; //error,内存太大sizeof()无法确定
};

struct Node
{
	int data;
	struct Node*next; //将链表的各个元素分为两部分,一部分存放内容,一部分存放下一个元素的地址(最后一个元素存放NULL)
	//存放内容的部分被称为数据域,next中存放指针的地方被称为指针域
};

typedef struct Node
{
	int data;
	struct Node*next;  //corr
}Node;

typedef struct 
{
	int data;
    Node*next;  //err 此时的成员变量内部用的Node还未定义
}Node;

int main()
{
	struct Node n1;
	Node n2;  //此时两种形式都可以创建局部变量
	return 0;
}

