//深度优先搜索利用递归，广度优先搜索利用队列
#include <stdio.h>
#include <stdlib.h>
typedef struct Node* Ptr;
struct Node{
    int data;//点的下标
    Ptr next;
};
typedef struct VNode* Head;
struct VNode{
    int data;//当前点的下标
    int visited;
    Ptr first;//第一条边
};
Head AdjList[10];//指针数组

void InsertEdge(Head h,int d){
    //按从小到大插入
    Ptr tmp = (Ptr)malloc(sizeof(struct Node));
    tmp->data = d;
    Ptr front, rear;
    front = h->first;
    rear = NULL;
    while (front != NULL && front->data < d)
    {
        rear = front;
        front = front->next;
    }
    tmp->next = front;
    if (rear != NULL)
        rear->next = tmp;
    else
        h->first = tmp;//插在头
}
void Create(int n,int e){
    int v1,v2;
    //点
    for(int i=0;i<n;i++){
        AdjList[i] = (Head)malloc(sizeof(struct VNode));
        AdjList[i]->data=i;
        AdjList[i]->visited=0;
        AdjList[i]->first = NULL;
    }
    //边
    for(int i=0;i<e;i++){
        scanf("%d%d",&v1,&v2);
        InsertEdge(AdjList[v1],v2);
        InsertEdge(AdjList[v2],v1);
    }
}
//Depth First Search O(n)=n+e
void DFS(int i){
    AdjList[i]->visited=1;
    printf("%d ",i);//类似先序遍历

    Ptr t=AdjList[i]->first;//traversal
    while(t){
        if(AdjList[t->data]->visited==0)
        DFS(t->data);
        t=t->next;
    }
}
void Reset(int n){
    for(int i=0;i<n;i++)
    AdjList[i]->visited=0;
}
//Breadth First Search O(n)=n+e
struct Queue{
    Head data[10];
    int front ; //指向首元素前一个位置
    int rear;
};
struct Queue queue;
int IsEmpty(){
    if(queue.front==queue.rear)
    return 1;
    else return 0;
}
int IsFull(){
    if((queue.rear+1)%10==queue.front)
    return 1;
    else return 0;
}
void AddQ(Head d){
    if(IsFull())
    return;
    queue.rear=(queue.rear+1)%10;
    queue.data[queue.rear]=d;
}
Head DeleteQ(){
    if(IsEmpty())
    return NULL;
    else{
        queue.front=(queue.front+1)%10;
        return queue.data[queue.front];
    }
}
void BFS(int i){
    AdjList[i]->visited=1;
    AddQ(AdjList[i]);
    while(!IsEmpty()){
        Head tmp=DeleteQ();
        printf("%d ",tmp->data);//类似层序遍历
        Ptr t=tmp->first;
        while(t){
            if(AdjList[t->data]->visited==0){
                AdjList[t->data]->visited=1;
                AddQ(AdjList[t->data]);
            }
            t=t->next;
        }
    }
}
/////////////////main//////////////////////////
int main(){
    int n,e;
    scanf("%d%d",&n,&e);
    Create(n,e);
    //DFS
    for(int i=0;i<n;i++){
        if(AdjList[i]->visited==0){
            if(i!=0)
            printf("\n");
            printf("{ ");
            DFS(i);
            printf("}");
        }
    }
    Reset(n);
    printf("\n");
    //BFS
    queue.front=queue.rear=0;
    for(int i=0;i<n;i++){
        if(AdjList[i]->visited==0){
            if(i!=0)
            printf("\n");
            printf("{ ");
            BFS(i);
            printf("}");
        }
    }
    return 0;
}