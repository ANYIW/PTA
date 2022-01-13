#include <stdio.h>
#include <stdlib.h>
long array[100000];
void Read(int n)
{
    for (int i = 0; i < n; i++)
        scanf("%ld", &array[i]);
}
//将a数组归并排序后存到tmp数组
//最后依据是否递归决定是否将结果从tmp导回a
void Merge(long a[], long tmp[], int LeftBegin, int RightBegin, int RightEnd)
{
    int LeftEnd = RightBegin - 1;
    int begin = LeftBegin;            //结果数组tmp的初始位置
    int n = RightEnd - LeftBegin + 1; //待排元素个数，导回需要
    //类似多项式加法
    while (LeftBegin <= LeftEnd && RightBegin <= RightEnd)
    {
        if (a[LeftBegin] <= a[RightBegin])
            tmp[begin++] = a[LeftBegin++];
        else
            tmp[begin++] = a[RightBegin++];
    }
    //结尾处理
    while (LeftBegin <= LeftEnd)
        tmp[begin++] = a[LeftBegin++];
    while (RightBegin <= RightEnd)
        tmp[begin++] = a[RightBegin++];
    //导回a数组，注意LeftBegin已变，不可用
    //i记录次数
    //for(int i=0;i<n;i++,RightEnd--)
    //a[RightEnd]=tmp[RightEnd];
}
//非递归实现
void MSort(long a[], long tmp[], int n, int length)
{
    //归并各包含length个元素的2个子列
    int i;
    for (i = 0; (i + 2 * length - 1) <= n - 1; i += 2 * length)
        Merge(a, tmp, i, i + length, i + 2 * length - 1);
    //归并最后2个子列
    if ((i + length) <= n - 1)
        Merge(a, tmp, i, i + length, n - 1);
    else
        for (int j = i; j <= n - 1; j++) //最后只剩1个子列
            tmp[j] = a[j];
}
void MergeSort(long a[], int n)
{
    int length = 1;
    long *tmp = (long)malloc(sizeof(long) * n);
    if (tmp != NULL)
    {
        while (length < n)
        {
            //从a导入tmp
            MSort(a, tmp, n, length);
            length *= 2;
            //从tmp导入a
            MSort(tmp, a, n, length);
            length *= 2;
        }
        free(tmp);
    }
}
void Print(int n)
{
    for (int i = 0; i < n - 1; i++)
        printf("%ld ", array[i]);
    printf("%ld", array[n - 1]);
}
int main()
{
    int n;
    scanf("%d", &n);
    Read(n);
    MergeSort(array, n);
    Print(n);
    return 0;
}