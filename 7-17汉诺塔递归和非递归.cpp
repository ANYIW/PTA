//非递归：将递归时的形参组合成结构体，作为栈的元素
//将首元素压栈，栈不为空则不断弹栈，并判断是否符合递归终止条件，符合则输出
//不符合则继续递归，递归操作转换为压栈操作，不过顺序相反
#include <stdio.h>
#include <string.h>

//递归实现
void Print(char a,char b){
    static int i=1;
    if(i==1)
    i++;
    else printf("\n");
    printf("%c -> %c",a,b);
}
//将头n个盘从a移到c上，借助b
void Hanoi1(int n,char a,char b,char c){
    if(n==1)
    Print(a,c);
    else{
        Hanoi1(n-1,a,c,b);
        //将最底下的盘从a移到c
        Print(a,c);
        Hanoi1(n-1,b,a,c);
    }
}
int main(){
    int n;
    scanf("%d",&n);
    Hanoi2(n,'a','b','c');
    return 0;
}
//非递归实现
typedef struct
{
    //将n个盘从A移到C，借助B
    int n;
    char A;
    char B;
    char C;
}Element; //栈中元素类型
typedef struct{
    Element e[100];
    int top;
}Stack;
void Push(Stack* s,Element e){
    if(s!=NULL&&s->top!=99){
        s->e[++s->top]=e;
    }
}
Element Pop(Stack* s){
    if(s!=NULL&&s->top!=-1){
        return s->e[s->top--];
    }
}
int Empty(Stack* s){
    if(s!=NULL)
    return (s->top==-1);
}

void Hanoi2(int n,char a,char b,char c){
    Element tmp,toPush;
    Stack* ptr=(Stack*)malloc(sizeof(Stack));
    ptr->top=-1;
    tmp.n=n;
    tmp.A=a;
    tmp.B=b;
    tmp.C=c;
    Push(ptr,tmp);
    while(!Empty(ptr)){
        tmp=Pop(ptr);
        if(tmp.n==1)
        Print(tmp.A,tmp.C);
        else{
            //倒着写以下三步
            //将头n-1个盘从a移到b，借助c
            //将最底下的盘从a移到c
            //将头n-1个盘从b移到c，借助a

            //将头n-1个盘从b移到c，借助a
            toPush.n = tmp.n - 1;
            toPush.A = tmp.B;
            toPush.B = tmp.A;
            toPush.C = tmp.C;
            Push(ptr,toPush);

            //将最底下的盘从a移到c
            toPush.n=1;
            toPush.A=tmp.A;
            toPush.B=tmp.B;
            toPush.C=tmp.C;
            Push(ptr,toPush);

            //将头n-1个盘从a移到b，借助c
            toPush.n = tmp.n - 1;
            toPush.A = tmp.A;
            toPush.B = tmp.C;
            toPush.C = tmp.B;
            Push(ptr,toPush);
        }
    }
}