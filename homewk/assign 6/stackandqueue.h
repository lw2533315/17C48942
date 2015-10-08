/* 
 * File:   stackandqueue.h
 * Author: Administrator
 *
 * Created on 2015年10月7日, 上午11:28
 */

#ifndef STACKANDQUEUE_H
#define	STACKANDQUEUE_H

#include "list.h"

template<class T>
class Stack : public SimpleV<T> {
public:

    Stack() : SimpleV<T>() {
    }

    Stack(int a) : SimpleV<T>(a) {
    }

    Stack(Stack&object) : SimpleV<T>(object) {
    }

    ~Stack() {
    }
    //    void append(T);

};

template<class T>
class Queue : public SimpleV<T> {
public:

    Queue() : SimpleV<T>() {
    }

    Queue(int a) : SimpleV<T>(a) {
    }

    Queue(Queue&object) : SimpleV<T>(object) {
    }

    ~Queue() {
    }

    void prepend();
};

template<class T>
void Queue<T>::prepend() {
    if (SimpleV<T>::front == 0) {
        SimpleV<T>::empError();
    } else {
        SimpleV<T>::temp = SimpleV<T>::front;
        SimpleV<T>::front = SimpleV<T>::front->nodeN;
        delete SimpleV<T>::temp;
        SimpleV<T>::listSize--;
    }

}
#endif	/* STACKANDQUEUE_H */

