/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年10月7日, 上午11:26
 */

#include <cstdlib>
#include "stackandqueue.h"
#include "list.h"
#include "doublelinked.h"
#include "circlelink.h"
#include "prioritylink.h"
#include "priorityqueue.h"
#include "sortedlink.h"
#include "sortedlink.h"

using namespace std;
template<class T>
void print(T&);

int main(int argc, char** argv) {
    srand(time(0));
    /*test sort linke's function sort();
     */
    cout<<"rest sortedlink"<<endl;
    Sortedlink<int>sl(10);
    for (int i = 0; i < sl.size(); i++) {
        sl[i] = rand() % 10;
    }
    print(sl);
    sl.Sort();
    print(sl);

    /*test circle link
     */
    
    cout<<endl<<"test circlelink"<<endl;
    Circlelink<int> cl;
    int n = 10;
    while (n) {
        cl.append(n);
        n--;
    }
    print(cl);
    for (int i = 0; i < 15; i++)//range 15> size 10
        cout << cl[i] << " ";

    /*test double pointer list
     */
    cout<<endl<<endl<<"test doublepointer list"<<endl;
    Doublelink<int> dl(10);
    for (int i = 0; i < dl.size(); i++) {
        dl[i] = rand() % 10;
    }
     print(dl);
    cout<<dl.rear->pre->node;
    
    /*prioritylink test
     */
    cout<<endl<<endl<<"test prioritylink"<<endl;
    Prioritylink<int>pl;
    n=10;
    while(n>0){
        pl.append(rand()%10);
        n--;
    }
    cout<<endl<<"test priority"<<endl;
    print(pl);
    pl.find(1);
    print(pl);
    cout<<endl<<"test append and prepend"<<endl;
    pl.append(33);    
    print(pl);
    pl.prepend();
    print(pl);
    
    /*test priority queue
     */
    cout<<endl<<endl<<"test priority queue"<<endl;
    Priorityqueue<int>pq;
     n=10;
    while(n>0){
        pq.append(rand()%10);
        n--;
    }
     print(pq);
     pq.append(15);
     print(pq);
  pq.prepend();
    print(pq);
    
    /*test stack
     */
    cout<<endl<<endl<<"test stack"<<endl;
    Stack<int> s(10);
    for (int i = 0; i < s.size(); i++) {
        s[i] = rand() % 10;
    }
    print(s);
    s.append(20);
    print(s);
    s.prepend();
    print(s);
    
    /*test queue
     */
    cout<<endl<<endl<<"test queue"<<endl;
    Queue<int> q(10);
        for (int i = 0; i < q.size(); i++) {
        q[i] = rand() % 10;
    }
    print(q);
    q.append(20);
   print(q);
   q.prepend();
   print(q);
    
   



    return 0;
}

template<class T>
void print(T& a) {
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}



