#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node *Ptr;
struct Node
{
    char name[35];
    int count;
    Ptr left;
    Ptr right;
};
//传指针的指针
void FindOrInsert(Ptr *node, char *tmp)
{
    if (*node == NULL)
    {
        *node = (Ptr)malloc(sizeof(struct Node));
        strcpy((*node)->name, tmp);
        (*node)->count = 1;
        (*node)->left = (*node)->right = NULL;
        return;
    }
    if (strcmp((*node)->name, tmp) == 0)
    {
        (*node)->count++;
        return;
    }
    if (strcmp((*node)->name, tmp) > 0)
        FindOrInsert(&((*node)->left), tmp);
    else
        FindOrInsert(&((*node)->right), tmp);
}
int times = 1; //最后一行末无换行符
//中序遍历序列按字典序从小到大排列
void InOrderPrint(Ptr node, int n)
{
    if (node == NULL)
        return;
    InOrderPrint(node->left, n);
    if (times == 1)
        times++;
    else
        printf("\n");
    printf("%s %.4lf%%", node->name, (double)node->count * 100 / n);
    InOrderPrint(node->right, n);
}
int main()
{
    int n;
    scanf("%d", &n);
    //树根
    Ptr root = (Ptr)malloc(sizeof(struct Node));
    //gets_s(root->name,35);
    getchar(); //过滤scanf遗留下的'\n'
    cin.getline(root->name, 35);
    root->count = 1;
    root->left = root->right = NULL;
    //构建二叉搜索树
    int i = n;
    while (--i)
    {
        char tmp[35];
        //gets_s(tmp,35);
        cin.getline(tmp, 35);
        FindOrInsert(&root, tmp);
    }
    //输出
    InOrderPrint(root, n);
    return 0;
}