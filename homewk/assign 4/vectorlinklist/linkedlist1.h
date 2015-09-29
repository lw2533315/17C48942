/* 
 * File:   linkedlist1.h
 * Author: Administrator
 *
 * Created on 2015年9月29日, 上午10:31
 */

#ifndef LINKEDLIST1_H
#define	LINKEDLIST1_H

/* 
 * File:   linkedlist.h
 * Author: Administrator
 *
 * Created on 2015年9月25日, 下午6:13
 */


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
        Node(const T &a = 0, Node*p = 0) : node(a), nodeN(p) {
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
        front = new Node();
        rear=front;
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
    if (sub < 0 || sub >= useSize)
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
            listSize--;
            delete temp;
            }
    }
}

template <typename T>
void SimpleV<T>::push_back(T t) {
    if(useSize<listSize){
        cout<<"rear node = "<<rear->node<<endl;
        rear = rear->nodeN;
        rear->node=t;
//        rear->node=t;
//        rear=rear->nodeN;
        useSize++;
    }else {
        if(listSize!=0){
//            cout<<"rearnode"<<rear->node<<endl;
            rear->nodeN=new Node(t);
            
            
             rear=rear->nodeN;
            Node*temp=rear;
           
            for(int i=0;i<listSize-1;i++){
                
                temp->nodeN=new Node();
                temp=temp->nodeN;
            }
            useSize++;
            listSize*=2;

        }
        else{
            front=rear=new Node(t);
            useSize=listSize=1;

        }
    }
}
template <typename T>
void SimpleV<T>::pop_back() {
    if(useSize>0){
        cout<<"use siez"<<useSize<<endl;
        useSize--;
        rear=front;
        for(int i=0;i<useSize-1;i++){
            cout<<"i = "<<i<<endl;
            rear=rear->nodeN;            
        }
        cout<<rear->node<<endl;
        
    }else
        empError();
}



#endif	/* LINKEDLIST_H */





