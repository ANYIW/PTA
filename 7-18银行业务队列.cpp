#include <stdio.h>
#include <stdlib.h>
typedef struct Queue *Ptr;
struct Queue
{
    int data[1000];
    int front;
    int rear;
};
void Add(Ptr ptr, int d)
{
    if (ptr != NULL && (ptr->rear + 1) % 1000 != ptr->front)
    {
        ptr->data[ptr->rear] = d;
        ptr->rear += 1;
    }
}
int Delete(Ptr ptr)
{
    int save;
    if (ptr->front != ptr->rear)
    {
        save = ptr->data[ptr->front];
        ptr->front = (ptr->front + 1) % 1000;
    }
    return save;
}
int IsEmpty(Ptr ptr)
{
    return (ptr->front == ptr->rear);
}
int IsOdd(int number)
{
    if (number % 2 != 0)
        return 1;
    else
        return 0;
}
void PrintSpace()
{
    static int i = 0;
    if (i == 0)
        i++;
    else
        printf(" ");
}
int main()
{
    Ptr A, B;
    A = (Ptr)malloc(sizeof(struct Queue));
    A->front = A->rear = 0;
    B = (Ptr)malloc(sizeof(struct Queue));
    B->front = B->rear = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int customer;
        scanf("%d", &customer);
        if (IsOdd(customer))
            Add(A, customer);
        else
            Add(B, customer);
    }
    while (1)
    {
        if (!IsEmpty(A))
        {
            PrintSpace();
            printf("%d", Delete(A));
        }
        else
            break;
        if (!IsEmpty(A))
        {
            PrintSpace();
            printf("%d", Delete(A));
        }
        else
            break;
        if (!IsEmpty(B))
        {
            PrintSpace();
            printf("%d", Delete(B));
        }
        else
            break;
    }
    //结尾处理，类似多项式加法
    while (!IsEmpty(A))
    {
        PrintSpace();
        printf("%d", Delete(A));
    }
    while (!IsEmpty(B))
    {
        PrintSpace();
        printf("%d", Delete(B));
    }
    return 0;
}