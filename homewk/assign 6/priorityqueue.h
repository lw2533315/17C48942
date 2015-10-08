/* 
 * File:   priorityqueue.h
 * Author: Administrator
 *
 * Created on 2015年10月7日, 下午7:51
 */

#ifndef PRIORITYQUEUE_H
#define	PRIORITYQUEUE_H

#include "prioritylink.h"

template<class T>
class Priorityqueue: public Prioritylink<T>{
    public:
        ~Priorityqueue(){};
        void prepend();
};
template<class T>
void Priorityqueue<T>::prepend(){
    if (Prioritylink<T>::listSize>1){
       Prioritylink<T>:: temp=Prioritylink<T>::front;
        Prioritylink<T>::front=Prioritylink<T>::front->nNext;
        delete Prioritylink<T>::temp;
        Prioritylink<T>::listSize--;
    }else if(Prioritylink<T>::listSize>0){
        delete Prioritylink<T>::front;
        Prioritylink<T>::front=Prioritylink<T>::rear=0;
    }else{
        cout<<"empty";
    }
};


#endif	/* PRIORITYQUEUE_H */

