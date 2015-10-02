/* 
 * File:   newfile.h
 * Author: Administrator
 *
 * Created on 2015年9月30日, 下午7:33
 */

#ifndef NEWFILE_H
#define	NEWFILE_H
#include <cstdlib>
using namespace std;

class ChessBoard {
private:

    struct Node {
        char pos;
        Node* down;
        Node* right;
        Node* up;
        Node* left;

        Node(const char& c = '?', Node*p = 0, Node*p1 = 0,
                Node*p2 = 0, Node*p3 = 0) : pos(c), down(p),
                right(p1), left(p2), up(p3) {}
    };
    Node* head;
    Node* rear;
    Node* curr;
    int boardSize;
    int row;
    int col;
public:
    ChessBoard(const int&, const int&);
    ~ChessBoard();
    void fillMine(int);
    char &operator[](const int&);

    char show(int index) {
        curr = head;
        for (int i = 1; i < index; i++) {
            curr = curr->right;
        }
        cout << curr->up->pos << endl;
        cout << curr->right->pos << endl;
        cout << curr->down->pos << endl;
        cout << curr->left->pos << endl;
    }

};

ChessBoard::ChessBoard(const int& row, const int& col) { //skip list
    srand(time(0));
    Node * p[col];// pointer point to upper row ,
    boardSize = row*col;
    this->row = row;
    this->col = col;
    p[0] = head = rear = new Node();
    for (int i = 1; i < row * col; i++) {
        rear->right = new Node();
        rear->right->left = rear;
        rear = rear->right;
        if (i >= col) {//using the pointer to connected with the upper row node 
            //begin to connected up and down points from the seconde row 
            p[i % col]->down = rear;
            p[i % col]->down->up = p[i % col];
        }
        p[i % col] = rear;//update the point to the rear point
    }
}
//return the char on the pos of the chessboard

char &ChessBoard::operator[](const int&n) {
    curr = head;
    for (int i = 0; i < n; i++) {               
        curr = curr->right;
    }
    return curr->pos;

}
//fill mine to chessboard

void ChessBoard::fillMine(int n) {
    int ratio = boardSize / n;
    curr = head;
    int mineLeft = n;
    int leftNode = boardSize;
    for (int i = 0; i < boardSize; i++) {
        if (mineLeft < leftNode) {//剩下的雷比剩下节点少
            if ((rand() % ratio) == 0) {
                curr->pos = 'm';
                curr = curr->right;
                n--;
                leftNode--;
            } else {
                curr->pos = ' ';
                curr = curr->right;
                leftNode--;
            }
        } else {
            curr->pos = 'm';
            curr = curr->right;
            n--;
            leftNode--;
        }
    }
}

ChessBoard::~ChessBoard() {
    while (head != 0) {
        curr = head->right;
        delete head;
        head = curr;
    }
}


#endif	/* NEWFILE_H */

