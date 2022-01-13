#include <stdio.h>
#include <stdlib.h>
//表达式栈
struct Stack1
{
    char data[100];
    int top;
};
struct Stack1 s1;
void Push1(char c)
{
    if (s1.top < 99)
        s1.data[++s1.top] = c;
}
char Pop1()
{
    if (s1.top != -1)
        return s1.data[s1.top--];
}
//运算数栈，因为需要从右往左扫描
struct Stack2
{
    double data[100];
    int top;
};
struct Stack2 s2;
void Push2(double d)
{
    if (s2.top < 99)
        s2.data[++s2.top] = d;
}
double Pop2()
{
    if (s2.top != -1)
        return s2.data[s2.top--];
}
//从右往左扫描，运算数压栈，运算符弹出数字计算后压栈
double Calculate()
{
    char ch;
    while (s1.top != -1)
    {
        ch = Pop1();
        if (ch >= '0' && ch <= '9')
        {
            int weight = 1;
            double sum = 0;
            flag:
            while (ch >= '0' && ch <= '9')
            {
                sum += (ch - '0') * weight;
                weight *= 10;
                ch = Pop1();
            }
            if(ch=='-'){
                sum *= (-1); //负号
                ch=Pop1();//弹出空格
            }
            else{
                if(ch=='+')
                ch=Pop1();//弹出空格
                else if(ch=='.'){
                    sum/=weight;//退化成小数部分
                    ch=Pop1();
                    weight=1;//重置权重
                    goto flag;
                }
            }
            Push2(sum);
        }
        else
        {
            double a, b;
            a = Pop2();
            b = Pop2();
            switch (ch)
            {
            case '+':
                Push2(a + b);
                break; //勿漏！！！
            case '-':
                Push2(a - b); //注意次序
                break;
            case '*':
                Push2(a * b);
                break;
            case '/':
                if (b)
                    Push2(a / b); //注意次序
                else
                {
                    printf("ERROR");
                    exit(0);
                }
                break;
            }
            ch = Pop1(); //弹出空格
        }
    }
    return s2.data[s2.top];
}
int main()
{
    s1.top = -1;
    s2.top = -1;
    char ch;
    scanf("%c", &ch);
    while (ch != '\n')
    {
        Push1(ch);
        ch = getchar();
    }
    printf("%.1lf", Calculate());
    return 0;
}
/*
+ + 2 * 3 - 7 4 / 8 4
13.0
-23.45
-23.4
/ 5 + * - 2 3 4 / 8 2
ERROR
/ -25 + * - 2 3 4 / 8 4
12.5*/