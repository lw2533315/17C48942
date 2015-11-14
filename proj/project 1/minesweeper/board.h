/* 
 * File:   newfile.h
 * Author: Administrator
 *
 * Created on 2015年9月30日, 下午7:33
 */

#ifndef NEWFILE_H
#define	NEWFILE_H
#include <cstdlib>
#include<iomanip>
#include<iostream>
using namespace std;

/*   -1 means mine, 0 means blank 
 */
template<class T>
class ChessBoard {
private:

    struct Node {//background board
        T val;
        Node* down;
        Node* right;
        Node* up;
        Node* left;

        Node(const T& c = 0, Node*p = 0, Node*p1 = 0,
                Node*p2 = 0, Node*p3 = 0) : val(c), down(p),
        right(p1), left(p2), up(p3) {
        }
    };
    Node* head;
    Node* rear;
    Node* curr;
    bool firstStep;
    int noMines; //非雷数
    int mines;
    int boardSize;
    int row;
    int col;
    int timeBegin;
    int win; //1 为赢，-1 为输
    char**p; //player board
public:
    ChessBoard(const int&, const int&, const int&);
    ~ChessBoard();
    void fillMine(int); //fill mines
    void fillNumber(); //fill numbers
    int &operator[](const int&);
    void click(int x, int y);
    void open(Node*, int x, int y); //recuision
    void print(); //display the real board
    void show(); //display the board player can see
    void build(); //build fake board with '?'
     void clearBoard() ;//clear the board
     inline int beginTime(){
         return timeBegin;
    }

    inline void edit2D(int x, int y) {
        p[x - 1][y - 1] = '*';
    }

    inline int winOrLoose() {
        return win;
    } //return win or lose;

    inline int rowR() {
        return row;
    }

    inline int colR() {
        return col;
    }
};

template<class T>
ChessBoard<T>::ChessBoard(const int& row, const int& col, const int&n) { //skip list
    srand(time(0));
    Node * p[col]; // pointer point to upper row ,
    noMines = 0; //the place player walk and the sametime no mines
    firstStep = true; //the first step,control open
    boardSize = row*col;
    mines = n;
    win = 0;
    timeBegin=0;
    this->row = row;
    this->col = col;
    p[0] = head = rear = new Node();
    for (int i = 1; i < boardSize; i++) {
        rear->right = new Node();
        rear->right->left = rear;
        rear = rear->right;
        if (i >= col) {//using the pointer to connected with the upper row node 
            //begin to connected up and down points from the seconde row 
            p[i % col]->down = rear;
            p[i % col]->down->up = p[i % col];
        }
        p[i % col] = rear; //update the point to the rear point
    }
    /*cut off the right side double pointer;
     */
    curr = head;

    for (int i = 1; i < boardSize; i++) {
        Node*temp;
        if (i % col == 0) {
            temp = curr->right;
            curr->right->left = 0;
            curr->right = 0;
            curr = temp;
        } else
            curr = curr->right;
    }
    build();
    fillMine(mines);
    fillNumber();

}



/*clear the board
 */
template<class T>
void ChessBoard<T>::clearBoard(){
        Node*temp = curr = head;
        for (int j = 0; j < row; j++) {
            for (int i = 0; i < col; i++) {
                curr->val = 0;
                curr = curr->right;
            }
            curr = temp->down;
            temp=curr;
        }
    }


//return the char on the val of the chessboard

template<class T>
int &ChessBoard<T>::operator[](const int&n) {
    curr = head;
    int r = n / col;
    while (r > 0) {
        curr = curr->down;
        r--;
    }
    int c = n % col;
    while (c > 0) {
        curr = curr->right;
        c--;
    }
    return curr->val;
}

template<class T>
void ChessBoard<T>::build() {
    p = new char*[row];
    for (int i = 0; i < row; i++) {
        p[i] = new char[col];
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            p[i][j] = '?';
        }
    }
}
//fill mine to chessboard

template<class T>
void ChessBoard<T>::fillMine(int n) {
    int x;
    int y;
    for (int i = 0; i < n; i++) {
        do {
            x = rand() % row;
            y = rand() % col;
        } while (operator[](x * col + y) == -1);
        operator[](x * col + y) = -1;
    }
}

