#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Info* Ptr;
struct Info
{
    char name[11];
    int level;
};
typedef struct
{
    Ptr element[100001];
    int size;
    int capacity;
} Heap;
Heap* Create()
{
    Heap* p = (Heap*)malloc(sizeof(Heap));
    p->element[0] = (Ptr)malloc(sizeof(struct Info));
    strcpy(p->element[0]->name, "sentry");
    p->element[0]->level = 0; //0小于正整数
    for (int i = 1; i <= 100000; i++)
        p->element[i] = NULL;
    p->size = 0;
    p->capacity = 100000;
    return p;
}
/*void Swap(Ptr* p1, Ptr* p2)
{
    Ptr tmp = (*p1);
    (*p1) = (*p2);
    (*p2) = tmp;
}*/
void Add(Heap* p, char* msg, int level)
{
    if (p->size == 100000) //堆满
        return;
    p->size++;
    if (p->element[p->size] == NULL)
        p->element[p->size] = (Ptr)malloc(sizeof(struct Info));

    int i;
    for (i = p->size; p->element[i / 2]->level > level; i /= 2) {
        //p->element[i] = p->element[i / 2];不可，不然会两个一起变
        strcpy(p->element[i]->name, p->element[i / 2]->name);
        p->element[i]->level = p->element[i / 2]->level;
    }
    strcpy(p->element[i]->name, msg);
    p->element[i]->level = level;
}
Ptr Delete(Heap* p)
{
    if (p->size == 0)
        return NULL;
    //Ptr min = p->element[1];不可，min会随element[1]改变
    Ptr min = (Ptr)malloc(sizeof(struct Info));
    strcpy(min->name, p->element[1]->name);
    min->level = p->element[1]->level;
    Ptr tmp = p->element[p->size--]; //取出堆中最后的元素
    int parent, child;
    for (parent = 1; 2 * parent <= p->size; parent = child)
    {
        child = 2 * parent;
        if (child != p->size && (p->element[child]->level > p->element[child + 1]->level))
            child++; //child为等级数较小儿子的下标
        if (tmp->level < p->element[child]->level)
            break;
        else {
            //p->element[parent] = p->element[child];不可，不然会两个一起变
            strcpy(p->element[parent]->name, p->element[child]->name);
            p->element[parent]->level = p->element[child]->level;
        }
    }
    //p->element[parent] = tmp;不可，不然会两个一起变
    strcpy(p->element[parent]->name, tmp->name);
    p->element[parent]->level = tmp->level;
    return min;
}
void PrintReturn()
{
    int static i = 1;
    if (i == 1)
        i++;
    else
        printf("\n");
}
int main()
{
    int n;
    char order[4];
    Heap* heap = Create();
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", order);
        if (strcmp(order, "PUT") == 0)
        {
            char message[11];
            int rank = 0;
            scanf("%s%d", message, &rank);
            Add(heap, message, rank);
        }
        else
        { //order为GET
            PrintReturn();
            Ptr priority = Delete(heap);
            if (priority == NULL)
                printf("EMPTY QUEUE!");
            else
                printf("%s", priority->name);
        }
    }
    return 0;
}