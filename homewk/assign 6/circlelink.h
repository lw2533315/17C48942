/* 
 * File:   circlelink.h
 * Author: Administrator
 *
 * Created on 2015年10月7日, 下午3:59
 */

#ifndef CIRCLELINK_H
#define	CIRCLELINK_H
template<class T>
class Circlelink{
protected:

    struct Node {
        T node;
        Node *nodeN;
        Node(const T&a = 0, Node*p = 0) : node(a), nodeN(p)
       {
        }
    };
    //protected:
//    Node* pre;
    Node * front;
    Node* rear;
    int listSize;
    //    int useSize;
    //    void memError();
    void subError();
    void empError();
public:
    Circlelink();
    Circlelink(int);
    Circlelink(Circlelink &object);
    ~Circlelink();
    //    Node* begin();

    int size() const {
        return listSize;
    }
    void append(T);
    void prepend();
    //    T getData(n);
    T getFirst();
    T getLast();
  
    T &operator[](const int&);
};

template <typename T>
Circlelink<T>::Circlelink() {
    front = rear = 0;
    listSize = 0;
}

template <typename T>
Circlelink<T>::Circlelink(int n) {
    front = rear = 0;
    listSize = 0;
    if (n >= 1) {
        front = rear = new Node();
        rear->nodeN=front;

        listSize = 1;
        while (n > 1) {
            rear->nodeN = new Node();
            rear = rear->nodeN;
            rear->nodeN=front;
            n--;
            listSize++;
        }
    }
}

template<typename T>
Circlelink<T>::Circlelink(Circlelink& object) {
    this->listSize = object.listSize;
    if (listSize == 0) {
        Circlelink();
    } else {
        //        cout<<"test1"<<"len is " <<len<<endl;
        rear = front = new Node();
        front->node = object[0];
        //          cout<<"test2"<<" object[0] is "<<object[0]<<endl;
        for (int i = 1; i < listSize; i++) {
            rear->nodeN = new Node(object[i]);
            rear = rear->nodeN;
            rear->nodeN = front;

        }
    }
}

template<typename T>
T & Circlelink<T>::operator[](const int &sub) {//【】参数必须是const
    //    cout<<sub<<endl;
    if (sub < 0 )
        subError();
    else {
        Node *temp = front;
        int num = sub%listSize;//circle list, 求模
        while (num > 0) { //by looping to find the point;
            //注意下标+1才是对应的数
            temp = temp->nodeN;
            num--;
        }
        return temp->node;
    }
}

template <class T>
void Circlelink<T>::subError() {
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

template <class T>
void Circlelink<T>::empError() {
    cout << "ERROR: out of range\n";
    exit(EXIT_FAILURE);
}

template <typename T>
Circlelink<T>::~Circlelink() {//delete front the front  
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
void Circlelink<T>::append(T t) {
    if (front != 0) {
        rear->nodeN = new Node(t);
        rear = rear->nodeN;
        rear->nodeN=front;
        listSize++;

    } else {
        front = new Node(t);
        rear = front;
        listSize++;

    }
}

template <typename T>
void Circlelink<T>::prepend() {
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
T Circlelink<T>::getFirst() {
    if (front == 0)
        empError();
    else
        return front->node;
}

template<typename T>
T Circlelink<T>::getLast() {
    if (front == 0)
        empError();
    else
        return rear->node;
}




#endif	/* CIRCLELINK_H */