template<class T>
void ChessBoard<T>::fillNumber() {
    int count;
    Node*temp = head;
    curr = head;
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            count = 0;
            if (curr->val != -1) {//节点判断
                if (curr->up != 0) {//up;
                    curr->up->val == -1 ? count++ : count += 0;
                    if (curr->up->left != 0) {//up-left
                        curr->up->left->val == -1 ? count++ : count += 0;
                    }
                    if (curr->up->right != 0) {//up-right
                        curr->up->right->val == -1 ? count++ : count += 0;
                    }
                }
                if (curr->down != 0) {//down
                    curr->down->val == -1 ? count++ : count += 0;
                    if (curr->down->left != 0) {//down-left
                        curr->down->left->val == -1 ? count++ : count += 0;
                    }
                    if (curr->down->right != 0) {//down-right
                        curr->down->right->val == -1 ? count++ : count += 0;
                    }
                }
                if (curr->left != 0) {//left
                    curr->left->val == -1 ? count++ : count += 0;
                }
                if (curr->right != 0) {//right
                    curr->right->val == -1 ? count++ : count += 0;
                }
                curr->val = count;
                curr = curr->right;
            } else curr = curr->right;
        }
        curr = temp->down; //right edge point has cut off, so depend on down pointer
        temp = curr;
    }
}

template<class T>
ChessBoard<T>::~ChessBoard() {
    Node*temp = head->down;
    int r = row;
    while (r > 1) {//can not be 0,because temp will point to a invalid allocation
        while (head != 0) {
            curr = head;
            head = head->right;
            delete curr;
        }
        head = temp;
        temp = head->down;
        r--;
    }
    while (head != 0) {
        curr = head;
        head = head->right;
        delete curr;
    }
    for (int i = 0; i < row; i++) {
        delete []p[i];
    }
    delete [] p;
}
/*  '/' mean in the recursion the place had been passed and no number there before
 */
template<class T>
void ChessBoard<T>::open(Node* now, int x, int y) {//recurseion for zero mine allocation open
    //    cout<<"noMines is "<<noMines<<endl;
    
    curr = now;
    Node*temp = now;
    if (curr->up != 0) {
        if (curr->up->val != 0) {
            if (p[x - 1][y] != curr->up->val + 48) {
                p[x - 1][y] = curr->up->val + 48;
                noMines++;
            }
        } else {
            if (p[x - 1][y] != '/') {
                p[x - 1][y] = '/';
                noMines++;
                open(curr->up, x - 1, y);
                curr = temp;
            }
        }
        if (curr->up != 0 && curr->up->left != 0) {
            if (curr->up->left->val != 0) {
                if (p[x - 1][y - 1] != curr->up->left->val + 48) {
                    p[x - 1][y - 1] = curr->up->left->val + 48;
                    noMines++;
                }
            } else {
                if (p[x - 1][y - 1] != '/') {
                    p[x - 1][y - 1] = '/';
                    noMines++;
                    open(curr->up->left, x - 1, y - 1);
                    curr = temp;
                }
            }
        }
        if (curr->up != 0 && curr->up->right != 0) {
            if (curr->up->right->val != 0) {
                if (p[x - 1][y + 1] != curr->up->right->val + 48) {
                    p[x - 1][y + 1] = curr->up->right->val + 48;
                    noMines++;
                }
            } else {
                if (p[x - 1][y + 1] != '/') {
                    p[x - 1][y + 1] = '/';
                    noMines++;
                    open(curr->up->right, x - 1, y + 1);
                    curr = temp;
                }
            }
        }
    }
    if (curr->left != 0) {
        if (curr->left->val != 0) {
            if (p[x ][y - 1] != curr->left->val + 48) {
                p[x ][y - 1] = curr->left->val + 48;
                noMines++;
            }
        } else {
            if (p[x ][y - 1] != '/') {
                p[x ][y - 1] = '/';
                noMines++;
                open(curr->left, x, y - 1);
                curr = temp;
            }
        }
    }
    if (curr->right != 0) {
        if (curr->right->val != 0) {
            if (p[x][y + 1] != curr->right->val + 48) {
                p[x][y + 1] = curr->right->val + 48;
                noMines++;
            }
        } else {
            if (p[x ][y + 1] != '/') {
                p[x ][y + 1] = '/';
                noMines++;
                open(curr->right, x, y + 1);
                curr = temp;
            }
        }
    }
    if (curr->down != 0) {
        if (curr->down->val != 0) {
            if (p[x + 1][y ] != curr->down->val + 48) {
                p[x + 1][y ] = curr->down->val + 48;
                noMines++;
            }
        } else {
            if (p[x + 1][y] != '/') {
                p[x + 1][y] = '/';
                noMines++;
                open(curr->down, x + 1, y);
                curr = temp;
            }
        }
        if (curr->down != 0 && curr->down->left != 0) {
            if (curr->down->left->val != 0) {
                if (p[x + 1][y - 1] != curr->down->left->val + 48) {
                    p[x + 1][y - 1] = curr->down->left->val + 48;
                    noMines++;
                }
            } else {
                if (p[x + 1][y - 1] != '/') {
                    p[x + 1][y - 1] = '/';
                    noMines++;
                    open(curr->down->left, x + 1, y - 1);
                    curr = temp;
                }
            }
        }
        if (curr->down != 0 && curr->down->right != 0) {
            if (curr->down->right->val != 0) {
                if (p[x + 1][y + 1] != curr->down->right->val + 48) {
                    p[x + 1][y + 1] = curr->down->right->val + 48;
                    noMines++;
                }
            } else {
                if (p[x + 1][y + 1] != '/') {
                    p[x + 1][y + 1] = '/';
                    noMines++;
                    open(curr->down->right, x + 1, y + 1);
                    curr = temp;
                }
            }
        }
    }
}

