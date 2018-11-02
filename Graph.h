#include <iostream>
using namespace std;

class Edge{//结点
public:
    friend class Graph_List;
    int VerAdj;//邻接顶点序号从0开始
    Edge *link;//下一个结点的指针
};

class Vertex{ //顶点
public:
    friend class Graph_List;
    int VerName;//顶点名称
    Edge *adjacent;//边链表头指针
};

class Graph_List{
private:
    Vertex *Head;
    Vertex *head;
    int graphsize;
public:
    void Build(int,int);
    void Delete(int);
    int GetFirstNeighbor(const int);
    int GetNextNeighbor(const int,const int);
    void RDFS(const int v,int *visited);
    bool Check(const int p,const int q);
    void output_1(int);
    void output_2(int);
    void ReliabilityJudgement(int);
    int BFS(int,int,int);
    void DeleteEdge(int,int,int);
    void DeleteNode(int,int*,int);
    void ImportanceJudgement(int,int);
    void ImportanceJudgement_1(int,int);
    void RecoveryNode(int,int*,int);
    void RecoveryEdge(int,int,int);
    int GetIsolatedNode(int,int,int*);
};
