#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iomanip>
#include <queue>
#include<iostream>
const int INT_MAX = 99999;
using namespace std;
// 定义顶点邻接表的节点结构

class edgeNode {
public:
    edgeNode(int = -1, int = 0); // 构造函数
    int adjVertex; // 该边中的邻接顶点在顶点表中的序号
    int weight; // 该边的权值
    edgeNode *next;
};
// 构造函数
// 参数a为邻接顶点的序号；参数w为边的权值，默认权值为0

edgeNode::edgeNode(int a, int w) : adjVertex(a), weight(w), next(NULL) {
}
// 定义顶点表的节点

template <class VertexType>
class VertexNode {
public:
    void ClearedgeList(); // 删除这个顶点的邻接表
    bool Appendedge(int, int = 0); // 在这个顶点的邻接表中加入一条边
    bool Removeedge(int); // 在这个顶点的邻接表中删除一条边
    VertexType data; // 顶点的数据
    edgeNode *edgeList; // 顶点邻接表的首节点指针
};
// 清空一个顶点的邻接表，释放邻接表各节点

template<class VertexType>
void VertexNode<VertexType>::ClearedgeList() {
    edgeNode *p, *q;
    p = edgeList;
    while (p != NULL) {
        q = p->next;
        delete p;
        p = q;
    }
    edgeList = NULL;
}
// 在这个顶点的邻接表中加入一条边
// 参数v为加入边中邻接顶点序号，wgh为加入边的权值

template<class VertexType>
bool VertexNode<VertexType>::Appendedge(int v, int wgh) {
    edgeNode *p = edgeList;
    edgeNode *q = NULL;
    // 找到链接表中末节点，末节点的指针赋值给q。如果发现有一个节点的adjVex的值和v相同，则返回false
    while (p != NULL) {
        if (p->adjVertex == v)
            return false;
        q = p;
        p = p->next;
    }
    // 在邻接表的最后加上一条边
    p = new edgeNode(v, wgh);
    if (q == 0)
        edgeList = p;
    else
        q->next = p;
    return true;
}
// 在顶点的邻接表中删除一条边
// 参数v为要删除边的邻接顶点序号

template <class VertexType>
bool VertexNode<VertexType>::Removeedge(int v) {
    edgeNode *p = edgeList;
    edgeNode *q = NULL;
    // 遍历邻接表，如果发现这条边，则删除
    while (p != NULL) {
        if (p->adjVertex == v) {
            if (p == edgeList)
                edgeList = p->next;
            else
                q->next = p->next;
            delete p;
            return true;
        }
        q = p;
        p = p->next;
    }
    return false;
}
// 图的邻接表定义
// VertexType是顶点的数据类型，如果VertexType不是简单的数据类型，在定义VertexType时，必须重载==运算符用于判断两个顶点数据是否相等

template <class VertexType>
class ALGraph {
public:

    enum GraphStyle // 图的类型
    {
        DG, // 有向图
        DN, // 有向网
        UDG, // 无向图
        UDN // 无向网
    };
    ALGraph(int = 0, GraphStyle = UDG); // 构造函数，默认图的类型为无向图
    ~ALGraph();
    int LocateVertex(const VertexType&); // 根据顶点的数据，找到顶点在顶点表中的序号
    inline int GetNumVertices(); // 取得图中的顶点数目
    bool GetVertex(int, VertexType&); // 根据序号，取得顶点的数据
    bool SetVertex(int, const VertexType&); // 根据序号，设置顶点的数据  
    bool InsertVertex(const VertexType&); // 插入一个顶点
    bool DeleteVertex(const VertexType&); // 删除一个顶点
    bool Insertedge(const VertexType&, const VertexType&, int = 0); // 插入一条边
    bool Deleteedge(const VertexType&, const VertexType&); // 删除一条边
    int GetFirstAdjVex(int); // 根据序号，取得顶点的第一个邻接顶点的序号
    int GetNextAdjVex(int v, int w); // 根据序号，取得v(相对于w)的下一个邻接顶点序号
    bool Getedge(int, int, edgeNode*&); // 根据顶点序号，取得两顶点之间的边
    inline int GetNumedges(); // 取得图中的边数
    void DFSTraverse(void (*Visit)(const VertexType&)); // 深度优先遍历图
    void BFSTraverse(void (*Visit)(const VertexType&)); // 广度优先遍历图

private:
    void DFS(void (*Visit)(const VertexType&), int); // 从一个顶点出发深度优先遍历图
    VertexNode<VertexType> *vertices; // 顶点表
    int numVertices; // 顶点个数
    int numedges; // 边数
    int maxVertices; // 最多可存放的顶点个数
    GraphStyle style; // 图的类型
    bool *visited; // 在遍历时存放是否访问过的标志
};
// 构造函数
// 参数s为该图最多可存放的顶点个数；gs为图的类型，默认为无向图UDG

