//乘法：
//对于第一条链表的第一项，乘以第二条链表的每一项，生成初始链表
//再用第一条链表的其余项，乘以第二条链表的每一项，并寻找插入位置
#include <stdio.h>
#include <stdlib.h>
typedef struct Node* P;
typedef struct Node Poly; //polynomial
struct Node
{
    int c; //coefficient
    int e; //exponent
    P next;
};

P Create()
{
    int n;
    scanf("%d", &n);
    if (n <= 0)
        return NULL;
    //哨兵
    P head = (P)malloc(sizeof(Poly));
    P tail = head;
    head->next = NULL;
    //循环
    for (int i = 0; i < n; i++)
    {
        P tmp = (P)malloc(sizeof(Poly));
        tmp->next = NULL;
        scanf("%d", &tmp->c);
        scanf("%d", &tmp->e);
        tail->next = tmp;
        tail = tmp;
    }
    //释放哨兵
    tail = head;
    head = head->next;
    free(tail);
    return head;
}
P Attach(P tail, int c, int e)
{
    if (tail == NULL)
        return NULL;
    P tmp = (P)malloc(sizeof(Poly));
    tmp->c = c;
    tmp->e = e;
    tmp->next = NULL;
    tail->next = tmp;
    return tmp;
}
P Add(P head1, P head2)
{
    if (head1 == NULL && head2 == NULL)
        return NULL;
    if (head1 == NULL && head2 != NULL)
        return head2;
    if (head1 != NULL && head2 == NULL)
        return head1;
    //哨兵
    P head = (P)malloc(sizeof(Poly));
    P tail = head;
    head->next = NULL;
    //遍历
    P t1 = head1;
    P t2 = head2;
    while (t1 && t2)
    {
        if (t1->e > t2->e)
        {
            tail = Attach(tail, t1->c, t1->e);
            t1 = t1->next;
            continue;
        }
        if (t1->e == t2->e)
        {
            if (t1->c + t2->c) //不相抵消
                tail = Attach(tail, t1->c + t2->c, t1->e);
            t1 = t1->next;
            t2 = t2->next;
            continue;
        }
        if (t2->e > t1->e)
        {
            tail = Attach(tail, t2->c, t2->e);
            t2 = t2->next;
            continue;
        }
    }
    while (t1)
    {
        tail = Attach(tail, t1->c, t1->e);
        t1 = t1->next;
    }
    while (t2)
    {
        tail = Attach(tail, t2->c, t2->e);
        t2 = t2->next;
    }
    //释放哨兵
    tail = head;
    head = head->next;
    free(tail);
    return head;
}
P Multiply(P head1, P head2)
{
    if (head1 == NULL || head2 == NULL)
        return NULL;
    //哨兵
    P head = (P)malloc(sizeof(Poly));
    P tail = head;
    head->next = NULL;
    //初始多项式
    P t1 = head1;
    P t2 = head2;
    while (t2)
    {
        tail = Attach(tail, head1->c * t2->c, head1->e + t2->e);
        t2 = t2->next;
    }
    //遍历
    t1 = head1->next;
    t2 = head2;
    while (t1)
    {
        while (t2)
        {
            int c = t1->c * t2->c;
            int e = t1->e + t2->e;
            P t = head->next;
            while (t->next)
            { //不可能比head->next次数还高，插在t后
                if (t->next->e == e)
                {
                    if (t->next->c + c)
                    { //合并
                        t->next->c += c;
                        break; //////////////勿忘
                    }
                    else
                    { //相抵消
                        P tmp = t->next;
                        t->next = tmp->next;
                        free(tmp);
                        t = t->next;//最后一项相抵消的情况，break后不能Attach
                        break; /////////////勿忘
                    }
                }
                if (t->next->e < e)
                { //插入
                    P tmp = (P)malloc(sizeof(Poly));
                    tmp->c = c;
                    tmp->e = e;
                    tmp->next = t->next;
                    t->next = tmp;
                    break; //////////////////勿忘
                }
                t = t->next;
            }
            if (t != NULL && t->next == NULL) //插在末尾
                tail = Attach(t, c, e);   //最后一项相抵消的情况，break后不能Attach
            //移位
            t2 = t2->next;
        }
        //移位
        t1 = t1->next;
        t2 = head2;
    }
    //释放哨兵
    tail = head;
    head = head->next;
    free(tail);
    return head;
}
void Print(P head)
{
    if (head == NULL)
    {
        printf("0 0");
        return;
    }
    printf("%d %d", head->c, head->e);
    head = head->next;
    while (head)
    {
        printf(" %d %d", head->c, head->e);
        head = head->next;
    }
}
void Release(P head)
{
    while (head)
    {
        P tmp = head->next;
        free(head);
        head = tmp;
    }
}
int main()
{
    P head1 = Create();
    P head2 = Create();
    P add = Add(head1, head2);
    P mult = Multiply(head1, head2);
    Print(mult);
    printf("\n");
    Print(add);
    Release(head1);;
    Release(head2);
    Release(add);
    Release(mult);
    return 0;
}
/*
2 3 3 2 2
2 3 2 -2 1
9 5 -4 3
3 3 5 2 -2 1*/