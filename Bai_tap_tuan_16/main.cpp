//Nguyen Kim Linh
//20233495
//               ..╱ | 、 ♡
//                (˚ˎ 。7      ⋆
//                | 、˜〵
//                じしˍ, )ノ

#include <iostream>
#include<vector>
#include<string>
using namespace std;

#define TVALUE int

struct Node {
    TVALUE info;
    Node* left;
    Node* right;
    int height;

    Node(TVALUE info) : info(info), left(NULL), right(NULL), height(1) {}

};

struct AVLTree {
    Node* root; 

    AVLTree() : root(NULL) {}

    int getHeight(Node* node) {
        return node == NULL ? 0 : node->height;
    }

    int getBalance(Node* node) {
        return node == NULL ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;

        x->right = y;
        y->left = temp;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;

        y->left = x;
        x->right = temp;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node* insert(Node* node, TVALUE info) {
        if (node == NULL)
            return new Node(info);

        if (info < node->info)
            node->left = insert(node->left, info);
        else if (info > node->info)
            node->right = insert(node->right, info);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && info < node->left->info)
            return rotateRight(node);
        if (balance < -1 && info > node->right->info)
            return rotateLeft(node);
        if (balance > 1 && info > node->left->info) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && info < node->right->info) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->info << " ";
            inorder(root->right);
        }
    }

    void insert(TVALUE info) {
        root = insert(root, info);
    }

    void printTree() {
        inorder(root);
        cout << endl;
    }
};
int main()
{
    AVLTree tree;

    int arr[] = { 10, 20, 30, 40, 50, 25 };
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        tree.insert(arr[i]);
    }

    tree.printTree();
    return 0;
}

