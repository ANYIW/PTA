#include <stdio.h>
#include <stdlib.h>
int array1[100000];
int array2[100000];
void Read(int n, int a[])
{
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
}
int main()
{
    int n;
    scanf("%d", &n);
    Read(n, array1);
    Read(n, array2);
    //位移下标
    int i1 = 0;
    int i2 = 0;
    //遍历，t1,t2相当于指针
    int t1 = array1[i1];
    int t2 = array2[i2];
    //找中位数n1,n2
    int n1, n2, count = 0;
    while (count != n + 1&&count!=n+2)
    {
        if (t1 < t2)
        {
            t1 = array1[++i1]; //i1改变
            count++;
            //首尾相接时会越界，单独考虑
            if(i1==n){
                n1=array1[n-1];
                n2=array2[0];
                break;
            }
            if (count == n)
                n1 = array1[i1 - 1]; //i1不变
            if (count == n + 1)
                n2 = array1[i1 - 1]; //i1不变
        }
        else if (t1 == t2)
        {
            t1 = array1[++i1];
            count++;
            //首尾相接时会越界，单独考虑
            if (i1 == n)
            {
                n1 = array1[n - 1];
                n2 = array2[0];
                break;
            }
            if (count == n)
                n1 = array1[i1 - 1]; //i1不变
            if (count == n + 1)
                n2 = array1[i1 - 1]; //i1不变

            t2 = array2[++i2];
            count++;
            if (count == n)
                n1 = array2[i2 - 1]; //i2不变
            if (count == n + 1)
                n2 = array2[i2 - 1]; //i2不变
        }
        else
        {
            t2 = array2[++i2];
            count++;
            //首尾相接时会越界，单独考虑
            if (i2 == n )
            {
                n1 = array2[n - 1];
                n2 = array1[0];
                break;
            }
            if (count == n)
                n1 = array2[i2 - 1]; //i2不变
            if (count == n + 1)
                n2 = array2[i2 - 1]; //i2不变
        }
    }
    printf("%d", (n1 + n2) / 2);
    return 0;
}