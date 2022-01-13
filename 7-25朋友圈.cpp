#include <stdio.h>
//负的father[i]：以i为代表的集合元素个数的相反数
int father[30010]; //下标从1开始
//对每个元素创建集合
void MakeSet(int n)
{
    for (int i = 1; i <= n; i++)
        father[i] = -1;
}
//查找所在集合
int Find(int index)
{
    if (father[index] < 0)
        return index;
    father[index] = Find(father[index]); //路径压缩
    return father[index];
}
//小集合并入大集合
void Union(int x, int y)
{
    if (Find(x) == Find(y))
        return;
    if (father[Find(x)] <= father[Find(y)])
    {
        father[Find(x)] += father[Find(y)];
        //找y集合的代表元来合并！！！
        father[Find(y)] = Find(x);
    }
    else
    {
        father[Find(y)] += father[Find(x)];
        //找x集合的代表元来合并！！！
        father[Find(x)] = Find(y);
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    MakeSet(n);
    while (m--)
    {
        int num, first;
        scanf("%d%d", &num, &first);
        //每个元素所在集合和该行首元素所在集合合并
        for (int i = 1; i < num; i++)
        {
            int index;
            scanf("%d", &index);
            Union(first, index);
        }
    }
    int min = father[1];
    for (int i = 1; i <= n; i++)
    {
        if (father[i] < min)
            min = father[i];
    }
    printf("%d", (-1) * min);
    return 0;
}