#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Ptr;
struct Node
{
    int coef;
    int expo;
    Ptr next;
};
Ptr Create()
{
    //哨兵
    Ptr head, tail;
    head = tail = (Ptr)malloc(sizeof(struct Node));
    head->next = NULL;
    //读入
    int c, e;
    //利用返回值判断是否还需读取
    while (scanf("%d%d", &c, &e) == 2)
    {
        Ptr temp = (Ptr)malloc(sizeof(struct Node));
        temp->coef = c;
        temp->expo = e;
        temp->next = NULL;

        tail->next = temp;
        tail = temp;
    }
    //释放哨兵
    tail = head;
    head = head->next;
    free(tail);

    return head;
}
void Derivation(Ptr head)
{
    if (head == NULL)
        return;

    Ptr temp = head;
    temp->coef *= temp->expo;
    temp->expo--;
    //零多项式和常数多项式不能什么都不输出
    if (temp->coef == 0)
    {
        printf("0 0");
        return;
    }
    else
        printf("%d %d", temp->coef, temp->expo);
    temp = temp->next;
    while (temp != NULL)
    {
        temp->coef *= temp->expo;
        temp->expo--;
        if (temp->coef != 0)
            printf(" %d %d", temp->coef, temp->expo);
        temp = temp->next;
    }
}
int main()
{
    Ptr head = Create();
    Derivation(head);
    return 0;
}