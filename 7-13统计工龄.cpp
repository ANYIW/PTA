#include <stdio.h>
int a[51];
void PrintReturn(){
    static int i=0;
    if(i!=0)
    printf("\n");
    i++;
}
int main(){
    int n;
    scanf("%d",&n);
    int age;
    for(int i=0;i<n;i++){
        scanf("%d",&age);
        a[age]++;
    }
    for(int i=0;i<51;i++){
        if(a[i]!=0){
            PrintReturn();
            printf("%d:%d",i,a[i]);
        }
    }
    return 0;
}