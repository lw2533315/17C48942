/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 2015年11月25日, 下午2:37
 */

#include <cstdlib>
#include<iostream>
#include "generalhashing.h"
#include<vector>
#include<set>
#include<algorithm>
#include<map>
#include<sstream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(time(0));
    //    map<unsigned int,int>m;

    cout << "input loopTime" << endl;
    int loopTimes, num;
    cin>>loopTimes;
    num = loopTimes;
    string str;
  
    int number=0;
    for (int sN = 1; sN <= 11; sN++) {
        switch (sN) {
            case 1:
                cout << "---------RSHash" << endl;
                break;
            case 2:
                cout << "---------JSHash" << endl;
                break;
            case 3:
                cout << "---------PJWHash" << endl;
                break;
            case 4:
                cout << "---------ELFHash" << endl;
                break;
            case 5:
                cout << "---------BKDRHash" << endl;
                break;
            case 6:
                cout << "---------SDBMHash" << endl;
                break;
            case 7:
                cout << "---------DJBHash" << endl;
                break;
            case 8:
                cout << "---------DEKHash" << endl;
                break;
            case 9:
                cout << "---------BPHash" << endl;
                break;
            case 10:
                cout << "---------FNVHash" << endl;
                break;
            case 11:
                cout << "--------APHash" << endl;
                break;
            default: break;
        }
        for (int j = 1; j <= 100; j += 10) {//test
            set<unsigned int>s;
            vector<unsigned int>v;
            bool print = true;
            for (int k = 0; k < j * loopTimes; k++) {
                number += rand();
                  stringstream ss;
                ss<<number;
                ss>>str;

                switch (sN) {
                    case 1: v.push_back(RSHash(str) % num);
                        break;
                    case 2: v.push_back(JSHash(str) % num);
                        break;
                    case 3: v.push_back(PJWHash(str) % num);
                        break;
                    case 4: v.push_back(ELFHash(str) % num);
                        break;
                    case 5: v.push_back(BKDRHash(str) % num);
                        break;
                    case 6: v.push_back(SDBMHash(str) % num);
                        break;
                    case 7: v.push_back(DJBHash(str) % num);
                        break;
                    case 8: v.push_back(DEKHash(str) % num);
                        break;
                    case 9: v.push_back(BPHash(str) % num);
                        break;
                    case 10: v.push_back(FNVHash(str) % num);
                        break;
                    case 11: v.push_back(APHash(str) % num);
                        break;
                    default: break;
                }
//                cout << "size is ~~~~~~~~~~~~~~`" << v.size() << "value is " << v[v.size() - 1] << endl;
                if (!s.insert(v[v.size() - 1]).second && print) {
                    cout << ";loopTimes is " << j * loopTimes << " :" << endl;
                    cout << "the first collision took on " << v.size() << endl;
                    print = false;
                }
            }
            int collision = 0;
            int bigCollision = 0;
            sort(v.begin(), v.end());
            unsigned int strIn = v[0];
            for (int i = 1; i < v.size(); i++) {
                if (v[i] == strIn) {
                    collision++;
                } else {
                    if (bigCollision < collision) {
                        bigCollision = collision;
                    }
                    collision = 0;
                    strIn = v[i];
                }
            }
            cout << "biggist frequent collision's collides number is " << bigCollision << endl;
        }
    }
    return 0;
}

