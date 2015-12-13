/* 
 * File:   graghHead1.h
 * Author: Administrator
 *
 * Created on 2015年12月9日, 下午1:56
 */

#ifndef GRAGHHEAD1_H
#define	GRAGHHEAD1_H
//#include<queue>
//#include<map>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
const int INFINITE = 999999;

struct arcNode {
    int weight;
    int desVertex; //arc destinate vertex,index
    arcNode *next;
};

struct headNode {
    int inDegree; //connect in arc
    int dist; //shortest distance
    int nodeName;
    int preNode; //a node at least there is a arc from this headnode.
    bool isKnown; //is the shortest distant found
    arcNode*link; //connect vertex and are
};

bool cmp(const pair<pair<int, int>, int>& a, const pair<pair<int, int>, int>& b) {
    return a.second < b.second;
}

class DiGraph {
private:
    headNode* p; //for dijkstra, kruskals;
    //    headNode* p_search; //for DFS list table;
    vector<pair<pair<int, int>, int> >* tree_kru;//for minimum spanning kru
    vector<pair<pair<int, int>, int> >* tree_pri;//for minimum spanning prime 
    vector<pair<pair<int, int>, int> >*backup; //store the arc information
    vector<pair<pair<int, int>, int> >*backup1; //for no direction graph' arc
    int nodeNum;
    int arcNum;
public:
    DiGraph(int, int);
    ~DiGraph();
    const int getWeight(int, int);
    const void printPath(int);
    const void printGraph();
    void Dijkstra(int);
    const int printDist(int);
    void Kruskals();
    void Dfs_traverse(int);
    void DfsStack(headNode*,vector<int>&v,vector<int>&r);
    void Bfs_traverse(int);
    void setArc(headNode*pT, const vector<pair<pair<int, int>, int> >* b);
};

/*use a array to store the headNode, and linklist to connect the arc to the headnode
 */

void DiGraph::setArc(headNode*pT, const vector<pair<pair<int, int>, int> >* b) {
//    cout<<"test input vecotor"<<endl;
//    for(int i=0;i<b->size();i++){
//        cout<<(*b)[i].first.first<<" : "<<(*b)[i].first.second
//        <<"  weight"<<(*b)[i].second<<endl;
//    }
    int begin, end, weight;
    for (int i = 0; i < b->size(); i++) {
        cout<<(*b)[i].first.first<<" : "<<(*b)[i].first.second
        <<"  weight"<<(*b)[i].second<<endl;
        begin = (*b)[i].first.first;
        end = (*b)[i].first.second;
        weight = (*b)[i].second;
        arcNode* node = new arcNode;
        node->desVertex = end - 1;
        node->weight = weight;
        node->next = p[begin - 1].link;
        pT[begin - 1].link = node; //insert the newest arc into the head
        pT[end - 1].inDegree += 1;
    }
//    cout<<"test inDegree of vertex"<<endl;
//        for (int i = 0; i < nodeNum; i++) {
//        cout << p[i].inDegree << " ";
//    }
//    cout << endl;

}

DiGraph::DiGraph(int nNum, int aNum) {
    //    cout<<"before open file"<<endl;
    tree_pri = new vector<pair<pair<int, int>, int> >();
    tree_kru = new vector<pair<pair<int, int>, int> >();
    backup = new vector<pair<pair<int, int>, int> >();
    backup1 = new vector<pair<pair<int, int>, int> >(); //for no direction graph
    //    p_search = new headNode [nodeNum];
    ifstream ifs;
    ifs.open("dfs.txt");
    //    cout<<"after open file"<<endl;
    nodeNum = nNum;
    arcNum = aNum;
    p = new headNode[nodeNum];
    for (int i = 0; i < nodeNum; i++) {
        p[i].inDegree = 0;
        p[i].nodeName = i + 1;
        p[i].preNode = -2; //-1mean self to self, -2 mean error
        p[i].link = NULL;
    }
    for (int i = 0; i < arcNum; i++) {
        int begin, end, weight;
        while (!ifs.eof()) {
            //            cout << "ifs, loop" << endl;
            ifs >> begin >> end>> weight;
            //            cout << begin << " " << end << " " << weight << endl;
            backup->push_back(make_pair(make_pair(begin, end), weight));
            backup1->push_back(make_pair(make_pair(end, begin), weight));

            //            tree_pri->push_back(make_pair(make_pair(begin, end), weight));
            //            arcNode* node = new arcNode;
            //            node->desVertex = end - 1;
            //            node->weight = weight;
            //            node->next = p[begin - 1].link;
            //            p[begin - 1].link = node; //insert the newest arc into the head
            //            p[end - 1].inDegree += 1;
        }
    }
    setArc(p, backup);

    ifs.close();
}