template <class VertexType>
ALGraph<VertexType>::ALGraph(int s, GraphStyle gs) : numVertices(0), numedges(0), maxVertices(s), style(gs) {
    if (s > 0)
        vertices = new VertexNode<VertexType>[s];
}
// 析构函数

template <class VertexType>
ALGraph<VertexType>::~ALGraph() {
    for (int i = 0; i < numVertices; i++)
        vertices[i].ClearedgeList();
    if (maxVertices != 0)
        delete[] vertices;
}
// 根据顶点的数据，找到顶点在顶点表中的序号
// 参数vex为顶点的数据
// 返回值为顶点的序号。如返回-1，未找到相关的顶点

template <class VertexType>
int ALGraph<VertexType>::LocateVertex(const VertexType & vex) {
    for (int i = 0; i < numVertices; i++)
        if (vertices[i].data == vex)
            return i;
    return -1;
}
// 取得图的顶点数目

template <class VertexType>
int ALGraph<VertexType>::GetNumVertices() {
    return numVertices;
}
// 取得图的边数目

template <class VertexType>
int ALGraph<VertexType>::GetNumedges() {
    return numedges;
}
// 根据顶点的序号，取得顶点的数据
// 参数v为顶点序号；参数vex用于返回顶点数据

template <class VertexType>
bool ALGraph<VertexType>::GetVertex(int v, VertexType& vex) {
    if (v < 0 || v >= numVertices)
        return false;

    vex = vertices[v].data;
    return true;
}
// 根据顶点的序号，设置顶点的数据
// 参数v为顶点序号；参数vex用于设置的顶点数据

template <class VertexType>
bool ALGraph<VertexType>::SetVertex(int v, const VertexType &vex) {
    if (v < 0 || v >= numVertices)
        return false;
    vertices[v].data = vex;
    return true;
}
// 在图中插入一个顶点
// 参数vex为要插入的顶点数据

template <class VertexType>
bool ALGraph<VertexType>::InsertVertex(const VertexType &vex) {
    // 如果存在的顶点个数已达最大值，则返回
    if (numVertices == maxVertices)
        return false;
    // 判断相同的顶点是否存在，如存在，则返回
    for (int i = 0; i < numVertices; i++)
        if (vertices[i].data == vex)
            return false;
    // 增加一个顶点项
    vertices[numVertices].data = vex;
    vertices[numVertices++].edgeList = NULL;
    return true;
}
// 在图中删除一个顶点
// 参数vex为欲删除顶点的值

template <class VertexType>
bool ALGraph<VertexType>::DeleteVertex(const VertexType &vex) {
    int i;
    int v;
    // 在顶点表中找到要删除顶点的序号，如果没找到则返回
    if ((v = LocateVertex(vex)) == -1)
        return false;

    // 遍历其它顶点，如果这些顶点的邻接表中包含了要删除的顶点，则移除
    for (i = 0; i < numVertices; i++)
        if (i != v) {
            if (vertices[i].Removeedge(v))
                numedges--;
        }
    // 在顶点表中删除序号为v的顶点
    vertices[v].ClearedgeList();
    for (i = v; i < numVertices - 1; i++)
        vertices[i] = vertices[i + 1];
    numVertices--;
    // 如果在所有的邻接边表中的顶点序号大于要删除的顶点序号，但将顶点序号减1
    edgeNode *p;
    for (i = 0; i < numVertices; i++) {
        // 遍历该顶点的邻接边点，调整邻接顶点序号
        p = vertices[i].edgeList;
        while (p != NULL) {
            if (p->adjVertex > v) // 判断邻接顶点号是否大于要删除的顶点号
                p->adjVertex--; // 如果>v，则将顶点号减1
            p = p->next;
        }
    }
    return true;
}
// 在图中插入一条边
// 参数vex1、vex2为要插入边的两个顶点的值；参数wgh为欲插入边的权值，默认值为0

