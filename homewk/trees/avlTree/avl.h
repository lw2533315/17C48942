/* 
 * File:   avl.h
 * Author: Administrator
 *
 * Created on 2015年12月1日, 下午2:11
 */

#ifndef AVL_H
#define	AVL_H


#include <iomanip>
#include <iostream>
#include<algorithm>
using namespace std;

template<class T>
struct Node {
    Node<T>*left;
    Node<T>*right;
    int height;
    T val;

    Node(T t = 0, Node<T>*l = 0, Node<T>*r = 0, int h = 0) : val(t), left(l), right(r), height(h) {
    }
};

template<class T>
class Avl {
private:
    void llRotate(Node<T>* &);
    void rrRotate(Node<T>* &);
    void lrRotate(Node<T>* &);
    void rlRotate(Node<T>* &);
    void insert(Node<T>* &, T);
    Node<T>* root;
    Node<T>* search(Node<T>*tree, T data);
    Node<T>* findMin();
    Node<T>*findMax();
    void remove(Node<T>* &tree, T data);
    void makeEmpty(Node<T>*); //删除所有节点
    void inOrder(Node<T>*);
    void preOrder(Node<T>*);
    void postOrder(Node<T>*);

public:
    bool isEmpty();
    void inOrder();
    void preOrder();
    void postOrder();
    Node<T>*findMin(Node<T>*tree);
    Node<T>*findMax(Node<T>*tree);
    Node<T>* search(T data);
    bool contain(T data);
    void insert(T);
    void remove(T data);

    Avl() {
        root = 0;
    };
    ~Avl();
    int height(Node<T>*);
};

template<class T>
void Avl<T>::makeEmpty(Node<T>* tree) {
    if (tree != NULL) {
        makeEmpty(tree->left);
        makeEmpty(tree->right);
        delete tree;
    }
    tree = NULL;
}

template<class T>
bool Avl<T>::isEmpty() {
    if (root == NULL)
        return true;
    else
        return false;
}

template<class T>
Avl<T>::~Avl() {
    makeEmpty(root);
}

/*remove element from treee
 */
template<class T>
void Avl<T>::remove(T data) {
    remove(root, data);
}

template<class T>
void Avl<T>::remove(Node<T>* &tree, T data) {
    if (NULL == tree) {
        return;
    } else if (data < tree->val) {
        remove(tree->left, data);
        if (height(tree->right) - height(tree->left) == 2) {
            Node<T>*r = tree->right;
            if (height(r->left) > height(r->right))
                rlRotate(tree);
            else
                rrRotate(tree);
        }
    } else if (data > tree->val) {
        remove(tree->right, data);
        if (height(tree->left) - height(tree->right) == 2) {
            Node<T>* l = tree->left;
            if (height(l->right) > height(l->left))
                lrRotate(tree);
            else
                llRotate(tree);
        }
    } else {
        if (tree->left != NULL && tree->right != NULL) {//节点有两个子树
            if (height(tree->left) > height(tree->right)) {
                //如果左边高于右边，取左边最大值赋给tree
                tree->val = findMax(tree->left)->val;
                T max=tree->val;//此处把用来替换data的末梢的值抓出来，用递归在下一行
                //代码中作为remove()的参数删除
                //删除此最大值
                remove(tree->left, max);
            } else {
                //左边低于右边，取右边最小值
                tree->val = findMin(tree->right)->val;
                T min=tree->val;
                remove(tree->right, min);
            }
        } else {
            Node<T>*temp = tree;
            tree = (tree->left != NULL) ? tree->left : tree->right;
            delete temp;
        }
    }
    //    root = tree;
}

/*find max element in the tree
 */
template<class T>
Node<T>*Avl<T>::findMax() {
    return findMax(root);
}

template<class T>
Node<T>* Avl<T>::findMax(Node<T>* tree) {
    if (NULL == tree)
        return NULL;
    else if (NULL == tree->right)
        return tree;
    else
        return findMax(tree->right);
}

/*find min element in the tree
 */
template <class T>
Node<T>* Avl<T>::findMin() {
    return findMin(root);
}

template<class T>
Node<T>* Avl<T>::findMin(Node<T>*tree) {
    if (NULL == tree)
        return NULL;
    else if (NULL == tree->left)
        return tree;
    else
        return findMin(tree->left);
}

/*  查找树中是否有某个元素
 */
template<class T>
bool Avl<T>::contain(T data) {
    if (NULL == search(root, data))
        return false;
    else
        return true;
}

/*  search a value in the tree and return the pointer,if do not
 * found it, return NULL
 */
template<class T>
Node<T>* Avl<T>::search(T val) {
    return search(root, val);
}

template<class T>
Node<T>* Avl<T>::search(Node<T>*tree, T data) {
    if (NULL == tree) {
        return NULL;
    } else if (data < tree->left) {
        return search(tree->left, data);
    } else if (data > tree->right) {
        return search(tree->right, data);
    } else
        return tree;
}

template<class T>
void Avl<T>::insert(T data) {
    insert(root, data);
}

template<class T>
void Avl<T>::insert(Node<T> * &tree, T key) {
    if (tree == 0) {
        tree = new Node<T>(key);
    } else if (key < tree->val) {
        insert(tree->left, key); //查入节点当
        //tree->left=0 的时候生成新节点并且地址赋给tree->left
        if (height(tree->left) - height(tree->right) == 2) {
            if (key < tree->left->val)
                llRotate(tree);
            else
                lrRotate(tree);
        }
    } else if (key > tree->val) {
        insert(tree->right, key);
        if (height(tree->right) - height(tree->left) == 2) {
            if (key > tree->right->val) {
                rrRotate(tree);
            } else
                rlRotate(tree);
        }
    } else {
        cout << "can not insert same key Node" << endl;
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;
}

template<class T>
int Avl<T>::height(Node<T>* tree) {
    if (tree != 0)
        return tree->height;
    else
        return 0;
}

template<class T>
void Avl<T>::llRotate(Node<T>* &tree) {
    Node<T>*temp;
    temp = tree->left;
    tree->left = temp->right;
    temp->right = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    tree = temp;
}

template<class T>
void Avl<T>::rrRotate(Node<T>* &tree) {
    Node<T> * temp;
    temp = tree->right;
    tree->right = temp->left;
    temp->left = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    tree = temp;
}

template<class T>
void Avl<T>::lrRotate(Node<T>* &tree) {
    rrRotate(tree->left);
    llRotate(tree);
}

template<class T>
void Avl<T>::rlRotate(Node<T>*&tree) {
    llRotate(tree->right);
    rrRotate(tree);
}
template<class T>
void Avl<T>::preOrder(){
    preOrder(root);
}
template<class T>
void Avl<T>::preOrder(Node<T>*tree){
    if(tree!=0){
        cout<<tree->val<<" ";
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template<class T>
void Avl<T>::postOrder(){
    postOrder(root);
}

template<class T>
void Avl<T>::postOrder(Node<T>* tree){
    if(tree!=NULL){
    postOrder(tree->left);
    postOrder(tree->right);
    cout<<tree->val<<" ";
    }
}
template<class T>
void Avl<T>::inOrder() {
    inOrder(root);
}

template<class T>
void Avl<T>::inOrder(Node<T>* tree) {
    if (tree != NULL) {
        inOrder(tree->left);
        cout << tree->val << " ";
        inOrder(tree->right);
    }
}


#endif	/* AVL_H */

