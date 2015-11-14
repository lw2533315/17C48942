/* 
 * File:   main.cpp
 * Author: Administrator
 *
 * Created on 1515年10月11日, 下午8:35
 */

#include <bits/stdc++.h>
#include "board.h"

using namespace std;
ChessBoard<int>* easy(int, int, int);
ChessBoard<int>* medium(int, int, int);
ChessBoard<int>* hard(int, int, int);
void quickSort(vector<pair<string, int> >&, int, int);

/*
 * 
 */
int main(int argc, char** argv) {
    cout << "Minesweeper" << endl;
    cout << "1. Easy  (8*8, 10)" << endl;
    cout << "2. Normal  (16*16, 40)" << endl;
    cout << "3. Hard  (30*16, 99)" << endl;
    bool more = true;
    int input;
    int x = 0; //row
    int y; //column
    int opt; //flag or not;
    ifstream ifs;
    vector<pair<string, int> >v; //temply store the data from file
    vector<pair<string, int> >::iterator iter;
    set<int>s;
    map<string, int> m;
    while (more) {
        cout << "enter your choice (1-4)" << endl;

        if (cin >> input) {
            if (input > 0 && input < 5) {
                more = false;
            } else cout << "input is out range" << endl;
        } else {
            cout << "wrong input" << endl;
            cin.clear();
            cin.ignore(1024, '\n');
        }
    }
    ChessBoard<int>* p;
    switch (input) {
        case 1: p = easy(8, 8, 10);
            break;
        case 2: p = medium(16, 16, 40);
            break;
        case 3: p = hard(16, 30, 99);
            break;
        default: break;
    }
    string tempS;
    int temp;
    //add STL set to the code by requirement
    if (input == 1) {
        ifs.open("easy.txt");
    } else if (input == 2) {
        ifs.open("normal.txt");
    } else {
        ifs.open("hard.txt");
    }
    try {
        if (ifs) {
            while (!ifs.eof()) {
                ifs>>tempS;
                ifs>>temp;
                s.insert(temp);
                //                    v.push_back(make_pair(tempS, temp));
            }
        } else throw "file missed";
    } catch (const char* e) {
        cout << e << endl;
    }
    set<int>::iterator itrS;
    itrS=s.begin();
    cout <<"The best record is "<<*itrS<<"s"<<endl;
    itrS=s.end();
    itrS--;
    cout<<"The worst record in the table is "<<*itrS<<"s"<<endl;    
            ifs.close();

    p->show();
    //    string tempS;
    //    int temp;
    getline(cin, tempS);
    //loop realize the process of sweeping
    int timeBegin, timeEnd; //recorder the time;
    while (p->winOrLoose() == 0) {
        do {
            more = false;
            cout << endl << "input the row(number) and column(character), then follow by _1 or 2,"
                    "1 is non-mine place , 2 is estimated mine flag"
                    "example (2B-2), put a mine flag at row 2,column B" << endl;
            string inputS;
            getline(cin, inputS);
            int temp = inputS.find('-');
            int digit = 0;
            x = y = opt = 0;
            int mutipl;
            if (inputS.length() != 4 && inputS.length() != 5) {
                more = true;
            } else if (inputS[2] != '-' && inputS[3] != '-') {
                cout << "wrong input" << endl;
                more = true;
            } else {
                if (inputS[temp + 1] == '1' ||
                        inputS[temp + 1] == '2') {
                    opt = inputS[temp + 1] - 48;
                } else {
                    more = true;
                }
                for (int i = 0; i < temp; i++) {
                    if (inputS[i] > 57 || inputS[i] < 48) {//is not 0-9
                        mutipl = 1;

                        for (int j = i - 1; j >= 0; j--) {
                            digit++;
                            if (inputS[j] >= 48 && inputS[j] <= 57) {//0-9 char-int
                                //                                cout << "inputS[j[+48 is " << inputS[j] - 48 << endl;
                                x = x + (inputS[j] - 48) * mutipl;
                                //                                cout << "x in process is " << x << endl;
                                mutipl *= 10;
                            } else {//out of 0-9
                                more = true;
                            }
                        }
                        //                        cout << "final x is " << x << endl;
                        if (x < 1 || x > p->rowR()) {//out of 1-row
                            //                            cout<<"final x is "<<x<<endl;
                            more = true;
                            //                            cout << 3 << endl;
                        }
                    }
                }
                for (int i = digit; i < temp; i++) {
                    char tempC = toupper(inputS[i]);
                    if (tempC < 65 || tempC > 90 || (tempC - 64) > p->colR()) {
                        //                        cout << "wrong place and the value is " << tempC << endl;

                        more = true;
                    } else {
                        y = tempC - 64;
                    }
                }
                if (more == true) {
                    //                    cout << "wrong input" << endl;
                }
            }
        } while (more);

        //        cout << "x is " << x << " : y is " << y << endl;
        if (opt == 2) {
            p->print();
            p->edit2D(x, y);
            //            cout << "test" << endl;
            p->show();
        } else {
            //               p->print();
            p->click(x, y);
            //                    p->print();
            p->show();
        }
    }
    timeBegin = p->beginTime();
    timeEnd = time(0);
    cout << endl;
    cout << "You spent " << timeEnd - timeBegin << "s" << endl;
    int times = timeEnd - timeBegin;

    if (p->winOrLoose() == 1) {
        cout << "Congratuation! You win" << endl;
        if (input == 1) {
            ifs.open("easy.txt");
        } else if (input == 2) {
            ifs.open("normal.txt");
        } else {
            ifs.open("hard.txt");
        }
        try {
            if (ifs) {
                while (!ifs.eof()) {
                    ifs>>tempS;
                    ifs>>temp;
                    v.push_back(make_pair(tempS, temp));
                }
            } else throw "file missed";
        } catch (const char* e) {
            cout << e << endl;
        }
        ifs.close();
        bool firstTen = false;
        for (int i = 0; i < v.size(); i++) {
            if (times < v[i].second) {//find the time allocation in the vector
                cout << "You are the " << i + 1 << "rd" << endl;
                cout << "please input your name" << endl;
                cin>>tempS;
                firstTen = true; //in first 10 rd
                v.push_back(make_pair(tempS, times));
                break;
            }
        }
        if (firstTen) {
            quickSort(v, 0, v.size() - 1);
            cout << right << setw(17) << "Sheet" << endl;
            cout << setw(10) << left << "Name" << right << setw(15) << "Time" << endl;
            for (int i = 0; i < v.size() && i < 10; i++) {//only the first ten name and time need to be print out
                cout << left << setw(10) << v[i].first << setw(15) << right << v[i].second << endl;
            }
            ofstream ofs; //after insert new data, the sheet in the file need to be edited
            if (input == 1) {
                ofs.open("easy.txt");
            } else if (input == 2) {
                ofs.open("normal.txt");
            } else {
                ofs.open("hard.txt");
            }
            for (int i = 0; i < v.size() - 1 && i < 9; i++) {//only save the first 10 score;
                ofs << v[i].first << endl;
                ofs << v[i].second << endl;
            }
            ofs << v[9].first << endl << v[9].second;
            ofs.close();
        } else {//mot insert any data to vector, so do not need edit the file
            cout << right << setw(17) << "Hero Sheet" << endl;
            cout << setw(10) << left << "Name" << right << setw(15) << "Time" << endl;

            for (iter = v.begin(); iter != v.end(); iter++) {
                cout << left << setw(10) << iter->first << setw(15) << right << iter->second << endl;
            }
        }
    }
    if (p->winOrLoose() == -1) {
        cout << "You loose" << endl;
        if (input == 1) {
            ifs.open("easy.txt");
        } else if (input == 2) {
            ifs.open("normal.txt");
        } else {
            ifs.open("hard.txt");
        }
        try {
            if (ifs) {
                while (!ifs.eof()) {
                    ifs>>tempS;
                    ifs>>temp;
                    v.push_back(make_pair(tempS, temp));
                    m.insert(pair<string,int>(tempS,temp));
                }
            } else throw "file missed";
        } catch (const char* e) {
            cout << e << endl;
        }
        ifs.close();
        cout << right << setw(17) << "Hero Sheet by Time" << endl;
        cout << setw(10) << left << "Name" << right << setw(15) << "Time(s)" << endl;
        for (iter = v.begin(); iter != v.end(); iter++) {
            cout << left << setw(10) << iter->first << setw(15) << right << iter->second << endl;
        }
          cout << right << setw(17) << "Hero Sheet by Name" << endl;
          map<string ,int>::iterator itrM;
        cout << setw(10) << left << "Name" << right << setw(15) << "Time(s)" << endl;
        for (itrM = m.begin(); itrM != m.end(); itrM++) {
            cout << left << setw(10) << itrM->first << setw(15) << right << itrM->second << endl;
        }
    }
    return 0;
}

ChessBoard<int>* easy(int x, int y, int z) {
    ChessBoard<int> *cb = new ChessBoard<int>(x, y, z);
    return cb;
}

ChessBoard<int>* medium(int x, int y, int z) {
    ChessBoard<int> *cb = new ChessBoard<int>(x, y, z);
    return cb;
}

ChessBoard<int>* hard(int x, int y, int z) {
    ChessBoard<int>* cb = new ChessBoard<int>(x, y, z);
    return cb;
}

void quickSort(vector<pair<string, int> >&v, int l, int r) {
    if (l < r) {
        int i = l;
        int j = r;
        vector<pair<string, int> >temp(1);
        temp[0] = v[l];
        while (i < j) {
            while (i < j && v[j].second >= temp[0].second) {
                j--;
            }
            if (i < j) {
                v[i++] = v[j];
            }
            while (i < j && v[i].second < temp[0].second) {
                i++;
            }
            if (i < j) {
                v[j--] = v[i];
            }
        }
        v[i] = temp[0];
        quickSort(v, 0, i - 1);
        quickSort(v, i + 1, r);
    }
}