template <class VertexType>
bool ALGraph<VertexType>::Insertedge(const VertexType &vex1, const VertexType &vex2, int wgh) {
    // 找到两个顶点在顶点表中的序号，分别赋值给v1、v2
    // 两个顶点中只要有一个在图的顶点表中未找到，则返回
    int v1 = LocateVertex(vex1);
    int v2 = LocateVertex(vex2);
    if (v1 == -1 || v2 == -1)
        return false;
    // 为第一个顶点的邻接表中增加一条边
    vertices[v1].Appendedge(v2, wgh);
    // 如果为无向图，则必须在另一顶点的邻接表中增加一条边
    if (style == UDG || style == UDN)
        vertices[v2].Appendedge(v1, wgh);
    numedges++;
    return true;
}
// 在图中删除一条边
// 参数vex1、vex2为要删除边的两个顶点数据

template <class VertexType>
bool ALGraph<VertexType>::Deleteedge(const VertexType &vex1, const VertexType &vex2) {
    // 找到两个顶点在顶点表中的序号，分别赋值给v1、v2
    // 两个顶点中只要有一个在图的顶点表中未找到，则返回
    int v1 = LocateVertex(vex1);
    int v2 = LocateVertex(vex2);
    if (v1 == -1 || v2 == -1)
        return false;
    // 为第一个顶点的邻接表中增加一条边
    vertices[v1].Removeedge(v2);
    // 如果为无向图，则必须在另一顶点的邻接表中增加一条边
    if (style == UDG || style == UDN)
        vertices[v2].Removeedge(v1);
    numedges--;
    return true;
}
// 取得图中第v个顶点的第一个邻接顶点序号

template <class VertexType>
int ALGraph<VertexType>::GetFirstAdjVex(int v) {
    if (v < 0 || v >= numVertices)
        return -1;
    if (vertices[v].edgeList == NULL)
        return -1;
    else
        return vertices[v].edgeList->adjVertex;
}
// 根据序号，取得v(相对于w)的下一个邻接顶点序号

template <class VertexType>
int ALGraph<VertexType>::GetNextAdjVex(int v, int w) {
    if (v < 0 || v >= numVertices)
        return -1;

    edgeNode *p = vertices[v].edgeList;
    while (p != NULL) {
        if (p->adjVertex == w)
            break;
        p = p->next;
    }
    if (p == NULL || p->next == NULL)
        return -1;
    return p->next->adjVertex;
}
// 根据顶点序号，取得两顶点之间的边

template <class VertexType>
bool ALGraph<VertexType>::Getedge(int v, int w, edgeNode*& edge) {
    if (v < 0 || v >= numVertices)
        return false;
    if (w < 0 || w >= numVertices)
        return false;
    edge = vertices[v].edgeList;
    while (edge != NULL) {
        if (edge->adjVertex == w)
            break;
        edge = edge->next;
    }
    return edge != NULL;
}
// 以深度优先的方法遍历图
// 参数Visit是遍历到每一顶点时调用的函数

template <class VertexType>
void ALGraph<VertexType>::DFSTraverse(void (*Visit)(const VertexType &)) {
    int v;

    // 每一顶点的访问标志置为false
    visited = new bool[numVertices];
    for (v = 0; v < numVertices; v++)
        visited[v] = false;
    // 以顶点表中的每一未访问过的顶点出发进行遍历
    for (v = 0; v < numVertices; v++)
        if (!visited[v])
            DFS(Visit, v);

    delete[] visited;
}
// 从某一顶点出发，递归地以深度优先的方法遍历图
// 参数v是出发顶点在顶点表的序号

template <class VertexType>
void ALGraph<VertexType>::DFS(void (*Visit)(const VertexType&), int v) {
    // 设置序号为v的顶点的访问标志，并调用Visit函数访问它
    visited[v] = true;
    Visit(vertices[v].data);
    // 查找序号为v的顶点的所有邻接顶点，该邻接顶点的序号为w，对w递归调用DFS
    edgeNode *p = vertices[v].edgeList;
    while (p != NULL) {
        int w = p->adjVertex;
        if (!visited[w])
            DFS(Visit, w);
        p = p->next;
    }
}
// 以广度优先的方法遍历图
// 参数Visit是遍历到每一顶点时调用的函数

