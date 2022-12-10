#ifndef INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H
#define INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H
#include <iostream>
#include <string>
template <class datatype>
class STree {
public:

    class Node {
    public:

        Node* left, * right;
        datatype data;

        Node(datatype data) : data(data), left(nullptr), right(nullptr) {}
    };
private:

    Node* root;
    size_t numLeaf;

public:

    STree() : root(nullptr), numLeaf(0) {}

private:

    void push(Node*& brws, datatype data) {
        if (brws == nullptr)
            brws = new Node(data);

        else if (data < brws->data)
            push(brws->left, data);

        else if (data > brws->data)
            push(brws->right, data);
        else return;
    }

    Node* minValueNode(Node* brws) {
        Node* current = brws;
        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    Node* deleteNode(datatype key, Node* brws) {
        if (brws == nullptr) return brws;

        if (brws->data < key)
            brws->right = deleteNode(key, brws->right);
        else if (brws->data > key)
            brws->left = deleteNode(key, brws->left);
        else {
            if (brws->left == nullptr) {
                Node* temp = brws->right;
                free(brws);
                return temp;
            }
            else if (brws->right == nullptr) {
                Node* temp = brws->left;
                free(brws);
                return temp;
            }

            Node* temp = minValueNode(brws->right);
            brws->data = temp->data;
            brws->right = deleteNode(temp->data, brws->right);
        }

        return brws;
    }

    void outNLR(Node* brws) const {
        if (brws == nullptr) return;
        std::cout << brws->data << " ";

        outNLR(brws->left);
        outNLR(brws->right);
    }

    void outLNR(Node* brws) const {
        if (brws == nullptr) return;

        outLNR(brws->left);
        std::cout << brws->data << " ";
        outLNR(brws->right);
    }

    void outLRN(Node* brws) const {
        if (brws == nullptr) return;

        outLRN(brws->left);
        outLRN(brws->right);
        std::cout << brws->data << " ";
    }

    void outLevel(int level, Node* brws) {

        if (brws == nullptr) return;

        if (level == 0)
            std::cout << brws->data << " ";

        outLevel(level - 1, brws->left);
        outLevel(level - 1, brws->right);
    }

    int height(Node* brws) {
        if (brws == nullptr)
            return 0;
        int a = height(brws->left);
        int b = height(brws->right);
        return a > b ? a + 1 : b + 1;
    }

public:

    void push(datatype data) {
        push(root, data);
        ++numLeaf;
    }

    void deleteNode(datatype key) {
       root = deleteNode(key, root);
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

    Node* _root() const {
        return this->root;
    }

    int height() {
        return height(root);
    }

    void outLevel(int level) {
        outLevel(level, root);
    }
};

#endif //INC_24___HUYNH_TAN_KIET___BINARYSEARCHTREE_H

