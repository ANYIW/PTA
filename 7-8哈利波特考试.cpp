#include <stdio.h>
#define INFINITY 101//
//下标从1开始存，一开始存权重，Floyd后存i到j的最短路径
int G[101][101];
void Create(int n,int m){
    int v1,v2,d;
    //初始化图
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        if(i!=j)
        G[i][j]=INFINITY;
    }
    //读入权重
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&v1,&v2,&d);
        G[v1][v2]=G[v2][v1]=d;
    }
}
void Floyd(int n){
    //每个点都作为中介试一试
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++){
        if(G[i][k]+G[k][j]<G[i][j])
        G[i][j]=G[i][k]+G[k][j];
    }
}
void Scan(int n){
    //G[i][0]存该行最大元
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    if(G[i][0]<G[i][j])
    G[i][0]=G[i][j];
}
void Print(int n){
    //找最大元中的最小元
    int minPosition;
    int min=INFINITY;
    for(int i=1;i<=n;i++){
        if(G[i][0]<min){
            min=G[i][0];
            minPosition=i;
        }
    }
    if(min==INFINITY)
    printf("0");
    else printf("%d %d",minPosition,min);
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    Create(n,m);
    Floyd(n);
    Scan(n);
    Print(n);
    return 0;
}