template <class VertexType>
void ALGraph<VertexType>::BFSTraverse(void (*Visit)(const VertexType &)) {
    int v;
    std::queue<int> vertexQueue; // 辅助队列
    edgeNode *p;

    // 每一顶点的访问标志置为false
    visited = new bool[numVertices];
    for (v = 0; v < numVertices; v++)
        visited[v] = false;

    // 以顶点表中的每一未访问过的顶点出发进行遍历
    for (v = 0; v < numVertices; v++) {
        if (visited[v])
            continue;
        visited[v] = true;
        Visit(vertices[v].data);
        vertexQueue.push(v);
        while (!vertexQueue.empty()) {
            int u = vertexQueue.front();
            vertexQueue.pop();
            p = vertices[u].edgeList;
            while (p != NULL) {
                int w = p->adjVertex;
                if (!visited[w]) {
                    visited[w] = true;
                    Visit(vertices[w].data);
                    vertexQueue.push(w);
                }
                p = p->next;
            }
        }
    }
    delete[] visited;
}
///////////////////////////
////  最小生成树
///////////////////////////
// 返回给定数组中，非0最小元素的下标值

int Minimum(int arr[], int n) {
    int i;
    int min = 0;
    for (i = 1; i < n; i++) {
        if (arr[i] > 0) {
            min = i;
            break;
        }
    }
    for (i = min; i < n; i++) {
        if (arr[i] > 0 && arr[i] < arr[min])
            min = i;
    }
    return min;
}
// Prim算法
// 从第0个顶点出发,计算并打印网g的最小生成树

template <class VertexType>
void Prim(ALGraph<VertexType>& g) {
    if (g.GetNumVertices() == 0) {
        cout << "图中无顶点!" << endl;
        return;
    }
    int i, j, k = 0;
    VertexType vex;
    edgeNode *edge = NULL;
    int *lowcost = new int[g.GetNumVertices()];
    VertexType *U = new VertexType[g.GetNumVertices()];
    for (i = 0; i < g.GetNumVertices(); i++) {
        lowcost[i] = INT_MAX;
    }
    for (i = 0; i < g.GetNumVertices(); i++) {
        if (i != k && g.Getedge(k, i, edge)) {
            lowcost[i] = edge->weight;
            g.GetVertex(k, U[i]);
        }
    }
    g.GetVertex(k, U[k]);
    lowcost[k] = 0;
    for (i = 1; i < g.GetNumVertices(); i++) {
        k = Minimum(lowcost, g.GetNumVertices());
        g.GetVertex(k, vex);
        cout << U[k] << " --> " << vex << " : " << lowcost[k] << endl;
        lowcost[k] = 0;
        for (j = 0; j < g.GetNumVertices(); j++) {
            if (g.Getedge(k, j, edge) && edge->weight < lowcost[j]) {
                lowcost[j] = edge->weight;
                g.GetVertex(k, U[j]);
            }
        }
    }
    delete[] lowcost;
    delete[] U;
}
////////////////////
////// 拓扑
////////////////////
// 对图g中的各顶点求入度，存入inArr

template<class VertexType>
void FindInDegree(ALGraph<VertexType>& g, int inArr[]) {
    int i, v;
    for (i = 0; i < g.GetNumVertices(); i++)
        inArr[i] = 0;
    for (i = 0; i < g.GetNumVertices(); i++) {
        v = g.GetFirstAdjVex(i);

        while (v != -1) {
            inArr[v]++;
            v = g.GetNextAdjVex(i, v);
        }
    }
}
// 拓扑排序
// 有向图g采用邻接表存储结构
// 若有向图g中无回路，此函数通过topoArr返回一个顶点序号的拓扑序列，并返回true；否则false
// toppArr存放拓扑次序
// count纯属多余，是否应该去掉，直接用i会不会理解不便？

template<class VertexType>
bool TopologicalSort(ALGraph<VertexType>& g, int* topoArr)//, int* ve)
{
    queue<int> q; // 存放度为0的顶点的序号
    VertexType vex;
    int count = 0;
    int i;
    int w;
    int* inDegree = new int[g.GetNumVertices()]; // 存放顶点的入度

    FindInDegree(g, inDegree); // 计算所有顶点的入度
    for (i = 0; i < g.GetNumVertices(); i++) // 入度为0的顶点进队列
        if (inDegree[i] == 0)
            q.push(i);
    i = 0;
    while (!q.empty()) {
        topoArr[i++] = q.front();
        for (w = g.GetFirstAdjVex(q.front()); w != -1; w = g.GetNextAdjVex(q.front(), w)) {
            if (--inDegree[w] == 0)
                q.push(w);
        }
        q.pop();
        count++;
    }
    delete[] inDegree;
    return count == g.GetNumVertices();
}
// 打印有向网g的关键路径

