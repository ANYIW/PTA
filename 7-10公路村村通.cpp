#include <stdio.h>
#define INFINITY 65536
G[1000][1000];
int dist[1000];
void Create(int n,int m){
    //初始化
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        if(i!=j)
        G[i][j]=INFINITY;
    }
    //读入
    for(int i=0;i<m;i++){
        int v1,v2,cost;
        scanf("%d%d%d",&v1,&v2,&cost);
        G[v1-1][v2-1]=cost;
        G[v2-1][v1-1]=cost;
    }
    //以下标为0的点为source
    for(int i=0;i<n;i++)
    dist[i]=G[0][i];//dist[0]为0，证明点0已经在MST中
}
int Scan(int n){
    int minDist=INFINITY;
    int minPosition=-1;
    for(int i=0;i<n;i++)
    if(dist[i]!=0&&dist[i]<minDist){
        minDist=dist[i];
        minPosition=i;
    }
    return minPosition;
}
void Prim(int n){
    int sum = 0;    //权重之和
    int vertex = 1; //被收录的点数
    while(1){    
        //找未被收录的点中dist最小者
        int v=Scan(n);
        //找不到这样的v
        if(v==-1)
        break;
        //收录v
        sum+=dist[v];
        dist[v]=0;
        vertex++;
        //对v的每个邻接点
        for(int w=0;w<n;w++){
            if(G[v][w]!=INFINITY&&G[v][w]!=0){
                if(G[v][w]<dist[w])
                dist[w]=G[v][w];
            }
        }
    }
    if(vertex!=n)
    printf("-1");
    else printf("%d",sum);
}
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    Create(n,m);
    Prim(n);
    return 0;
}