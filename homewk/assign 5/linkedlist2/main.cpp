/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 205年9月25日, 下午6:12
 */

#include <cstdlib>
#include <vector>
#include "linkedlist.h"

using namespace std;

template<class T>
void print(SimpleV<T> &v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
}

/*
 * 
 */
int main(int argc, char** argv) {
    SimpleV <double>v1(10);
    cout << "initiate size 10 linked list:" << endl;
    print(v1);
    cout << endl << endl;
    cout << "assign value to the list:" << endl;
    for (int i = 0; i < v1.size(); i++) {
        v1[i] = i + 1;
    }
    print(v1);
    cout << endl << endl;
    cout << "copy constructor:" << endl;
    SimpleV<double> vcopy(v1);
    print(vcopy);
    cout << endl << endl;
    cout << "delete value==1 node" << endl;
    v1.extract(1);
    print(v1);
    cout << endl << endl;
    cout << "the first one element in v1 is " << v1.getFirst() << endl;
    cout << "the last one elemnt in v1 is " << v1.getLast() << endl << endl;

    cout << "inset before index 3, value 15 in list vcopy is " << endl;
    vcopy.insertBefore(3, 15);
    print(vcopy);
    cout << endl << endl;
    cout << "inset after index 9, value 16 in list vcopy is " << endl;
    vcopy.insertAfter(9, 16);
    print(vcopy);
    cout << endl << endl;

    return 0;
}

