/* 
 * File:   sortedlink.h
 * Author: Administrator
 *
 * Created on 2015年10月7日, 下午8:35
 */

#ifndef SORTEDLINK_H
#define	SORTEDLINK_H

template<class T>
class Sortedlink {
private:

    struct Node {
        T data;
        Node* next;

        Node(T a = 0, Node*p = 0) :
        data(a), next(p) {
        }
    };
    int linkSize;
    Node* front;
    Node* rear;
    Node* worker;
public:
    Sortedlink();
    Sortedlink(int);
    ~Sortedlink();
    void Sort();

    int size() {
        return linkSize;
    }
    void append(T);
    void prepend();
    T &operator[](const int&);


};

template<class T>
Sortedlink<T>::Sortedlink() {
    front = worker = rear = 0;
    linkSize = 0;
}

template<class T>
Sortedlink<T>::Sortedlink(int len) {
    front = rear = worker = new Node();
    linkSize = 1;
    while (len > 1) {
        rear->next = new Node();
        rear = rear->next;
        len--;
        linkSize++;
    }
}

template<class T>
Sortedlink<T>::~Sortedlink() {
//    cout << "destructor" << endl;
    while (front != 0) {
        worker = front;
        front = front->next;
        delete worker;
    }
}

template<class T>
T & Sortedlink<T>::operator[](const int &sub) {//【】参数必须是const
    //    cout<<sub<<endl;
    if (sub < 0 || sub >= linkSize)
        cout << "out of range" << endl;
    else {
        worker = front;
        int num = sub;
        while (num > 0) { //by looping to find the point;
            //注意下标+1才是对应的数
            worker = worker->next;
            num--;
        }
        return worker->data;
    }
}

template<class T>
void Sortedlink<T>::append(T t) {
    if (front == 0) {
        front = rear = new Node(t);
        linkSize++;
    } else {
        rear->next = new Node(t);
        rear = rear->next;
        linkSize++;
    }
}

template<class T>
void Sortedlink<T>::prepend() {
    if (linkSize == 0)
        cout << "empty" << endl;
    else if (linkSize == 1) {
        delete rear;
        linkSize--;
    } else {
        worker = front;
        while (worker->next->next != 0) {
            worker = worker->next;
        }
        delete rear;
        rear = worker;
        linkSize--;
    }
}

template<class T>
void Sortedlink<T>::Sort() {
    if (linkSize == 0)
        cout << "empty" << endl;
    else if (linkSize == 1) {
    } else {
//        cout<<"size is "<<linkSize<<endl;
        Node* pos = new Node();//add a node at the begin of the link
        pos->next = front;
        front = pos;
        rear->next=new Node(11111);//add a node with big enough data 
        //at the end of the link
        Node* temp;        
        Node* indexSmall=front;
        worker = front->next;
        int len=linkSize;
//        linkSize+=2;
//                 for(int i=0;i<linkSize;i++){
//              cout<<operator[](i)<<" ";}
        while (len > 0) {
            for (; worker->next != 0;) {
                if (indexSmall->next->data > worker->next->data) {
                    indexSmall= worker;
                }
                worker = worker->next;
            }
            
            temp = indexSmall->next->next;
            indexSmall->next->next = front;
            front = indexSmall->next;
            indexSmall->next = temp;
            len--;
            worker = pos->next;
            indexSmall = pos;
//            cout<<endl;
//            cout<<"len is "<<len<<endl;
//          for(int i=0;i<linkSize;i++){
//              cout<<operator[](i)<<" ";
//          } 
        }rear=front;
        for(int i=0;i<linkSize-1;i++){
          rear=rear->next;  
        }
        delete pos->next;//delete the added node
        delete pos;
        rear->next=0;//rear->next should assign back to 0;
    }
}
//    worker = front;
//    Node* smallest = front;
//    Node* index = front;
//    cout<<"size is "<<linkSize<<endl;
//    for (int i = 0; i < linkSize; i++) {
//        for (int j = i; j < linkSize; j++) {
////            cout<<"here"<<endl;
//            if (worker->next != 0 && smallest->data > worker->next->data) {
//                smallest = worker->next;
//            }
//            worker = worker->next;
//        }
//        if(smallest->data!=front->data){
//        while (index->data != smallest->data) {
//            index = index->next;
//        }
//        index->next = smallest->next;
//        smallest->next = front;
//        front = smallest;
//        int count = i;
//        worker = front;
//        smallest = index = front;
//        while (count >= 0) {
//            worker = worker->next;
//            smallest = smallest->next;
//            count--;
//        }
//        }else{
//            worker=worker->next;
//            smallest=smallest->next;
//            index=front;
//        }
//    }
//}

#endif	/* SORTEDLINK_H */