template<class T>
void ChessBoard<T>::click(int x, int y) {
    cout << endl;
    curr = head;
    int x_temp = x;
    int y_temp = y;
    while (x > 1) {
        curr = curr->down;
        x--;
    }
    while (y > 1) {
        curr = curr->right;
        y--;
    }
    while (firstStep && curr->val != 0) {//if the first step is not empty,rand()mines again)
        Node*temp=curr;
        clearBoard();//before refill mines, clear all the numbers of the board first
//        cout<<"mines number is "<<mines<<endl;
        fillMine(mines);
        fillNumber();
        curr=temp;
        timeBegin=time(0);
//        cout<<"after is "<<curr->val<<endl;
    }
    if (curr->val == -1) {
        p[x_temp - 1][y_temp - 1] = 'M';
        win = -1;
        //下一步需要考虑递归中开出的不是雷的格子数目
    } else if (curr->val == 0) {//
        timeBegin=time(0);
        p[x_temp - 1][y_temp - 1] = '/';
        noMines++;
        open(curr, x_temp - 1, y_temp - 1);
    } else {
        p[x_temp - 1][y_temp - 1] = curr->val + 48;
        noMines++;
    }

    if (noMines == row * col - mines) {
        win = 1;
    }

    //    cout<<"noMinse number is "<<noMines<<endl;
    firstStep = false;
}

template<class T>
void ChessBoard<T>::show() {
    cout << endl;
    cout << "  ";
    for (int k = 0; k < col; k++) {
        cout << right << setw(3) << char(k + 65);
    }
    cout << endl;
    for (int k = 0; k < 3 * col + 3; k++) {
        cout << "_";
    }
    cout << endl;
    for (int i = 0; i < row; i++) {
        cout << right << setw(2) << i + 1 << "|";
        for (int j = 0; j < col; j++) {
            if (p[i][j] == '/')
                p[i][j] = ' ';
            cout << right << setw(2) << p[i][j] << "|";
        }
        cout << left << setw(2) << i + 1;
        cout << endl;
    }
    for (int k = 0; k < 3 * col + 3; k++) {
        cout << "-";
    }
    cout << endl;
    cout << "  ";
    for (int k = 0; k < col; k++) {
        cout << right << setw(3) << char(k + 65);
    }
}

template<class T>
void ChessBoard<T>::print() {
    for (int k = 0; k < 3 * col; k++) {
        cout << "_";
    }
    for (int i = 0; i < boardSize; i++) {
        if (i % col == 0) {
            cout << endl << "|";
        }
        cout << setw(2) << operator[](i) << "|";
    }
    cout << endl;
    for (int k = 0; k < 3 * col; k++) {
        cout << "-";
    }
}
#endif	/* NEWFILE_H */

