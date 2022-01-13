//利用父子下标的关系和哨兵结点
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 10000
#define MinData -10001
typedef struct Node* Ptr;
struct Node{
    int *data;
    int size;
    int capacity;
};
Ptr Create(int maxsize){
    Ptr Heap=(Ptr)malloc(sizeof(struct Node));
    Heap->data=(int*)malloc(sizeof(int)*(maxsize+1));
    Heap->data[0] =MinData;//最小堆
    Heap->size = 0;
    Heap->capacity=maxsize;
    return Heap;
}
Ptr Insert(Ptr H,int v){
    if(H==NULL)
    return NULL;

    if(H->capacity==H->size)
    return H;

    int i;
    for(i=++H->size;v<H->data[i/2];i/=2){
        H->data[i]=H->data[i/2];
    }
    H->data[i]=v;

    return H;
}
void Print(Ptr H,int i){
    if(H==NULL)
    return;

    if(i>H->size)
    return;

    printf("%d",H->data[i]);
    i/=2;
    while(i!=0){
        printf(" %d",H->data[i]);
        i/=2;
    }
}

int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    Ptr Heap=Create(MaxSize);
    for(int i=0;i<n;i++){
        int v;
        scanf("%d",&v);
        Heap=Insert(Heap,v);
    }
    for(int i=0;i<m;i++){
        int v;
        scanf("%d",&v);
        Print(Heap,v);
        if(i!=m-1)
        printf("\n");
    }
    return 0;
}