/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 205年9月25日, 下午6:12
 */

#include <cstdlib>
#include "linkedlist.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    SimpleV <double>v1(20);
    cout<<v1[19]<<endl;
    SimpleV <int> v;
    v.push_back(10);
   
    v.push_back(11);
    v.pop_back();
      
    v.push_back(12);
    v[1]=22;

    v.push_back(13);
//        cout<<" size: "<<v.size()<<endl;

    v.push_back(14);
//        cout<<" size: "<<v.size()<<endl;


    for(int i=0;i<v.size();i++)
        cout<<v[i]<<" ";
    
    return 0;
}