DiGraph::~DiGraph() {
    cout<<"destructor"<<endl;
    delete tree_kru;
    delete tree_pri;
    delete backup;
    delete backup1;
    for (int i = 0; i < nodeNum; i++) {
        arcNode * temp = p[i].link;
        while (temp) {
            arcNode* temp1 = temp->next;
            delete temp;
            temp = temp1;
        }
        p[i].link = NULL;
    }
    delete [] p;
}
void DiGraph::DfsStack(headNode* h, vector<int>& v, vector<int>&r){
    if(r.size()==nodeNum)
        return;
    else{
        int distance=INFINITE;
        int end;//target vertex;
        int index=v.size()-1;//当前点的下标
        arcNode*dTemp=h[v[index]-1].link->next;
        cout<<"headnode's name is "<<h[v[index]-1].nodeName<<endl;
        while(dTemp!=false){//不为空时查找距离最小且未被使用的点
            int dest=dTemp->desVertex;//目标的下标
            cout<<"substript is "<<dTemp->desVertex<<endl;
            if(h[dest].isKnown==false&&dTemp->weight<distance){
                distance=dTemp->weight;
                cout<<"distance is "<<distance<<endl;
//                h[dest].isKnown=true;
                end=dest+1;
                cout<<"next possible node is "<<end<<endl;
            }
           dTemp=dTemp->next;
        }
      
      
        if(distance==INFINITE){//未发现路径回退一格
            cout<<"no path"<<endl;
            v.pop_back();
            DfsStack(h,v,r);
        }else{//发现路径
            cout<<"get path"<<endl;
              h[end-1].isKnown=true;//找到最小路径不要忘记标记为已经路过
                cout<<end-1<<" 小标 is "<<"true"<<endl;
            r.push_back(end);
            v.push_back(end);
            DfsStack(h,v,r);
        }
        
    }
}
void DiGraph::Dfs_traverse(int start) {
    headNode* headTemp = new headNode [nodeNum];
    for (int i = 0; i < nodeNum; i++) {
        headTemp[i].inDegree = 0;
        headTemp[i].nodeName = i + 1;
        headTemp[i].preNode = -2; //-1mean self to self, -2 mean error
        headTemp[i].isKnown=false;//true means 使用过了
        headTemp[i].link = NULL;
    }
    //    setArc(headTemp,backup);
    for (int i = 0; i < backup->size(); i++) {
        backup1->push_back((*backup)[i]);
    }
   
 
    setArc(headTemp, backup1);
     for(int i=0;i<nodeNum;i++){
        cout<<headTemp[i].inDegree<<" ";
    }
//       cout<<endl;
//    for(int i=0;i<backup1->size();i++){
//        cout<<(*backup1)[i].first.first<<" : "<<(*backup1)[i].first.second<<" w: "<<(*backup1)[i].second<<endl;
//    }
    vector<int> dfsV;
    vector<int>dfsR;
    dfsV.push_back(start);//it is a stack，便于后进先出
    dfsR.push_back(start);//store the dfs 结果
    headTemp[start-1].isKnown=true;
    DfsStack(headTemp,dfsV,dfsR);
    for(int i=0;i<dfsR.size();i++)
        cout<<dfsR[i]<<" ";
    cout<<endl;
    



//why here can not delete the pointer ?
//    for (int i = 0; i < nodeNum; i++) {
//        arcNode * temp = headTemp[i].link;
//        while (temp) {
//            arcNode* temp1 = temp->next;
//            delete temp;
//            temp = temp1;
//        }
//        headTemp[i].link = NULL;
//    }delete [] headTemp;
}

void DiGraph::Bfs_traverse(int start) {

}

/*1.从小到大排序
 * 2. 造成联通成环的边舍去。 
 * 方法：不相邻的边的顶点构成不同的set，情况1新边判断如果只有一个顶点在之前的set中，
 * 那么另外一个顶点加入那个set；情况2 如果两个顶点都不在之前的任意一个set，产生一个新set
 * 情况3 如果两个顶点都在一个set中，那么这两个顶点的边舍去
 */
