#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Ptr;
struct Node
{
    char data;
    Ptr left;
    Ptr right;
};
//前序遍历数组 中序遍历数组 前序第一个位置 中序第一个位置 当前处理的数组长度
Ptr Build(char *pre, char *in, int pre1, int in1, int length)
{
    //递归终止条件
    if (length == 0)
        return NULL;

    //创建第一个结点
    Ptr root = (Ptr)malloc(sizeof(struct Node));
    root->data = pre[pre1];
    //递归创建后续结点
    int length1 = 0; //左递归的长度
    int k;           //k为先序第一个元素在中序中的下标
    for (k = in1; k < in1 + length && in[k] != pre[pre1]; k++)
        length1++;
    //创建左子树
    root->left = Build(pre, in, pre1 + 1, in1, length1);
    //创建右子树，注意剔除本次的根结点
    root->right = Build(pre, in, pre1 + length1 + 1, k + 1, length - length1 - 1);
    //返回指针，以改变原来的树
    return root;
}
//level为当前根所在层数
int Depth(Ptr root, int level)
{
    if (root == NULL)
        return level;
    else
    {
        int left = Depth(root->left, level + 1);
        int right = Depth(root->right, level + 1);
        return (left > right) ? left : right;
    }
}
int main()
{
    //读取
    int n;
    scanf("%d", &n);
    char *preOrder, *inOrder;
    preOrder = (char *)malloc(sizeof(char) * (n + 1)); //还要存\0
    scanf("%s", preOrder);
    inOrder = (char *)malloc(sizeof(char) * (n + 1)); //还要存\0
    scanf("%s", inOrder);
    //创建
    Ptr root = Build(preOrder, inOrder, 0, 0, n);
    //计算深度
    printf("%d", Depth(root, 0)); //起始为第0层
    return 0;
}