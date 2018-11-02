#include <iostream>
using namespace std;
#include <stdlib.h>
#include<windows.h>
#include"Graph.h"
#define random(x)(rand()%x)
int main(){
    int N,M,Q=-1;
    bool tt=false;
    while(!tt){
    cout<<"请输入城市个数："<<endl;
    cin>>N;
    cout<<"请输入通讯路线个数："<<endl;
    cin>>M;
    if(N*(N-1)/2>=M)
        tt=true;
    else
        cout<<"路径过多，请重新输入"<<endl;
    }
    Graph_List A;
    A.Build(N,M);
    cout<<"下面输出一个存在冗余的图"<<endl;
    A.output_1(N);
    A.ReliabilityJudgement(N);
    A.ImportanceJudgement(N,Q);
    A.Delete(N);
    cout<<"下面输出一个去掉冗余的图"<<endl;
    A.output_2(N);
    Q=0;
    A.ImportanceJudgement_1(N,Q);
    system("dot -Tpng f1.dot -o f1.png");
    system("dot -Tpng f3.dot -o f3.png");
    system("start f1.png");
    system("start f3.png");

}



