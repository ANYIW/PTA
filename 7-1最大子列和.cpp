//在线处理：
//一项一项往后加，和比最大值大，则更新最大值
//和为负数，则抛弃之前的

//普通方法 O(N^3)
int MaxSubseqSum1(int A[],int N){
    int ThisSum,MaxSum=0;
    int i,j,k;
    for(i=0;i<N;i++){
        for(j=i;j<N;j++){
            ThisSum=0;//A[i]到A[j]子列和
            for(k=i;k<=j;k++)//该循环可简化为ThisSum+=A[j];
            ThisSum+=A[k];
            if(ThisSum>MaxSum)
            MaxSum=ThisSum;
        }
    }
    return MaxSum;
}
//分而治之 O(logN)
int Max(int a,int b,int c){
    return ((a>b)?(a>c?a:c):(b>c?b:c));
}
int DivideAndConquer(int List[],int left,int right){
    int mls,mrs;//MaxLeftSum,MaxRightSum
    int lbs,rbs;//LeftBorderSum,RightBorderSum跨边界
    int mlbs,mrbs;//MaxLeftBorderSum,MaxRightBorderSum
    int center,i;
    //递归终止
    if(left==right){
        if(List[left]>0)
        return List[left];
        else return 0;
    }
    //分
    center=(left+right)/2;
    mls=DivideAndConquer(List,left,center);
    mrs=DivideAndConquer(List,center+1,right);
    //治
    lbs=mlbs=0;
    for(i=center;i>=left;i--){//从中间向左扫描
        lbs+=List[i];
        if(lbs>mlbs)
        mlbs=lbs;
    }
    rbs=mrbs=0;
    for(i=center+1;i<=right;i++){//从中间向右扫描
        rbs+=List[i];
        if(rbs>mrbs)
        mrbs=rbs;
    }
    return Max(mls,mrs,(mlbs+mrbs));
}
//在线处理 O(N)
int MaxSubseqSum2(int A[],int N){
    int ThisSum,MaxSum;
    int i;
    ThisSum=MaxSum=0;
    for(i=0;i<N;i++){
        ThisSum+=A[i];
        if(ThisSum>MaxSum)
        MaxSum=ThisSum;
        else 
        if(ThisSum<0)//当前子列和为负则不可能使后面的部分和增大
        ThisSum=0;
    }
    return MaxSum;
}