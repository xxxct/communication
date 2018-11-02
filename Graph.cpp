#include <iostream>
#include <fstream>
#include <queue>
#include"Graph.h"
#include <stdlib.h>
#include <time.h>
#define random(x)(rand()%x)
using namespace std;
int Graph_List::GetFirstNeighbor(const int v){
    if(v==-1) return -1;
    Edge *p=Head[v].adjacent;
    if(p!=NULL)
        return p->VerAdj;
    else return -1;
}
int Graph_List::GetNextNeighbor(const int v1,const int v2){
    if(v1!=-1&&v2!=-1){
        Edge *p=Head[v1].adjacent;
            while(p->VerAdj!=v2&&p!=NULL)
                p=p->link;
        if(p==NULL) return -1;
        p=p->link;
        if(p==NULL) return -1;
        return p->VerAdj;
    }
    return -1;
}

void Graph_List::Build(int N,int M){
    int from,to;
    Head=new Vertex[100];
    for(int i=0;i<N;i++){
        Head[i].VerName=i;
        Head[i].adjacent=NULL;
    }
    int i=0;
    srand((unsigned)time(NULL));
    ofstream fout("fromto.dot");
    ofstream f1("f1.dot");
    f1<<"graph f1{";
    while(i<M){
        from=random(N); //随机生成两个城市
        to=random(N);
        if(!Check(from,to)){//检测两城市是否已经链接,以及两点是同一个点的情况,只有不是这两种情况才能使计数加1
    		fout<<from<<" ";
    		fout<<to<<" ";
    		f1<<from<<"--";
    		f1<<to<<"; ";
            Edge *q=Head[from].adjacent;
            Edge *p=new Edge;
            p->VerAdj=to;
            p->link=NULL;
            if(q==NULL)
                Head[from].adjacent=p;
            else{
                while(q->link!=NULL)
                    q=q->link;
                q->link=p;
            }
            Edge *q1=Head[to].adjacent;
            Edge *p1=new Edge;
            p1->VerAdj=from;
            p1->link=NULL;
            if(q1==NULL)
                Head[to].adjacent=p1;
            else{
                while(q1->link!=NULL)
                    q1=q1->link;
                q1->link=p1;
            }
            i++;
        }
    }
    f1<<"}";
}
void Graph_List::Delete(int N){
    head=new Vertex[100];
    for(int i=0;i<N;i++){
        head[i].VerName=i;
        head[i].adjacent=NULL;
    }
    int *visited=new int[N];//深度优先遍历辅助数组
        for(int k=0;k<N;k++)
            visited[k]=0;
    for(int j=0;j<N;j++){
        RDFS(j,visited);
    }
}
void Graph_List::ReliabilityJudgement(int N){
    int x,y;
    int w=-1;
    ifstream in("fromto.dot");
    int bi=0;
    while(!in.eof()){
        in>>x;
        in>>y;
        DeleteEdge(x,y,w);
        DeleteEdge(y,x,w);
        if(BFS(N,w,w)==0){
		   bi=1;
		}/*每次删除一条连线都检查是否联通,如不联通直接否决*/
		RecoveryEdge(x,y,w);
		RecoveryEdge(y,x,w);/*每次删除检测后都会被恢复以备下次检测其他边*/
	}
	if(bi==0) cout<<"该图是可靠网络"<<endl;
	else cout<<"该图不是可靠网络"<<endl;
}
void Graph_List::ImportanceJudgement(int N,int Q){
	int *vector=new int[N];
	int *vector1=new int[N];
	for(int k=0;k<N;k++)
        vector1[k]=-1;
	int j=0;
	int y=GetIsolatedNode(N,Q,vector1);
	int x;
	for(int i=0;i<N;i++){
		x=y;
	    for(int k=0;k<N;k++)
        vector[k]=-1;
		for(int k=0;k<N;k++){
			if(vector1[k]==i){
				x=y-1;
			}
		}/*考虑要删除检验的节点本身就是独立节点的情况*/
		DeleteNode(i,vector,Q);
		if(BFS(N,x,Q)==0){
			cout<<"城市"<<i<<"需要配备交换机"<<endl;
			j=1;
			string e,ch;
			ifstream f1("f1.dot");
            ofstream f2("f2.dot");
            while(f1.eof()==0){
                getline(f1,e,' ');
                while(e.compare("}")!=0){
                    f2<<e;
                    f2<<' ';
                    getline(f1,e,' ');
            }
            f2<<i<<"[color=red]; "<<"}";
                    f1.close();
                    f2.close();
                    ifstream f_2("f2.dot");
                    ofstream f_1("f1.dot",ios::trunc);
                    getline(f_2,ch);
                    f_1<<ch;
                    f_1.close();
                    f_2.close();
                    remove("f2.dot");

		}}

		RecoveryNode(i,vector,Q);
	}
	if(j==0) cout<<"没有城市需要配备交换机"<<endl;
}

