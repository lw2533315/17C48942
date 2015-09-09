/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年9月3日, 上午10:16
 */

/*
 * Dr Mark E. Lehr
 * Sept 2nd, 2015
 * Purpose:  Tranigular Matrix
 * Hmwk:  Create a templated Class implmented the Matrix
*/

//System Libraries

#include"d2array.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
using namespace std;




//Execution Begins Here
int main(){
//    srand(time(0));
    Array <int> triangle(10);
    triangle.fillArray();
    triangle.prnt1Ary();
    triangle.prnt2Ary();
       
    return 0;
}




