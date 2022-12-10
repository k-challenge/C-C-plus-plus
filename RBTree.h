#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H
#include <iostream>
#include <string>
#include<iomanip>
#define COUNT 10
template <class datatype>
class RBTree {
public:

    class Node{
    public:

        Node *left, *right, *parent;
        bool color;
        datatype data;

        Node(datatype data) : data(data), left(nullptr), parent(nullptr), right(nullptr), color(1) {}
    };

    Node *root;
    bool _case[5];

public:

    RBTree() : root(nullptr) {}

private:

    Node *rotateRight(Node *rooted) {
        Node *x = rooted->left;
        rooted->left = x->right;
        if(x->right != nullptr)
            x->right->parent = rooted;

        x->right = rooted;
        rooted->parent = x;
        return x;
    }

    Node *rotateLeft(Node *rooted) {
        Node *x = rooted->right;
        rooted->right = x->left;
        if(x->left != nullptr)
            x->left->parent = rooted;

        x->left = rooted;
        rooted->parent = x;
        return x;
    }
// case[0]: conflict red - red
// case[1]: lef lef
// case[2]: right right
// case[3]: left right
// case[4]: right left
    Node *push(Node *rooted, const datatype key) {
        _case[0] = false; // reset case[0]: conflict red red -> false;
        if (rooted == nullptr) return new Node(key);
        else if (key < rooted->data) {
            rooted->left = push(rooted->left, key);
            rooted->left->parent = rooted;
            if (root != rooted) {
                if (rooted->color == rooted->left->color == 1)
                    _case[0] = true;
            }
        } else {
            rooted->right = push(rooted->right, key);
            rooted->right->parent = rooted;
            if (root != rooted) {
                if (rooted->color == rooted->right->color == 1)
                    _case[0] = true;
            }
        }

        if (_case[1]) {
            rooted = rotateRight(rooted);
            rooted->color = 0;
            rooted->right->color = 1;
            _case[1] = false;
        } else if (_case[2]) {
            rooted = rotateLeft(rooted);
            rooted->color = 0;
            rooted->left->color = 1;
            _case[2] = false;
        } else if(_case[3]) {
            rooted->left = rotateLeft(rooted->left);
            rooted->left->parent = rooted;
            rooted = rotateRight(rooted);
            rooted->color = 0;
            rooted->right->color = 1;
            _case[3] = false;
        } else if(_case[4]) {
            rooted->right = rotateRight(rooted->right);
            rooted->right->parent = rooted;
            rooted = rotateLeft(rooted);
            rooted->color = 0;
            rooted->right->color = 1;
            _case[4] = false;
        }

        if(_case[0]) {
            if(rooted->parent->right == rooted) {
                if (rooted->parent->left == nullptr || rooted->parent->left->color == 0) {
                    if (rooted->left != nullptr && rooted->left->color == 1)
                        _case[4] = true;
                    if (rooted->right != nullptr && rooted->right->color == 1)
                        _case[2] = true;
                } else {
                    rooted->color = rooted->parent->left->color = 0;
                    if (rooted != root)
                        rooted->parent->color = 1;
                }
            } else {
                if(rooted->parent->right == nullptr || rooted->parent->right->color == 0) {
                    if(rooted->left != nullptr && rooted->left->color ==1)
                        _case[1] = true;
                    if(rooted->right != nullptr && rooted->right->color ==1)
                        _case[3] = true;
                } else {
                    rooted->color == rooted->parent->right->color == 1;
                    if(rooted != root)
                        rooted->parent->color = 1;
                }
            }
            _case[0] = false;
        }

        return rooted;
    }

    void print2DUtil(Node* root, int space) {
        if (root == NULL)
            return;
        space += COUNT;
        print2DUtil(root->right, space);
        std::cout << std::endl;
        for (int i = COUNT; i < space; i++)
            std::cout << " ";
        std::cout << root->data << " " << "\n";
        print2DUtil(root->left, space);
    }

public:

    void push(const datatype key) {
        root = push(root, key);
        if (root->color)
            root->color = 0;
    }

    void print() {
        print2DUtil(root,0);
    }
};
#endif //RBTREE_RBTREE_H
