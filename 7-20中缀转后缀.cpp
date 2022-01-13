#include <stdio.h>
#include <stdlib.h>
//栈
struct Stack{
    char data[20];
    int top;
};
struct Stack stack;
char Pop(){
    if(stack.top!=-1)
    return stack.data[stack.top--];
}
void Push(char c){
    if(stack.top!=19)
    stack.data[++stack.top]=c;
}
//要判断'+'、'-'是正负号还是运算符，需要得知之前的字符
char exp[20];
//数字判断
int IsDigit(char c){
    if((c>='0'&&c<='9')||c=='.')//小数点
    return 1;
    else return 0;
}
//第一个元素前不输出空格
int cnt=1;
void PrintSpace(){
    if(cnt==1)
    cnt++;
    else printf(" ");
}
int main(){
    //存储表达式
    char ch;
    int n=0;
    scanf("%c", &ch);
     while (ch!= '\n'){
         exp[n++] = ch;
         scanf("%c",&ch);
    }
    stack.top=-1;//初始化栈  
    //处理表达式
    for(int i=0;i<n;i++){
        if(IsDigit(exp[i])){
            PrintSpace();
            while (i < n && IsDigit(exp[i]))
            {
                printf("%c", exp[i]);
                i++;
            }
            i--;//退回数字位
            continue;
        }
        if (exp[i] == '(')
        {
            Push(exp[i]);
            continue;
        }
        if (exp[i] == '+' || exp[i] == '-')
        {
            if(i==0||exp[i-1]=='('){//正负号，输出符号
                PrintSpace();
                if(exp[i]=='-')
                    printf("%c", exp[i]);
                i++;
                while (i < n && IsDigit(exp[i]))
                {
                    printf("%c", exp[i]);
                    i++;
                }
                i--;//退回数字位
            }else{//运算符，优先级最低
                while(stack.top!=-1&&stack.data[stack.top]!='('){
                    PrintSpace();
                    printf("%c", Pop());
                }
                Push(exp[i]);
            }
            continue;
        }
        if(exp[i]=='*'||exp[i]=='/'){
            while(stack.top!=-1&&(stack.data[stack.top]=='*'||stack.data[stack.top]=='/')){
                PrintSpace();
                printf("%c", Pop());
            }
            Push(exp[i]);
            continue;
        }
        if(exp[i]==')'){
            while(stack.data[stack.top]!='('){
                PrintSpace();
                printf("%c", Pop());
            }
            Pop();//弹出左括号
            continue;
        }
    }
    while(stack.top!=-1){
        PrintSpace();
        printf("%c",Pop());
    }
    return 0;
}