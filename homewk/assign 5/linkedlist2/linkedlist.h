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
        } 
            };
private:
    Node * front;
    Node* rear;
    int listSize;
    //    int useSize;
    //    void memError();
    void subError();
    void empError();
public:
    SimpleV();
    SimpleV(int);
    SimpleV(SimpleV &object);
    ~SimpleV();
    //    Node* begin();

    int size() const {
        return listSize;
    }
    void append(T);
    void prepend();
    //    T getData(n);
    T getFirst();
    T getLast();
    void extract(T);
        void insertAfter(int,T);
    void insertBefore(int, T);
    T &operator[](const int&);
};

template <typename T>
SimpleV<T>::SimpleV() {
    front = rear = 0;
    listSize = 0;
}

template <typename T>
SimpleV<T>::SimpleV(int n) {
    front = rear = 0;
    listSize = 0;
    if (n >= 1) {
        front = rear = new Node();

        listSize = 1;
        while (n > 1) {
            rear->nodeN = new Node();
            rear = rear->nodeN;
            n--;
            listSize++;
        }
    }
}

template<typename T>
SimpleV<T>::SimpleV(SimpleV& object) {
    this->listSize = object.listSize;
    if (listSize == 0) {
        SimpleV();
    } else {
        //        cout<<"test1"<<"len is " <<len<<endl;
        rear = front = new Node();
        front->node = object[0];
        //          cout<<"test2"<<" object[0] is "<<object[0]<<endl;
        for (int i = 1; i < listSize; i++) {
            rear->nodeN = new Node(object[i]);
            rear = rear->nodeN;
            rear->nodeN = NULL;
        
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

        }
    }

}

template <typename T>
void SimpleV<T>::append(T t) {
    if (front != 0) {
        rear->nodeN = new Node(t);
        rear = rear->nodeN;
        listSize++;

    } else {
        front = new Node(t);
        rear = front;
        listSize++;

    }
}

template <typename T>
void SimpleV<T>::prepend() {
    if (listSize == 0)
        empError();
    else if (listSize == 1) {
        delete front;
        front = rear = 0;
        listSize--;

    } else if (listSize == 2) {
        delete rear;
        rear = front;
        rear->nodeN = 0;
        listSize--;

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

    }
}

template <typename T>
T SimpleV<T>::getFirst() {
    if (front == 0)
        empError();
    else
        return front->node;
}

template<typename T>
T SimpleV<T>::getLast() {
    if (front == 0)
        empError();
    else
        return rear->node;
}

template <typename T>
void SimpleV<T>::extract(T n) {
    Node* temp = front;
    Node*temp1;
    for (; temp->nodeN != NULL;) {
        //         cout<<"here1"<<endl<<"list size"<<listSize<<endl;
        if (temp->nodeN->node == n) {
            //            cout<<"here"<<endl;
            temp1 = temp->nodeN;
            temp->nodeN = temp1->nodeN;
            // temp=temp->nodeN;
            delete temp1;
            listSize--;
        } else
            temp = temp->nodeN;
    }
    if (front->node == n) {
        front = front->nodeN;
        listSize--;
    }
}


template<typename T>
void SimpleV<T>::insertBefore(int index, T data) {
    Node*temp;
    if (index > 9 || index < 0) {
        cout<<"insert positino out of range"<<endl;     
    }
    else if (index == 0) {
        temp = new Node(data);
        temp->nodeN = front;
        front = temp;
        listSize++;
    } else {
        Node*tempBack;
        temp = front;
        for (int i = 1; i < listSize; i++) {
            if (index == i) {
                tempBack = temp->nodeN;
                temp->nodeN = new Node(data);
                temp->nodeN->nodeN = tempBack;
                listSize++;
                break;
            }
            temp = temp->nodeN;
        }
    }
}
template<typename T>
void SimpleV<T>::insertAfter(int index, T data) {
    Node*temp;
    if (index > 9 || index < 0) {
        cout<<"insert positino out of range"<<endl;     
    }
    else if (index ==listSize-1) {
        temp = new Node(data);
        rear->nodeN = temp;
        rear = temp;
        listSize++;
    } else {
        Node*tempBack;
        temp = front;
        for (int i = 0; i < listSize; i++) {
            if (index == i) {
                tempBack = temp->nodeN;
                temp->nodeN = new Node(data);
                temp->nodeN->nodeN = tempBack;
                listSize++;
                break;
            }
            temp = temp->nodeN;
        }
    }
}
#endif	/* LINKEDLIST_H */

