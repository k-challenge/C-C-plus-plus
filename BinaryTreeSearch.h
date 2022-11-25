#ifndef INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H
#define INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H
#include <iostream>
#include <string>
template <class datatype>
class STree {
public:

    class Node {
    public:

        Node *left, *right;
        datatype data;

        Node(datatype data) : data(data), left(nullptr), right(nullptr) {}
    };
private:

    Node *root;
    size_t numLeaf;

public:

    STree() : root(nullptr), numLeaf(0) {}

private:

    void push(Node *&brws, datatype data) {
        if (brws == nullptr)
            brws = new Node(data);

        else if (data < brws->data)
            push(brws->left, data);

        else if (data > brws->data)
            push(brws->right, data);
    }

    void outNLR(Node *brws) const {
        if (brws == nullptr) return;
        std::cout << brws->data << " ";

        outNLR(brws->left);
        outNLR(brws->right);
    }

    void outLNR(Node *brws) const {
        if (brws == nullptr) return;

        outLNR(brws->left);
        std::cout << brws->data << " ";
        outLNR(brws->right);
    }

    void outLRN(Node *brws) const {
        if (brws == nullptr) return;

        outLRN(brws->left);
        outLRN(brws->right);
        std::cout << brws->data << " ";
    }

    void outLevel(int level, Node *brws) {

        if (brws == nullptr) return;

        if (level == 0)
            std::cout << brws->data << " ";

        outLevel(level-1, brws->left);
        outLevel(level-1, brws->right);
    }

public:

    void push(datatype data) {
        push(root, data);
        ++numLeaf;
    }

    void outNLR() {
        outNLR(root);
    }

    void outLNR() {
        outLNR(root);
    }

    void outLRN() {
        outLRN(root);
    }

    Node* _root() const{
        return this->root;
    }


    void outLevel(int level) {
        outLevel(level, root);
    }
};

#endif //INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H
