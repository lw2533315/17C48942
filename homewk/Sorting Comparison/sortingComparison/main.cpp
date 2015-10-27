/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on len15年10月22日, 下午3:28
 */

#include <cstdlib>
#include<iostream>
#include<vector>


using namespace std;
template<class T>
void print(vector<T>);
template<class T>
void Swap(T&, T&);
template<class T>
void bubble(vector<T>, int, int&);
template<class T>
void selection(vector<T>, int, int&);
template<class T>
void quickSort(vector<T>&, int, int, int&);
template<class T>
void assisQuick(vector<T>, int, int, int&);
template<class T>
void assisHeap(vector<T>, int, int&);
template<class T>
void heapSort(vector<T>&, int, int&);
template<class T>
void heapRebuild(vector<T>&, int, int, int&);
template<class T>
void assisMerge(vector<T>, int, int&);
template<class T>
void mrgSort(vector<T>&, int, int, int&);
template<class T>
void merge(vector<T>&, int, int, int, int&);

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(0));
    int countBub = 0, countSel = 0, countHep = 0, countMrg = 0, countQik = 0;
    vector<int>v;
    for (int i = 0; i < 100; i++) {
        v.push_back(rand()%1000);
    }
    int len = v.size();
    cout<<"100 random number sort";
    print(v);
    cout<<endl;
    bubble(v, len, countBub);
    cout << endl << "bubble operation: " << countBub << endl;
    selection(v, len, countSel);
    cout << endl << "selection operation: " << countSel << endl;
    assisQuick(v, 0, len - 1, countQik); //quickSort
    cout << endl << "quick operation: " << countQik << endl;
    //    print(v);
    assisHeap(v, len, countHep); //heap
    cout << endl << "heap operation: " << countHep << endl;
    assisMerge(v, len, countMrg); //merge
    cout << endl << "merge operation: " << countMrg << endl;
    
    cout<<endl<<"200 random number sort";
     countBub = 0; countSel = 0; countHep =0 ; countMrg =0 ; countQik = 0;
      vector<int>v1;
    for (int i = 0; i < 200; i++) {
        v1.push_back(rand()%2000);
    }
    len = v1.size();
     print(v1);
    cout<<endl;
    bubble(v1, len, countBub);
    cout << endl << "bubble operation: " << countBub << endl;
    selection(v1, len, countSel);
    cout << endl << "selection operation: " << countSel << endl;
    assisQuick(v1, 0, len - 1, countQik); //quickSort
    cout << endl << "quick operation: " << countQik << endl;
    //    print(v);
    assisHeap(v1, len, countHep); //heap
    cout << endl << "heap operation: " << countHep << endl;
    assisMerge(v1, len, countMrg); //merge
    cout << endl << "merge operation: " << countMrg << endl;

    return 0;
}

template<class T>
void assisQuick(vector<T>p, int l, int r, int&countQik) {
    quickSort(p, l, r, countQik);
    print(p);
}

template<class T>
void assisHeap(vector<T>p, int l, int&countHep) {
    heapSort(p, l, countHep);
    print(p);
}

template<class T>
void assisMerge(vector<T>p, int l, int&countMrg) {
    mrgSort(p, 0, l, countMrg);
    print(p);
}

template<class T>
void print(vector<T>v) {
    cout << endl;
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << " ";
}

template<class T>
void Swap(T& a, T &b) {
    T temp;
    temp = b;
    b = a;
    a = temp;

}

template<class T>
void mrgSort(vector<T>&a, int beg, int end, int&countMrg) {
    countMrg += 3; // assign
    int center = (beg + end) / 2;
    countMrg += 2; //if
    if ((center - beg) > 1)mrgSort(a, beg, center, countMrg);
    countMrg += 2; //if
    if ((end - center) > 1)mrgSort(a, center, end, countMrg);
    merge(a, beg, center, end, countMrg);
}

