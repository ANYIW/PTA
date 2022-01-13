#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node *Ptr;
struct Node
{
    char account[11];
    char password[17];
    Ptr next;
};
Ptr Hash[100000];
//第一次不输出回车
void PrintReturn()
{
    static int i = 1;
    if (i == 1)
        i++;
    else
        printf("\n");
}
void Judge(int n)
{
    char order;
    char acc[11];
    char pass[17];
    for (int i = 0; i < n; i++)
    {
        int index = 0;
        //先读回车符但不保存
        scanf("%*c%c", &order);
        scanf("%s", acc);
        //以后五位作为散列地址
        for (int i = strlen(acc) - 5; i < strlen(acc); i++)
            index = index * 10 + acc[i] - '0';
        scanf("%s", pass);
        Ptr tmp;
        switch (order)
        {
        case 'N':
            tmp = Hash[index];
            while (tmp != NULL && strcmp(tmp->account, acc) != 0)
                tmp = tmp->next;
            if (tmp == NULL)
            {
                tmp = (Ptr)malloc(sizeof(struct Node));
                strcpy(tmp->account, acc);
                strcpy(tmp->password, pass);
                if (Hash[index] == NULL)
                { //创建表头
                    Hash[index] = tmp;
                    Hash[index]->next = NULL;
                }
                else
                { //插入表头
                    tmp->next = Hash[index]->next;
                    Hash[index]->next = tmp;
                }
                PrintReturn();
                printf("New: OK");
            }
            else
            {
                PrintReturn();
                printf("ERROR: Exist");
            }
            break;
        case 'L':
            tmp = Hash[index];
            while (tmp != NULL && strcmp(tmp->account, acc) != 0)
                tmp = tmp->next;
            if (tmp == NULL)
            {
                PrintReturn();
                printf("ERROR: Not Exist");
            }
            else
            {
                PrintReturn();
                if (strcmp(tmp->password, pass) != 0)
                    printf("ERROR: Wrong PW");
                else
                    printf("Login: OK");
            }
            break;
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    Judge(n);
    return 0;
}