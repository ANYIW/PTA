#include <stdio.h>
#include <stdlib.h>
typedef struct Stack* Ptr;
struct Stack{
    int* data;
    int top;
    int size;
};
Ptr Create(int n){
    Ptr tmp=(Ptr)malloc(sizeof(struct Stack));
    tmp->data=(int*)malloc(sizeof(int)*n);
    tmp->top=-1;
    tmp->size=n;
    return tmp;
}
int IsEmpty(Ptr p){
    if(p!=NULL&&p->top==-1)
    return 1;
    else return 0;
}
int IsFull(Ptr p){
    if(p!=NULL&&p->top==p->size-1)
    return 1;
    else return 0;
}
int Pop(Ptr p){
    if(p!=NULL&&!IsEmpty(p))
    return p->data[p->top--];
}
void Push(Ptr p,int d){
    if(p!=NULL&&!IsFull(p))
    p->data[++p->top]=d;
}
void PrintReturn(){
    static int i=1;
    if(i==1)
    i++;
    else printf("\n");
}
int main(){
    int size1,size2;
    Ptr p1,p2;//p1容量不小于p2
    scanf("%d%d",&size1,&size2);
    //创建栈
    if(size1>size2){
        p1=Create(size1);
        p2=Create(size2);
    }
    else{
        p1=Create(size2);
        p2=Create(size1);
    }
    char str[2];//存\0
    scanf("%s",str);
    while(str[0]!='T'){
        if(str[0]=='A'){
            int d;
            scanf("%d", &d);
            if(!IsFull(p2)){
                Push(p2,d);
            }
            else{
                if(IsFull(p2)&&IsEmpty(p1)){
                    while(!IsEmpty(p2))
                    Push(p1,Pop(p2));
                    Push(p2,d);
                }
                else{
                    PrintReturn();
                    printf("ERROR:Full");
                }
            }
        }
        if(str[0]=='D'){
            if(!IsEmpty(p1)){
                PrintReturn();
                printf("%d",Pop(p1));
            }
            else{
                if(IsEmpty(p1)&&!IsEmpty(p2)){
                    while(!IsEmpty(p2))
                    Push(p1,Pop(p2));
                    PrintReturn();
                    printf("%d",Pop(p1));
                }
                else{
                    PrintReturn();
                    printf("ERROR:Empty");
                }
            }
        }
        scanf("%s",str);
    }
    return 0;
}