#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node *Ptr;
//分离链接法
struct Node
{
    char number[12];
    int times;
    Ptr next;
};
//号码后五位作为散列地址
Ptr key[100000];
void Create(int n)
{
    char num[12];
    for (int i = 0; i < 2 * n; i++)
    {
        int index = 0;
        scanf("%s", num);
        //后五位转为数字
        for (int j = 6; j <= 10; j++)
        {
            index = index * 10 + num[j] - '0';
        }
        Ptr tmp = key[index];
        //找位置
        while (tmp != NULL && strcmp(tmp->number, num) != 0)
            tmp = tmp->next;
        if (tmp == NULL)
        {
            tmp = (Ptr)malloc(sizeof(struct Node));
            strcpy(tmp->number, num);
            tmp->times = 1;
            //勿漏插入操作
            if (key[index] == NULL)
            {
                key[index] = tmp;
                key[index]->next = NULL;
            }
            else
            {
                tmp->next = key[index]->next;
                key[index]->next = tmp;
            }
        }
        else
            tmp->times++;
    }
}
void Print()
{
    int maxTimes = 0;
    char number[12];
    int people;//记录并列人数
    for (int i = 0; i < 100000; i++)
    {
        Ptr tmp = key[i];
        while (tmp != NULL)
        {
            if (tmp->times > maxTimes)
            {
                maxTimes = tmp->times;
                strcpy(number, tmp->number);
                people=1;//重置并列人数
            }
            else if (tmp->times == maxTimes)
            {
                people++;//累加并列人数
                if ((strcmp(tmp->number, number)) < 0)
                    strcpy(number, tmp->number);
            }
            tmp = tmp->next;
        }
    }
    printf("%s %d", number, maxTimes);
    if(people>1)
    printf(" %d",people);
}
int main()
{
    int n;
    scanf("%d", &n);
    Create(n);
    Print();
    return 0;
}