/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年12月9日, 下午1:56
 */

#include <cstdlib>
//#include "graphnodirection.h"
#include "graghHead1.h"
#include<vector>
#include <string>
#include<iostream>
#include<string>
#include<map>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream ifs;
    ifs.open("input2.txt");
    int nodeNum, arcNum;
    //    cout << "请输入顶点个数，边长个数: ";
    //    cin >> nodeNum >> arcNum;
    ifs >> nodeNum>>arcNum;
    DiGraph g(nodeNum, arcNum);
    ifs.close();

    //    cout<<"path here?";
    cout << "=============================" << endl;
    cout << "print graph information.." << endl;
    g.printGraph();
      cout << "=============================" << endl;
    cout<<"DFS "<<endl;
    ifs.open("input2.txt");
    ifs>>nodeNum>>arcNum;
    DiGraph h(nodeNum,arcNum);
    h.Dfs_traverse();
    cout << "=============================" << endl;
    cout << "Druskals " << endl;
    g.Kruskals();
    cout << "=============================" << endl;
    cout << "Dijkstra..shortest distance." << endl;
    cout << "input the start vertex" << endl;
    int input;
    cin>>input;
    g.Dijkstra(input);

    cout << "=============================" << endl;
    cout << "shortest path" << endl;
    for (int k = 1; k <= input; k++) {
        cout << "v" << input << " to v" << k << "'s shortest path " << g.printDist(k) << ": ";
        g.printPath(k);
        cout << endl;
    }
    for (int k = input + 1; k <= nodeNum; k++) {
        cout << "v" << input << " to v" << k << "'s shortest path " << g.printDist(k) << ": ";
        g.printPath(k);
        cout << endl;
    }


    //    ifs.close();
    return 0;
}

