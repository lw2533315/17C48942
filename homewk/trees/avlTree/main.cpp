/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年12月1日, 下午2:11
 */

#include <cstdlib>
#include "avl.h"
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    Avl<int> a;
    a.insert(10);
    a.insert(8);
    a.insert(6);
    a.insert(9);
    a.insert(11);
    a.insert(13);
    a.insert(12);
    cout<<"insert 10,8,6,9,11,13,12 one by one into avl-tree"<<endl;
    cout<<"inOrder is: ";
    a.inOrder();
    cout<<endl<<"preOrder is: ";
    a.preOrder();
    cout<<endl<<"postOrder is: ";
    a.postOrder();
    cout<<endl;
    a.remove(8);
    cout<<"after delete element 8, the avl tree in inOrder is: ";
    a.inOrder();
     cout<<endl<<"preOrder is: ";
    a.preOrder();
    cout<<endl<<"postOrder is: ";
    a.postOrder();
    return 0;
}

