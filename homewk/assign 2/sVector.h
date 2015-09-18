/* 
 * File:   sVector.h
 * Author: Administrator
 *
 * Created on 2015年9月16日, 下午7:33
 */

#ifndef SVECTOR_H
#define	SVECTOR_H
#include <iostream>
#include <new>       // Needed for bad_alloc exception
#include <cstdlib>   // Needed for the exit function
using namespace std;

template <class T>
class SimpleVector {
private:
    T *aptr; // To point to the allocated array
    int useSize;
    int arraySize; // Number of elements in the array
    void memError(); // Handles memory allocation errors
    void subError(); // Handles subscripts out of range

public:
    // Default constructor

    SimpleVector() {
//        cout << "constructor";
        aptr = 0;
        arraySize = 0;
        useSize = 0;
    }

    // Constructor declaration
    SimpleVector(int);

    // Copy constructor declaration
    SimpleVector(const SimpleVector &);

    // Destructor declaration
    ~SimpleVector();

    // Accessor to return the array size

    int size() const {
        return useSize;
    }
    void pop_back();
    void push_back(T);
    int check();
    // Accessor to return a specific element
    T getElementAt(int position);

    // Overloaded [] operator declaration
    T &operator[](const int &);
};

//***********************************************************
// Constructor for SimpleVector class. Sets the size of the *
// array and allocates memory for it.                       *
//***********************************************************

template <class T>
SimpleVector<T>::SimpleVector(int s) {
    arraySize = s;
    useSize = s;
    // Allocate memory for the array.
    try {
        aptr = new T [s];
    } catch (bad_alloc) {
        memError();
    }

    // Initialize the array.
    for (int count = 0; count < arraySize; count++)
        *(aptr + count) = 0;
}

//*******************************************
// Copy Constructor for SimpleVector class. *
//*******************************************

template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj) {
    // Copy the array size.
    arraySize = obj.arraySize;

    // Allocate memory for the array.
    aptr = new T [arraySize];
    if (aptr == 0)
        memError();

    // Copy the elements of obj's array.
    for (int count = 0; count < useSize; count++)
        *(aptr + count) = *(obj.aptr + count);
}

//**************************************
// Destructor for SimpleVector class.  *
//**************************************

template <class T>
SimpleVector<T>::~SimpleVector() {
    if (arraySize > 0)
        delete [] aptr;
    if (arraySize == 0)
        delete aptr;
}

//*******************************************************
// memError function. Displays an error message and     *
// terminates the program when memory allocation fails. *
//*******************************************************

template <class T>
void SimpleVector<T>::memError() {
    cout << "ERROR:Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//***********************************************************
// subError function. Displays an error message and         *
// terminates the program when a subscript is out of range. *
//***********************************************************

template <class T>
void SimpleVector<T>::subError() {
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//*******************************************************
// getElementAt function. The argument is a subscript.  *
// This function returns the value stored at the sub-   *
// cript in the array.                                  *
//*******************************************************

template <class T>
T SimpleVector<T>::getElementAt(int sub) {
    if (sub < 0 || sub >= useSize)
        subError();
    return aptr[sub];
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************

template <class T>
T &SimpleVector<T>::operator[](const int &sub) {
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub];
}

template<typename T>
void SimpleVector<T>::push_back(T t) {
    if (useSize >= arraySize) {
        if (arraySize > 0) {
            T*p = new T[arraySize * 2];
            for (int i = 0; i < arraySize; i++)
                p[i] = aptr[i];
            delete [] aptr;
            aptr = p;
            arraySize *= 2;
            aptr[useSize++] = t;
        } else { //for the default constructor data set
            T*p = new T[1];
            delete aptr;
            aptr = p;
            arraySize = 1;
            useSize = 1;
            aptr[useSize - 1] = t;
        }
    } else {
        aptr[useSize++] = t;
    }
}

template<class T>
int SimpleVector<T>::check() {
    return arraySize;
}

template <typename T>
void SimpleVector<T>::pop_back() {
    if (useSize > 0) {
        useSize--;
    } else {
        cout << "vector is empty";
    }
}

#endif	/* SVECTOR_H */

