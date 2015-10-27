/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年10月23日, 下午10:41
 */

#include <cstdlib>
#include<vector>
#include<map>
#include<set>
#include<iostream>
#include<algorithm>

using namespace std;
struct cmp{
    bool operator () (const pair< int, int > &a, const pair < int, int > &b)  
    {  
//        return  a.second == b.second ? a.first > b.first : a.second < b.second; 
        return a.second<=b.second;
    }  
};

/*
 * 
 */
int main(int argc, char** argv) {
    float mean, median;
    int sum = 0;
    srand(time(0));
    vector<int>v;
    set<int>s;
    map<int, int>m;
    int number = 9;
    vector<int>::iterator vItr;
    set<int>::iterator sItr;
    map<int, int>::iterator mItr;
    for (int i = 0; i < number; i++) {
        v.push_back(rand() % number);
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < number; i++) {
        cout << v[i] << " ";
    }
    for (vItr = v.begin(); vItr != v.end(); vItr++) {
        sum += *vItr;
    }
    mean = (float) sum / v.size();
    int index;
    if (v.size() % 2 == 0) {
        index = v.size() / 2;
        median = (float) (v[index - 1] + v[index]) / 2;
    } else {
        index = v.size() / 2;
        median = (float) v[index];
    }
    cout << endl << "mean is " << mean << endl << "median is " << median << endl;
    for (vItr = v.begin(); vItr != v.end(); vItr++) {
        if (s.insert(*vItr).second)//when insert set succeed, insert map at the same time;
            m.insert(pair<int, int>(*vItr, 0));
    }
    for (int i = 0; i < v.size(); i++) {//find the mode for every key in map
        m[v[i]]++;
    }
       int big = 0;
//    for (mItr = m.begin(); mItr != m.end(); mItr++) {//find the biggist mode
//        big = max(big, mItr->second);
//    }
     big=max_element(m.begin(),m.end(),cmp())->second; 
    cout << "the mode is  ";
    for (mItr = m.begin(); mItr != m.end(); mItr++) {
        if (mItr->second == big)
            cout << mItr->first << " ";
    }
    return 0;
}


