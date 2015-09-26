/* 
 * File:   linkedlist.h
 * Author: Administrator
 *
 * Created on 2015年9月25日, 下午6:13
 */

#ifndef LINKEDLIST_H
#define	LINKEDLIST_H
#include<iostream>
#include<new>
#include<cstdlib>
using namespace std;

template <typename T>
class SimpleV {
private:

    struct Node {
        T node;
        Node *nodeN;

        Node(const T&a = 0, Node*p = 0) : node(a), nodeN(p) {
        } //struct constructor, nodeN 
        //defaut value is 0
    };
    Node * front;
    Node* rear;
    int listSize;
    int useSize;
    //    void memError();
    void subError();
    void empError();
public:
    SimpleV();
    SimpleV(int);
    ~SimpleV();

    int size() const {
        return useSize;
    }
    void pop_back();
    void push_back(T);
    T &operator[](const int&);
};

template <typename T>
SimpleV<T>::SimpleV() {
    front = rear = 0;
    listSize = useSize = 0;
}

template <typename T>
SimpleV<T>::SimpleV(int n) {
    front = rear = 0;
    listSize = useSize = 0;
    if (n >= 1) {
        front = rear = new Node();
        useSize = listSize = 1;
        while (n > 1) {
            rear->nodeN = new Node();
            rear = rear->nodeN;
            n--;
            listSize++;
            useSize++;
        }
    }
}

template<typename T>
T & SimpleV<T>::operator[](const int &sub) {//【】参数必须是const
    //    cout<<sub<<endl;
    if (sub < 0 || sub >= listSize)
        subError();
    else {
        Node *temp = front;
        int num = sub;
        while (num > 0) { //by looping to find the point;
            //注意下标+1才是对应的数
            temp = temp->nodeN;
            num--;
        }
        return temp->node;
    }
}

template <class T>
void SimpleV<T>::subError() {
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

template <class T>
void SimpleV<T>::empError() {
    cout << "ERROR: out of range\n";
    exit(EXIT_FAILURE);
}

template <typename T>
SimpleV<T>::~SimpleV() {//delete front the front  
    if (listSize == 0) {
        delete front;
    } else {
        while (listSize > 0) {
            Node *temp = front;
            front = front->nodeN;
            delete temp;
            listSize--;
            useSize--;
        }
    }

}

template <typename T>
void SimpleV<T>::push_back(T t) {
    if (front != 0) {
        rear->nodeN = new Node(t);
        rear = rear->nodeN;
        listSize++;
        useSize++;
    } else {
        front = new Node(t);
        rear = front;
        listSize++;
        useSize++;
    }
}

template <typename T>
void SimpleV<T>::pop_back() {
    if (listSize == 0)
        empError();
    else if (listSize == 1) {
        delete front;
        front = rear = 0;
        listSize--;
        useSize--;
    } else if (listSize == 2) {
        delete rear;
        rear = front;
        rear->nodeN = 0;
        listSize--;
        useSize--;
    } else {
        Node* temp = front;
        int index = listSize;
        while (index > 2) {
            temp = temp->nodeN;
            index--;
        }
        rear = temp;
        delete rear->nodeN;
        rear->nodeN = 0;
        listSize--;
        useSize--;
    }
}



#endif	/* LINKEDLIST_H */