void DiGraph::Kruskals() {
    for (int i = 0; i < backup->size(); i++) {
        tree_kru->push_back((*backup)[i]);
    }
    sort(tree_kru->begin(), tree_kru->end(), cmp);
    vector<pair<pair<int, int>, int> > temp;
    vector<set<int> >vSet;
    temp.push_back((*tree_kru)[0]);
    set<int> sTemp;
    sTemp.insert((*tree_kru)[0].first.first); //the first set of vector
    sTemp.insert((*tree_kru)[0].first.second);
    vSet.push_back(sTemp);
    int index = 1;
    while (temp.size() < nodeNum - 1) {
        bool flag1; //插入set时判断是否成功
        bool flag2;
        vector<set<int> > vSetTemp(vSet); //生成一个与vSet一致的备份vector
        set<int>::iterator itr;
        bool flag3; //合并集合标志
        for (int i = 0; i < vSet.size(); i++) {
            for (int j = i + 1; j < vSet.size(); j++) {
                itr = vSet[j].begin();
                flag3 = true;
                for (itr; itr != vSet[j].end(); itr++) {
                    if (!vSet[i].insert(*itr).second) {
                        flag3 = false;
                    }
                }
                if (flag3)
                    vSet[i] = vSetTemp[i];
                else {
                    vSet.erase(vSet.begin() + j); //如若两个set合并不产生冲突那么删除
                    //移动了元素的set
                    vSetTemp[i] = vSet[i]; //修改备份的信息
                }
            }
        }
        /*  分别找最小权值得边，如果边两个顶点都不相同开新的set，一个相同加入有相同
         * 的set，两个都相同，舍去此边，因为两个都相同会产生回路
         */
        for (int i = 0; i < vSet.size(); i++) {
            flag1 = true;
            flag2 = true;
            if (!vSet[i].insert((*tree_kru)[index].first.first).second) {
                flag1 = false;
            }//插入失败 flag1=false;
            if (!vSet[i].insert((*tree_kru)[index].first.second).second) {
                flag2 = false;
            }
            if (flag1 == false && flag2 == false) {
                tree_kru->erase(tree_kru->begin() + index);
                break;
            } else if (flag1 == false || flag2 == false) {
                temp.push_back(make_pair(make_pair((*tree_kru)[index].first.first,
                        (*tree_kru)[index].first.second), (*tree_kru)[index].second));
                index++;
                break;
            } else {
                if (i == vSet.size() - 1) {
                    vSet[i].erase((*tree_kru)[index].first.first);
                    vSet[i].erase((*tree_kru)[index].first.second);
                    sTemp.clear();
                    sTemp.insert((*tree_kru)[index].first.first);
                    sTemp.insert((*tree_kru)[index].first.second);
                    //                    cout<<"before push vSet is "<<(*tree_kru)[index].first.first
                    //                    <<" "<<(*tree_kru)[index].first.second<<endl;
                    vSet.push_back(sTemp);
                    temp.push_back((*tree_kru)[index]);
                    index++;
                    break;
                } else {
                    vSet[i].erase((*tree_kru)[index].first.first);
                    vSet[i].erase((*tree_kru)[index].first.second);
                }
            }
        }
    }
    (*tree_kru) = temp;
    cout << "the minimum spnning tree: " << endl;
    for (int i = 0; i < tree_kru->size(); i++)
        cout << (*tree_kru)[i].first.first << " : " << (*tree_kru)[i].first.second << " /" <<
            (*tree_kru)[i].second << endl;
}

const int DiGraph::getWeight(int begin, int end) {
    arcNode*temp = p[begin - 1].link;
    while (temp) {
        if (temp->desVertex = end - 1) {
            return temp->weight;
        }
        temp = temp->next;
    }
}

void DiGraph::Dijkstra(int start) {
    //initiat all headnodes
//    cout << "~~~~~~test" << endl;
    for (int i = 0; i < nodeNum; i++) {
        p[i].dist = INFINITE; //set the distance to infinite to the vertex from start node
        p[i].isKnown = false;
    }
    p[start - 1].dist = 0; //the start node ,dist should be 0;
    p[start - 1].preNode = -1; //flag the node is start node;
    //    p[start-1].isKnown=true;
    //    bool flag = false;
    while (true) {
        bool ok = true; //表示是否全部ok
        for (int i = 0; i < nodeNum; i++) {
            //只要有一个顶点的最短路径未知,ok就设置为false
            if (!p[i].isKnown) {
                ok = false;
                break;
            }
        }
        if (ok) return;
        int minIndex = -1;
        /*find the vertex's index, who has the shortest distance and was not known
         */
        for (int i = 0; i < nodeNum; i++) {
            if (!p[i].isKnown) {
                if (minIndex == -1)
                    minIndex = i;
                else if (p[minIndex].dist > p[i].dist)
                    minIndex = i;
            }
        }
        int end, begin, weight;
        p[minIndex].isKnown = true;
        arcNode*tempD = p[minIndex].link; //each loop the vertex who has 
        //the shortest distant is set by isKnown=true;
        while (tempD!=0 ) {
            end = tempD->desVertex + 1; //destination vertex;
            begin = minIndex + 1;
            /*比较end点的disk ，如果从begin点出发的弧线权值加上
             * begin点的disk任然小于他，那么替换掉end点的disk
             */
            if (p[minIndex].dist + tempD->weight < p[end - 1].dist) {
                p[end - 1].dist = p[minIndex].dist + tempD->weight;
                p[end - 1].preNode = minIndex;
            }
            tempD = tempD->next;
        }
    }
    cout << "end suanfa " << endl;
}

const void DiGraph::printPath(int end) {
    if (p[end - 1].preNode == -2) {//degraph judge the vertex's indgree==0;
        return;
    }
    if (p[end - 1].preNode == -1) {
        cout << "v" << end;
    } else if (end != 0) {
        printPath(p[end - 1].preNode + 1);
        cout << " -> v" << end;
    }
}

const void DiGraph::printGraph() {
    for (int i = 0; i < nodeNum; i++) {
        cout << "vertex v" << p[i].nodeName << "inDgree";
        cout << p[i].inDegree << ", arc's number from it: ";
        arcNode *node = p[i].link;
        while (node != NULL) {
            cout << "v" << p[node->desVertex].nodeName << "(weight:" << node->weight << ")" << "  ";
            node = node->next;
        }
        cout << endl;
    }
}

const int DiGraph::printDist(int index) {
    return p[index - 1].dist;
}
#endif	/* GRAGHHEAD1_H */

