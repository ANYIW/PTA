#include <stdio.h>
#include <stdlib.h>
//建图
typedef struct Node *Ptr;
struct Node
{
    int data; //点的下标
    Ptr next; //下一条边
};
typedef struct VNode *Head;
struct VNode
{
    int visited;
    Ptr first; //第一条边
};
Head AdjList[1001]; //邻接表头指针数组，从下标为1的元素开始存起
void InsertEdge(Head h, int d)
{
    //从前插入，不用单独考虑第一次插入的情况
    Ptr tmp = (Ptr)malloc(sizeof(struct Node));
    tmp->data = d;
    tmp->next = h->first;
    h->first = tmp;
}
void Create(int v, int e)
{
    //vertex
    for (int i = 1; i <= v; i++)
    {
        AdjList[i] = (Head)malloc(sizeof(struct VNode));
        AdjList[i]->visited = 0;
        AdjList[i]->first = NULL;
    }
    //edge
    for (int i = 0; i < e; i++)
    {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        InsertEdge(AdjList[v1], v2);
        InsertEdge(AdjList[v2], v1); //无向图
    }
}
//队列
struct Queue
{
    int data[1000];
    int front; //指向队列头前一个位置
    int rear;
};
struct Queue queue;
int IsEmpty()
{
    if (queue.front == queue.rear)
        return 1;
    else
        return 0;
}
int IsFull()
{
    if ((queue.rear + 1) % 1000 == queue.front)
        return 1;
    else
        return 0;
}
int DeleteQ()
{
    if (IsEmpty())
        return -1;
    queue.front = (queue.front + 1) % 1000;
    return queue.data[queue.front];
}
void AddQ(int d)
{
    if (IsFull())
        return;
    queue.rear = (queue.rear + 1) % 1000;
    queue.data[queue.rear] = d;
}
//BFS遍历下标为i的点所在的连通集并返回符合条件的点数
int Count(int i)
{
    int count = 0;
    int level = 0; //本身为第0层
    int last = i;  //上一层最后一个点
    AddQ(i);
    AdjList[i]->visited = 1;
    count++;

    while (!IsEmpty())
    {
        //出队
        int tmp = DeleteQ();
        //相邻点入队
        Ptr t = AdjList[tmp]->first; //traversal
        while (t)
        { //第level层入队
            if (AdjList[t->data]->visited == 0)
            {
                AddQ(t->data);
                AdjList[t->data]->visited = 1;
                count++;
            }
            t = t->next;
        }
        if (tmp == last)
        { //之前的相邻点入队是第level+1层，之后要进入第level+2层了，需更新last
            level++;
            last = queue.data[queue.rear];
        }
        if (level == 6)
            break;
    }
    return count;
}
//重置visited
void Reset(int n)
{
    for (int i = 1; i <= n; i++)
        AdjList[i]->visited = 0;
}
//输出
void Print(int n, int i)
{
    queue.front = queue.rear = 0;                     //初始化队列
    double proportion = ((double)Count(i) / n) * 100; //输出百分数
    printf("%.2lf", proportion);
    printf("%%");
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Create(n, m);
    for (int i = 1; i <= n; i++)
    {
        printf("%d: ", i);
        Print(n, i);
        Reset(n);
        if (i != n)
            printf("\n");
    }
    return 0;
}