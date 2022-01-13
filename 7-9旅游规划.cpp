#include <stdio.h>
#define INFINITY 501
int G[500][500];
int C[500][500];
int dist[500];
int cost[500];
int collected[500];
void Create(int n,int m){
    //初始化
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){
        if(i!=j){
            G[i][j]=G[j][i]=INFINITY;
            C[i][j]=C[j][i]=INFINITY;
        }
    }
    //读取
    int v1,v2,d,c;
    for(int i=0;i<m;i++){
        scanf("%d%d%d%d",&v1,&v2,&d,&c);
        G[v1][v2]=G[v2][v1]=d;//对称矩阵
        C[v1][v2]=C[v2][v1]=c;
    }
}
void Initialize(int n,int s){
    for(int i=0;i<n;i++){
        dist[i]=G[s][i];
        cost[i]=C[s][i];
    }
}
//寻找未被收录的点中dist最小者
int Scan(int n){
    int min=INFINITY;
    int minPosition=-1;
    for(int i=0;i<n;i++){
        if(collected[i]==0&&dist[i]<min){
            min=dist[i];
            minPosition=i;
        }
    }
    return minPosition;
}
void Dijkstra(int n,int s){
    while(1){
        int v=Scan(n);
        //找不到这样的v
        if(v==-1)
        break;
        //收录v
        collected[v]=1;
        for(int i=0;i<n;i++){
            //对于v的每个未被收录的邻接点
            if(collected[i]==0&&G[v][i]!=INFINITY){
                if(dist[v]+G[v][i]<dist[i]){
                    dist[i]=dist[v]+G[v][i];
                    cost[i]=cost[v]+C[v][i];
                }else{//第一权重相等，比较第二权重
                    if(dist[v]+G[v][i]==dist[i]&&cost[v]+C[v][i]<cost[i])
                    cost[i]=cost[v]+C[v][i];
                }
            }
        }
    }
}
int main(){
    int n,m,s,d;
    scanf("%d%d%d%d",&n,&m,&s,&d);
    Create(n,m);
    Initialize(n,s);
    Dijkstra(n,s);
    printf("%d %d",dist[d],cost[d]);
    return 0;
}