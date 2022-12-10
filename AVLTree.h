// AVL tree implementation in C++
#include <iostream>
using namespace std;
template <class datatype>
class AVLTree {
public:
    class Node {
    public:
        datatype key;
        Node *left;
        Node *right;
        int height;

        Node(datatype key): key(key), left(nullptr), right(nullptr), height(1) {}
    } ;
private:
    Node* _root;

public:
    AVLTree(): _root(nullptr) {};
private:
    int max(int a, int b) {
        return (a > b) ? a : b;
    }

// Calculate height
    int height(Node *N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

// Rotate right
    Node *rightRotate(Node *y) {
        Node *x = y->left;
        y->left = x->right;
        x->right = y;
        y->height = max(height(y->left),
                        height(y->right)) +
                    1;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;
        return x;
    }

// Rotate left
    Node *leftRotate(Node *x) {
        Node *y = x->right;
        x->right = y->left;
        y->left = x;
        x->height = max(height(x->left),
                        height(x->right)) +
                    1;
        y->height = max(height(y->left),
                        height(y->right)) +
                    1;
        return y;
    }

// Get the balance factor of each node
    int getBalanceFactor(Node *N) {
        if (N == NULL)
            return 0;
        return height(N->left) -
               height(N->right);
    }

// Insert a node
    Node *insertNode(Node *node, datatype key) {
        // Find the correct postion and insert the node
        if (node == NULL)
            return new Node(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        // Update the balance factor of each node and
        // balance the tree
        node->height = 1 + max(height(node->left),
                               height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (key < node->left->key) {
                return rightRotate(node);
            } else if (key > node->left->key) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (key > node->right->key) {
                return leftRotate(node);
            } else if (key < node->right->key) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

// Node with minimum value
    Node *nodeWithMimumValue(Node *node) {
        Node *current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

// Delete a node
    Node *deleteNode(Node *root, int key) {
        // Find the node and delete it
        if (root == NULL)
            return root;
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == NULL) ||
                (root->right == NULL)) {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;
                free(temp);
            } else {
                Node *temp = nodeWithMimumValue(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right,
                                         temp->key);
            }
        }

        if (root == NULL)
            return root;

        // Update the balance factor of each node and
        // balance the tree
        root->height = 1 + max(height(root->left),
                               height(root->right));
        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) >= 0) {
                return rightRotate(root);
            } else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) <= 0) {
                return leftRotate(root);
            } else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

// Print the tree
    void printTree(Node *root, string indent, bool last) {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            } else {
                cout << "L----";
                indent += "|  ";
            }
            cout << root->key << endl;
            printTree(root->left, indent, false);
            printTree(root->right, indent, true);
        }
    }

public:
    void push(datatype key) {
        _root = insertNode(_root, key);
    }
    void print() {
        printTree(_root, "", true);
    }
    void deleteNode(int key) {
        deleteNode(_root,key);
    }
};