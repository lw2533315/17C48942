/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年9月16日, 下午4:37
 */

#include <cstdlib>
#include "sVector.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

//    SimpleVector<int> test(10);
//    cout<<test.size()<<endl;
//    test.push_back(11);
//    test.pop_back();
//     test.pop_back();
//      test.pop_back();
//      test.push_back(11);
//      test.push_back(11);
//      test.push_back(11);
//      test.push_back(11);
//    cout<<test.size();
    SimpleVector<int>test1;
    
    test1.pop_back();
    cout<<endl<<test1.size();
    
//  SimpleVector<int> test;
//  test.push_back(1);
//  test.push_back(2);
//   
//  cout<<test.size()<<endl;
//  cout<<test.check()<<endl;
//  
// for (int i=0;i<test.size();i++)
//     cout<<test[i]<<" ";
    return 0;
}

