//建树过程寻找树根，递归判断是否同构
#include <stdio.h>
#include <stdlib.h>
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1
struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
} T1[MaxTree], T2[MaxTree];
//建树并返回根结点
Tree BuildTree(struct TreeNode T[])
{
    int N, i, Root;
    int check[MaxTree];
    char cl, cr;
    scanf("%d\n", &N); //把\n也读了
    if (N == 0)
        return -1;
    if (N)
    {
        for (i = 0; i < N; i++) //最终根结点的check为0
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            scanf("%c %c %c\n", &T[i].Element, &cl, &cr); //注意格式
            if (cl != '-')
            {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else
                T[i].Left = Null;
            if (cr != '-')
            {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1; //不是根
            }
            else
                T[i].Right = Null;
        }
        for (i = 0; i < N; i++)
            if (!check[i])
                break;
        Root = i;
    }
    return Root;
}
int Isomorphic(Tree R1, Tree R2)
{                                 //比较左右根是否同构
    if (R1 == Null && R2 == Null) //都空
        return 1;
    if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) //有一个为空
        return 0;
    if (T1[R1].Element != T2[R2].Element) //元素不同
        return 0;
    if (T1[R1].Left == Null && T2[R2].Left == Null) //左侧儿子都空
        return Isomorphic(T1[R1].Right, T2[R2].Right);
    //左侧儿子都不空
    if ((T1[R1].Left != Null) && (T2[R2].Left != Null) && (T1[T1[R1].Left].Element == T2[T2[R2].Left].Element))
        return (Isomorphic(T1[R1].Left, T2[R2].Left) && Isomorphic(T1[R1].Right, T2[R2].Right));
    else
        return (Isomorphic(T1[R1].Left, T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
}
int main()
{
    Tree root1 = BuildTree(T1);
    Tree root2 = BuildTree(T2);
    if (Isomorphic(root1, root2))
        printf("Yes");
    else
        printf("No");
    return 0;
}