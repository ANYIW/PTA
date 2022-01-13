#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Seed *Ptr;
struct Seed
{
    char name[32];
    int count;
    Ptr next;
};
Ptr Tablet[26];
void Read(int n)
{
    char name[32];
    Ptr tmp;
    for (int i = 0; i < n; i++)
    {
        fgets(name, 32, stdin);        //30个英文字母和1个空格
        name[strlen(name) - 1] = '\0'; //fgets不丢弃\n，需将\n转为\0
        tmp = Tablet[name[0] - 'A'];
        while (tmp != NULL && strcmp(tmp->name, name) != 0)
            tmp = tmp->next;
        if (tmp == NULL)
        { //从头部插入
            tmp = (Ptr)malloc(sizeof(struct Seed));
            strcpy(tmp->name, name);
            tmp->count = 1;
            if (Tablet[name[0] - 'A'] == NULL)
            {
                tmp->next = NULL;
                Tablet[name[0] - 'A'] = tmp;
            }
            else
            { //按字典顺序插入
                if (strcmp(tmp->name, Tablet[name[0] - 'A']->name) < 0)
                {
                    //插在头
                    tmp->next = Tablet[name[0] - 'A'];
                    Tablet[name[0] - 'A'] = tmp;
                }
                else
                { //不插在头
                    Ptr front, back;
                    front = NULL;
                    back = Tablet[name[0] - 'A'];
                    while (back != NULL && strcmp(back->name, tmp->name) < 0)
                    {
                        front = back;
                        back = back->next;
                    }
                    if (back == NULL)
                    {
                        front->next = tmp;
                        tmp->next = NULL;
                    }
                    else
                    {
                        front->next = tmp;
                        tmp->next = back;
                    }
                }
            }
        }
        else
            tmp->count++;
    }
}
void PrintReturn()
{
    int static i = 1;
    if (i == 1)
        i++;
    else
        printf("\n");
}
void Print(int total)
{
    Ptr traversal;
    for (int i = 0; i < 26; i++)
    {
        traversal = Tablet[i];
        while (traversal != NULL)
        {
            double proportion = ((double)traversal->count / total) * 100;
            PrintReturn();
            printf("%s %.4lf%%", traversal->name, proportion);
            traversal = traversal->next;
        }
    }
}

int main()
{
    int n;
    scanf("%d\n", &n);
    Read(n);
    Print(n);
    return 0;
}