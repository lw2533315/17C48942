/* 
 * File:   prioritylink.h
 * Author: Administrator
 *
 * Created on 2015年10月7日, 下午4:08
 */

#ifndef PRIORITYLINK_H
#define	PRIORITYLINK_H
#include <bits/stdc++.h>
using namespace std;

template<class T>
class Prioritylink {
protected:

    struct Node {
        T data;
        Node* nNext;

        Node(T d = 0, Node*p = 0) :
        data(d), nNext(p) {
        }
    };
    Node*temp;
    Node* front;
    Node*rear;
    int listSize;
public:
    Prioritylink();
    //    Prioritylink(int);

    ~Prioritylink() {
        //        for(int i=0;i<listSize;i++){
        //             Node*temp = front;
        //             front = front->nNext;
        //            delete temp;
        //            
        //        }
        while (front != 0) {
            //        for(int i=0;i<listSize;i++){
            temp = front;
            front = front->nNext;
            delete temp;
        }
    }

    int size() const {
        return listSize;
    }
    void append(T);
    void prepend();
    void find(T);
    T & operator[](const int&);
};

template<class T>
Prioritylink<T>::Prioritylink() {
    front = rear = 0;
    listSize = 0;
}

template<class T>
void Prioritylink<T>::append(T t) {
    if (front == 0)
        front = rear = new Node(t);
    else {
        temp = new Node(t);
        temp->nNext = front;
        front = temp;
    }
    listSize++;
}

template<class T>
void Prioritylink<T>::prepend() {
    if (listSize == 0)
        cout << "empty";
    else if (listSize == 1) {
        delete front;
        front = rear = 0;
        listSize--;

    } else if (listSize == 2) {
        delete rear;
        rear = front;
        rear->nNext = 0;
        listSize--;

    } else {
        temp = front;
        int index = listSize;
        while (index > 2) {
            temp = temp->nNext;
            index--;
        }
        rear = temp;
        delete rear->nNext;
        rear->nNext = 0;
        listSize--;

    }
}

template <class T>
void Prioritylink<T>::find(T t) {
    //    cout<<listSize<<endl;
    Node* index = front;
    
    for (; index->nNext != 0;) {
        if (index->nNext->data == t) {
//            cout << index->data << endl << endl;
            temp = index->nNext;
            index->nNext = temp->nNext;
            temp->nNext = front;
            front = temp;
        } else {
            index = index->nNext;
        }
    }
};

template<class T>
T & Prioritylink<T>::operator[](const int &sub) {//【】参数必须是const
    //    cout<<sub<<endl;
    if (sub < 0 || sub >= listSize)
        cout << "out of range" << endl;
    else {
        temp = front;
        int num = sub;
        while (num > 0) { //by looping to find the point;
            //注意下标+1才是对应的数
            temp = temp->nNext;
            num--;
        }
        return temp->data;
    }
}



#endif	/* PRIORITYLINK_H */

