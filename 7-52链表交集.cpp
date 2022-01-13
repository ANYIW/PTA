#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;
    Ptr next;
};
//tail会后移，必须返回或使用指针的指针
Ptr Attach(Ptr tail,int v){
    Ptr temp = (Ptr)malloc(sizeof(struct Node));
    temp->data = v;
    temp->next = NULL;
    tail->next = temp;
    tail = temp;
    return tail;
}
Ptr Create(){
    //哨兵
    Ptr head,tail;
    head=tail=(Ptr)malloc(sizeof(struct Node));
    head->next=NULL;
    //读取
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
    //返回
    return head;
}
Ptr Intersection(Ptr head1,Ptr head2){
    if(head1==NULL||head2==NULL)
    return NULL;
    //哨兵
    Ptr head, tail;
    head = tail = (Ptr)malloc(sizeof(struct Node));
    head->next = NULL;
    //Traversal
    Ptr t1=head1,t2=head2;
    while(t1&&t2){
        if(t1->data<t2->data)
        t1=t1->next;
        else if(t1->data==t2->data){
            tail=Attach(tail,t1->data);
            t1=t1->next;
            t2=t2->next;
        }else t2=t2->next;
    }
    //释放哨兵
    tail = head;
    head = head->next;
    free(tail);
    //返回
    return head;
}
void Print(Ptr head)
{
    if (head == NULL)
        printf("NULL");
    else
    {
        printf("%d", head->data);
        head = head->next;
        while (head)
        {
            printf(" %d", head->data);
            head = head->next;
        }
    }
}
void Release(Ptr head)
{
    while (head)
    {
        Ptr tmp = head->next;
        free(head);
        head = tmp;
    }
}
int main(){
    Ptr head1=Create();
    Ptr head2=Create();
    Ptr head=Intersection(head1,head2);
    Print(head);
    Release(head1);
    Release(head2);
    Release(head);
    return 0;
}