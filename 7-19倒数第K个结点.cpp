#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;
    Ptr next;
};
Ptr Create(){
    //哨兵
    Ptr head=(Ptr)malloc(sizeof(struct Node));
    head->next=NULL;
    return head;
}
//头插法
void FrontInsert(Ptr head,int v){
    Ptr temp=(Ptr)malloc(sizeof(struct Node));
    temp->data=v;
    temp->next=head->next;
    head->next=temp;
}
Ptr Search(Ptr head,int v){
    int count=0;
    while(head!=NULL&&count!=v){
        head=head->next;
        count++;
    }  
    return head;
}
void Release(Ptr head){
    Ptr tmp=head->next;
    while(tmp!=NULL){
        free(head);
        head=tmp;
        tmp=head->next;
    }
}
int main(){
    Ptr head=Create();
    int k,times=0;
    scanf("%d",&k);
    if(k<=0){
        printf("NULL");
        return 0;
    }
    int v;
    scanf("%d",&v);
    //负数标志结束
    while(v>=0){
        FrontInsert(head,v);
        times++;
        scanf("%d",&v);
    }

    if(k>times)
    printf("NULL");
    else printf("%d",Search(head,k)->data);

    Release(head);
    return 0;
}