template<class VertexType>
void PrintCriticalPath(ALGraph<VertexType>& g) {
    int i, j;
    VertexType vex, start, end;
    int w;
    edgeNode* edge;
    int *ve;
    int *vl;
    int *pArr = new int[g.GetNumVertices()];
    if (!TopologicalSort(g, pArr)) {
        cout << "Graph has a circle!" << endl;
        delete[] pArr;
        return;
    }
    ve = new int[g.GetNumVertices()];
    vl = new int[g.GetNumVertices()];
    for (i = 0; i < g.GetNumVertices(); i++)
        ve[i] = 0;
    for (i = 0; i < g.GetNumVertices(); i++) {
        for (w = g.GetFirstAdjVex(pArr[i]); w != -1; w = g.GetNextAdjVex(pArr[i], w)) {
            g.Getedge(pArr[i], w, edge);
            //由于VC6.0放弃使用max
            ve[w] = (ve[w] > ve[pArr[i]] + edge->weight) ? ve[w] : ve[pArr[i]] + edge->weight;
        }
    }
    for (i = 0; i < g.GetNumVertices(); i++)
        vl[i] = ve[g.GetNumVertices() - 1];
    for (i = g.GetNumVertices() - 1; i >= 0; i--) {
        for (w = g.GetFirstAdjVex(pArr[i]); w != -1; w = g.GetNextAdjVex(pArr[i], w)) {
            g.Getedge(pArr[i], w, edge);
            //由于VC6.0放弃使用min
            vl[pArr[i]] = (vl[pArr[i]] <= vl[w] - edge->weight) ? vl[pArr[i]] : vl[w] - edge->weight;
        }
    }
    cout << "|  起点  |  终点  |   最早开始时间   |   最迟完成时间   |  差值  |  备注  |" << endl;
    for (i = 0; i < g.GetNumVertices(); i++) {
        for (w = g.GetFirstAdjVex(i); w != -1; w = g.GetNextAdjVex(i, w)) {
            g.Getedge(i, w, edge);
            g.GetVertex(i, start);
            g.GetVertex(w, end);
            cout << setiosflags(ios::right)
                    << setw(6) << start
                    << setw(9) << end
                    << setw(14) << ve[i]
                    << setw(19) << vl[w]
                    << setw(14) << edge->weight
                    << setw(12) << (ve[i] == vl[w] - edge->weight ? "关键路径" : "") << endl;
        }
    }
    delete[] ve;
    delete[] vl;
    delete[] pArr;
}
///////////////////////////
//// 最短路径
///////////////////////////

struct TableEntry {
    bool known;
    int dist; // 距离
    int preVertex; // 前驱节点
};
// 返回table中known为false且dist最小的元素的位置
// n是table数组长度

int SmallestUnknownDistIndex(TableEntry table[], int n) {
    int min = INT_MAX;
    int i;
    int index = -1;
    for (i = 0; i < n; i++) {
        if (table[i].known)
            continue;
        if (table[i].dist < min) {
            min = table[i].dist;
            index = i;
        }
    }
    return index;
}
// 用Dijkstra算法求有向图g的顶点vex到其余顶点的最短路径，返回TableEntry类型数组

template <class VertexType>
TableEntry* ShortestPath_DIJ(ALGraph<VertexType>& g, VertexType vex) {
    int i, v, w;
    int start = g.LocateVertex(vex);
    edgeNode* edge;
    TableEntry* table = new TableEntry[g.GetNumVertices()];
    //init table
    for (i = 0; i < g.GetNumVertices(); i++) {
        table[i].known = false;
        table[i].dist = INT_MAX;
        table[i].preVertex = -1;
    }
    table[start].dist = 0;
    while (true) {
        v = SmallestUnknownDistIndex(table, g.GetNumVertices());
        if (v == -1)
            break;
        table[v].known = true;
        for (w = g.GetFirstAdjVex(v); w != -1; w = g.GetNextAdjVex(v, w)) {
            if (!table[w].known) {
                g.Getedge(v, w, edge);
                if (table[v].dist + edge->weight < table[w].dist) {
                    table[w].dist = table[v].dist + edge->weight;
                    table[w].preVertex = v;
                }
            }
        }
    }
    return table;
}
// 打印table中起点到顶点end的最短路径

template <class VertexType>
void PrintPath(ALGraph<VertexType>& g, VertexType end, TableEntry table[]) {
    int v = g.LocateVertex(end);
    VertexType vex;
    if (table[v].preVertex != -1) {
        g.GetVertex(table[v].preVertex, vex);
        PrintPath(g, vex, table);
        cout << " ---> ";
    }
    cout << end;
}
#endif