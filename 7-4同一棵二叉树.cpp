//无需建立两棵树，对第二棵树的每一个节点，在第一棵树中查找
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *Ptr;
struct Node
{
    int address;
    Ptr left, right;
    int flag; //标记是否经过
};
Ptr NewNode(int v)
{
    Ptr T = (Ptr)malloc(sizeof(struct Node));
    T->address = v;
    T->left = T->right = NULL;
    T->flag = 0;
    return T;
}
//将v加入以H为根的树
Ptr Add(Ptr H, int v)
{
    //递归终止
    if (H == NULL)
        return NewNode(v);

    if (v == H->address)
        return H;
    //左小右大
    if (v > H->address)
        H->right = Add(H->right, v);
    else
        H->left = Add(H->left, v);

    return H;
}
//依据v判断是否是同一棵树
int Judge(Ptr H, int v)
{
    if (H == NULL)
        return 0;

    if (H->address != v)
    {
        if (H->flag == 0)
            return 0;
        else
        {
            if (v > H->address)
                return Judge(H->right, v);
            else
                return Judge(H->left, v);
        }
    }
    if (H->address == v)
    {
        if (H->flag == 0)
        {
            H->flag = 1;
            return 1;
        }
        else
            return 0
    }
}
void Reset(Ptr H)
{
    //递归终止
    if (H == NULL)
        return;
    //类似先序遍历
    H->flag = 0;
    Reset(H->left);
    Reset(H->right);
}
int main()
{
    while (1)
    {
        //建树
        int n, l, v;
        scanf("%d", &n);
        if (n == 0)
            break;
        scanf("%d", &l);
        scanf("%d", &v);
        Ptr H = NewNode(v); //根结点
        for (int i = 0; i < n - 1; i++)
        {
            scanf("%d", &v);
            H = Add(H, v);
        }
        for (int i = 0; i < l; i++)
        {
            int flag = 1; //假设是同一棵树
            for (int j = 0; j < n; j++)
            {
                scanf("%d", &v);
                if (Judge(H, v) == 0)
                    flag = 0;
            }
            if (flag)
                printf("Yes\n");
            else
            {
                printf("No\n");
                flag = 1;
            }
            Reset(H); //开启新的一轮
        }
    }
    return 0;
}