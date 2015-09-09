/* 
 * File:   d2array.h
 * Author: Administrator
 *
 * Created on 2015年9月3日, 上午11:11
 */

#ifndef D2ARRAY_H
#define	D2ARRAY_H
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

template<typename T>
class Array {
private:
    int col;
    int *d1array;
    T **d2array;
public:
    Array(int size);
    ~Array() {
        delete []d1array;
        for (int i = 0; i < col; i++) {
            delete []d2array[i];
        }
        delete []d2array;
//        cout<<"destructor"<<endl;
    }
    T** fillArray();
    void prnt1Ary() const;
    void prnt2Ary() const;

};
template<typename T>
Array<T>::Array(int size) {
    srand(time(0));
    col = size;
    d1array = new int [size];
    for (int i = 0; i < size; i++) {
        d1array[i] = i + 1;
    }
}
template<typename T>
void Array<T>::prnt2Ary() const {
    cout << endl;
    for (int row = 0; row < col; row++) {
        for (int colum = 0; colum < d1array[row]; colum++) {
            cout << d2array[row][colum] << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}
template<typename T>
void Array<T>::prnt1Ary() const {
    cout << endl;
    for (int i = 0; i < col; i++) {
        cout << d1array[i] << " ";
    }
}
template<typename T>
T** Array<T>::fillArray() {
    d2array = new T*[col];
    for (int i = 0; i < col; i++) {
        d2array[i] = new T [d1array[i]];
    }
    for (int row = 0; row < col; row++) {
        for (int colum = 0; colum < d1array[row]; colum++) {
            d2array[row][colum] = static_cast<T>(rand() % 8999+1000)/100;
        }
    }
   return d2array;
}


#endif	/* D2ARRAY_H */

