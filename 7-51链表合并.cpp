#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;
    Ptr next;
};
Ptr Attach(Ptr tail, int v)
{
    if (tail == NULL)
        return NULL;

    Ptr tmp = (Ptr)malloc(sizeof(struct Node));
    tmp->data = v;
    tmp->next = NULL;
    tail->next = tmp;
    tail = tmp;
    return tail;
}
Ptr Create(){
    Ptr head,tail;
    //哨兵
    head=tail=(Ptr)malloc(sizeof(struct Node));
    head->next=NULL;

    int v;
    scanf("%d",&v);
    while(v!=-1){
        tail=Attach(tail,v);
        scanf("%d",&v);
    }
    //释放哨兵
    tail=head;
    head=head->next;
    free(tail);
    return head;
}

Ptr Merge(Ptr h1,Ptr h2){
    if(h1==NULL)
    return h2;
    if(h2==NULL)
    return h1;
    //哨兵
    Ptr head,tail;
    head = tail = (Ptr)malloc(sizeof(struct Node));
    head->next=NULL;
    //Traversal
    Ptr t1=h1;
    Ptr t2=h2;
    while(t1&&t2){
        if(t1->data<t2->data){
            tail=Attach(tail,t1->data);
            t1=t1->next;
        }else{
            tail=Attach(tail,t2->data);
            t2=t2->next;
        }
    }
    while(t1!=NULL){
        tail=Attach(tail,t1->data);
        t1=t1->next;
    }
    while(t2!=NULL){
        tail=Attach(tail,t2->data);
        t2=t2->next;
    }
    //释放哨兵
    tail=head;
    head=head->next;
    free(tail);

    return head;
}
void Print(Ptr head){
    if(head==NULL)
    printf("NULL");
    else{
        printf("%d",head->data);
        head=head->next;
        while(head){
            printf(" %d",head->data);
            head=head->next;
        }
    }
}
void Release(Ptr head){
    while(head){
        Ptr tmp=head->next;
        free(head);
        head=tmp;
    }
}
int main(){
    Ptr head1=Create();
    Ptr head2=Create();
    Ptr head=Merge(head1,head2);
    Print(head);
    Release(head1);
    Release(head2);
    Release(head);
    return 0;
}