template<class T>
void merge(vector<T>&hilow, int beg, int nlow, int nhigh, int&countMrg) {
    //Create a merged array
    countMrg += 4; //assign
    int span = nhigh - beg; //Span the range to merge
    int cntl = beg, cnth = nlow; //Independent counters to merge
    vector<T>c(span); //Allocate Memory

    //Fill the array
    countMrg++; //i=0
    for (int i = 0; i < span; i++) {
        countMrg += 3; //i< and i++
        countMrg++; //if
        if (cntl == nlow) {
            countMrg += 5; //assign
            c[i] = hilow[cnth++];
        } else if (cnth == nhigh) {
            countMrg += 6; //if 
            c[i] = hilow[cntl++];
        } else if (hilow[cntl] < hilow[cnth]) {
            countMrg += 9;
            c[i] = hilow[cntl++];
        } else {
            countMrg += 9;
            c[i] = hilow[cnth++];
        }
    }
    //Copy back and deallocate memory
    countMrg++; //i=0
    for (int i = 0; i < span; i++) {
        countMrg += 7; //for loop
        hilow[beg + i] = c[i];
    }
}

template<class T>
void bubble(vector<T>p, int l, int&countBub) {
    int lowerL = l - 1;
    countBub++; //lower count;
    countBub++; //i count;    
    for (int i = 0; i < l; i++) {
        countBub += 4; //j, i<1,i++ 
        for (int j = 0; j < lowerL; j++) {
            countBub+=3; //j<lowerLj++
            countBub+=4; //if();
            if (p[j + 1] < p[j]) {
                Swap(p[j + 1], p[j]);
                countBub += 9; //swap;
            }
        }
    }
    print(p);
}

template<class T>
void selection(vector<T>p, int l, int&countSel) {
    countSel++; //i=0
    for (int i = 0; i < l; i++) {
        countSel += 4; //j=i,i<l,i++
        for (int j = i; j < l; j++) {
            countSel += 6; //j<l,j++,if
            if (p[i] > p[j]) {
                countSel += 9; //swap
                Swap(p[j], p[i]);
            }
        }
    }
    print(p);
}

template<class T>
void quickSort(vector<T>&s, int l, int r, int&countQik) {
    countQik++; //if
    if (l < r) {
        countQik += 4; //i,j,x
        int i = l, j = r;
        T x = s[l]; //参照数是s[l];
        countQik++; //while
        while (i < j) {
            countQik += 4; //while i<j
            while (i < j && s[j] >= x) // 从右向左找第一个小于x的数  
            {
                j--;
                countQik+=2; //j--
            }
            countQik++; //if
            if (i < j) //这里判断i<j,上面while循环有可能条件同时打破
            {
                s[i++] = s[j];
                countQik += 5; // assign and ++
            }
            countQik += 3; //i<j and s<x
            while (i < j && s[i] < x) // 从左向右找第一个大于等于x的数  
            {
                i++;
                countQik+=2; //i++
            }
            countQik++; //if
            if (i < j) {
                s[j--] = s[i];
                countQik += 5; //assign and j--
            }
        }
        countQik+=2; //assign
        s[i] = x;
        quickSort(s, l, i - 1, countQik);
        quickSort(s, i + 1, r, countQik);
    }
}

template<class T>
void heapSort(vector<T>& p, int size, int&countHep) {
    countHep++; //
    for (int i = size - 1; i >= 0; i--) {
        countHep += 4; //
        heapRebuild(p, i, size, countHep);
    }
    countHep+=2; //
    int last = size - 1;
    countHep++; //
    for (int i = 1; i <= size; i++, last--) {
        countHep += 5;
        
        countHep+=7;
        int temp = p[0];
        p[0] = p[last];
        p[last] = temp;
        heapRebuild(p, 0, last, countHep);
    }
}

template<class T>
void heapRebuild(vector<T>&p, int root, int size, int& countHep) {
    countHep += 4;
    int child =  root *2 + 1; //永远是左孩子的下标，而且保障从上到下比较到底
    countHep += 3; //
    if (child <= size - 1) {//下标不越界
        countHep += 2; //
        int rightChild = child + 1;
        countHep += 3;
        if (rightChild <= size - 1) {//右孩子存在
            countHep+=3;
            if (p[child] < p[rightChild]) //当右孩子>左孩，用右孩子做准备
            {
                child = rightChild;
                countHep++; //
            }
            countHep+=3;
            if (p[root] < p[child]) {//把比较大的孩子与父做比较
                countHep += 7;
                int temp = p[child];
                p[child] = p[root];
                p[root] = temp;
                heapRebuild(p, child, size, countHep);
            }
        }
    }
}