void Graph_List::ImportanceJudgement_1(int N,int Q){
	int *vector=new int[N];
	int *vector1=new int[N];
	for(int k=0;k<N;k++)
        vector1[k]=-1;
	int j=0;
	int y=GetIsolatedNode(N,Q,vector1);
	int x;
	for(int i=0;i<N;i++){
		x=y;
	    for(int k=0;k<N;k++)
        vector[k]=-1;
		for(int k=0;k<N;k++){
			if(vector1[k]==i){
				x=y-1;
			}
		}/*考虑要删除检验的节点本身就是独立节点的情况*/
		DeleteNode(i,vector,Q);
		if(BFS(N,x,Q)==0){
			cout<<"城市"<<i<<"需要配备交换机"<<endl;
			j=1;
			string e,ch;
			ifstream f1("f3.dot");
            ofstream f2("f2.dot");
            while(f1.eof()==0){
                getline(f1,e,' ');
                while(e.compare("}")!=0){
                    f2<<e;
                    f2<<' ';
                    getline(f1,e,' ');
            }
            f2<<i<<"[color=red]; "<<"}";
                    f1.close();
                    f2.close();
                    ifstream f_2("f2.dot");
                    ofstream f_1("f3.dot",ios::trunc);
                    getline(f_2,ch);
                    f_1<<ch;
                    f_1.close();
                    f_2.close();
                    remove("f2.dot");

		}}

		RecoveryNode(i,vector,Q);
	}
	if(j==0) cout<<"没有城市需要配备交换机"<<endl;
}
void Graph_List::RDFS(const int v,int *visited){
    if(visited[v]) return;
    int w=GetFirstNeighbor(v);
    if(w!=-1) visited[v]++;
    while(w!=-1){
        if(!visited[w]){
            Edge *q=head[v].adjacent;
            Edge *p=new Edge;
            p->VerAdj=w;
            p->link=NULL;
            if(q==NULL)
                head[v].adjacent=p;
            else{
                while(q->link!=NULL)
                    q=q->link;
                q->link=p;
            }
            Edge *q1=head[w].adjacent;
            Edge *p1=new Edge;
            p1->VerAdj=v;
            p1->link=NULL;
            if(q1==NULL)
                head[w].adjacent=p1;
            else{
                while(q1->link!=NULL)
                    q1=q1->link;
                q1->link=p1;
            }
            RDFS(w,visited);
        }
        w=GetNextNeighbor(v,w);
    }
}
void Graph_List::DeleteEdge(int x,int y,int Q){
	Edge* q=new Edge;
	Edge* l=new Edge;
	Edge* p=new Edge;
	if(Q==-1){
		q=Head[x].adjacent;
	}
	else{
	    q=head[x].adjacent;
	}
	l=q;
    p=q;
    if(q->VerAdj==y){
    	if(q->link!=NULL&&Q==-1) Head[x].adjacent=q->link;
    	if(q->link!=NULL&&Q!=-1) head[x].adjacent=q->link;
    	if(q->link==NULL&&Q==-1) Head[x].adjacent=NULL;
    	if(q->link==NULL&&Q!=-1) head[x].adjacent=NULL;
    	delete l;
    	return;
	}
    while(p->VerAdj!=y){
    	l=p;
    	p=p->link;
	}
	if(p->link!=NULL) l->link=p->link;
	else l->link=NULL;
	delete p;
    return;
}
void Graph_List::RecoveryEdge(int x,int y,int Q){
	Edge* q=new Edge;
	if(Q==-1) q=Head[x].adjacent;
	else q=head[x].adjacent;
	Edge* l=new Edge;
	l->VerAdj=y;
	l->link=NULL;
	if(q==NULL&&Q==-1) Head[x].adjacent=l;
	if(q==NULL&&Q!=-1) head[x].adjacent=l;
	if(q!=NULL){
	while(q->link!=NULL){
		q=q->link;
	}
	q->link=l;
	}
}
void Graph_List::DeleteNode(int x,int* vector,int Q){
	Edge* q=new Edge;
	if(Q==-1) q=Head[x].adjacent;
	else q=head[x].adjacent;
	int i=0;
	while(q!=NULL){
		vector[i]=q->VerAdj;
		q=q->link;
		i++;
	}
	for(i=0;vector[i]!=-1;i++){
		DeleteEdge(x,vector[i],Q);
		DeleteEdge(vector[i],x,Q);
	}
}
void Graph_List::RecoveryNode(int x,int* vector,int Q){
	for(int i=0;vector[i]!=-1;i++){
		RecoveryEdge(x,vector[i],Q);
		RecoveryEdge(vector[i],x,Q);
	}
}
int Graph_List::GetIsolatedNode(int N,int Q,int* vector1){/*输出所有孤立点以及其数量*/
	int j=0;
	if(Q==-1){
	for(int i=0;i<N;i++){
		if(Head[i].adjacent==NULL){
			vector1[j]=i;
		    j++;
		}
	}
		return j;
	}
	else{
		for(int i=0;i<N;i++){
		if(head[i].adjacent==NULL){
			vector1[j]=i;
			j++;
		}
	}
		return j;
	}
}
int Graph_List::BFS(int N,int w,int Q){/*w启动去点时连通性检测并且w的值代表了在删除检测点之前有多少孤立点,Q是决定是检测去冗余前还是后*/
	int *visited=new int[N];//深度优先遍历辅助数组
    for(int k=0;k<N;k++)
        visited[k]=0;
	queue<int> q;
	Edge* s=new Edge;
	Edge* p=new Edge;
	int count=0;
	for(int k=0;k<N;k++){
		if(Q==-1) s=Head[k].adjacent;
	    else s=head[k].adjacent;
	    if(s!=NULL){
		    q.push(k);
		    break;
		}
	}
	while(!q.empty()){
		int v=q.front();
		visited[v]=1;
		q.pop();
		count++;/*由于结束循环时队列空了,所以每弹出一个计数加一则可以统计队列中的结点个数*/
		if(Q==-1) p=Head[v].adjacent;
		else p=head[v].adjacent;
		while(p!=NULL){/*把与v联通且没被访问过的都压入队列*/
			if(!visited[p->VerAdj]){
				q.push(p->VerAdj);
				visited[p->VerAdj]=1;
			}
			p=p->link;
		}
	}
	int x=N-1;
	if(w==-1){
	if(count==N) return 1;
	}
	else{
		if(count==x-w) return 1;
	}
	return 0;
}/*判断图是否为联通*/
bool Graph_List::Check(const int p,const int q){
    if(p==q) return true;
    int w=GetFirstNeighbor(p);
    while(w!=-1){
        if(w==q)
            return true;
        w=GetNextNeighbor(p,w);
    }
    return false;
}
void Graph_List::output_1(int N){
    for(int i=0;i<N;i++){
            Edge *q=Head[i].adjacent;
            cout<<Head[i].VerName<<"--";
            while(q!=NULL){
                cout<<q->VerAdj<<"--";
                q=q->link;
            }
            cout<<endl;
        }
}
void Graph_List::output_2(int N){
    for(int i=0;i<N;i++){
            Edge *q=head[i].adjacent;
            cout<<head[i].VerName<<"--";
            while(q!=NULL){
                cout<<q->VerAdj<<"--";
                q=q->link;
            }
            cout<<endl;
        }
    int **A=new int*[N];
    for(int i=0;i<N;i++){
            A[i]=new int[N];
        for(int j=0;j<N;j++){
            A[i][j]=0;
        }
    }
    ofstream f3("f3.dot");
    f3<<"graph f3{";
    for(int i=0;i<N;i++){
            Edge *q1=head[i].adjacent;
            while(q1!=NULL){
                if(A[head[i].VerName][q1->VerAdj]==0&&A[q1->VerAdj][head[i].VerName]==0){
                    f3<<head[i].VerName<<"--"<<q1->VerAdj<<"; ";
                    A[head[i].VerName][q1->VerAdj]=1;
                    A[q1->VerAdj][head[i].VerName]=1;
                    q1=q1->link;
                }
                else
                     q1=q1->link;
            }
        }
    f3<<"}";
}
