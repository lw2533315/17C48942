/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年9月29日, 上午10:29
 */

#include <bits/stdc++.h>
#include "linkedlist1.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    SimpleV<int> v(2);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.pop_back();
    v.pop_back();
    
    for(int i=0;i<5;i++)
        v.push_back(i);
    for(int i=0;i<v.size();i++)
        cout<<v[i];

    return 0;
}

