//
// Created by fuchs on 9/27/2023.
//
#include <iostream>
#include <vector>
#include <string>
#pragma once
using namespace std;

class AVLTree{
    struct Node{
        string name = "";
        string id = "";
        int height = 1;
        Node* left = nullptr;
        Node* right = nullptr;
        Node();
        Node(string name, string id);
        ~Node();
    };

    Node* root = nullptr;

    Node* insertNAMEID(AVLTree::Node* root, string name, string id);
    void updateHeight(Node* root);
    string checkRotate(Node* root);
    int getBalanceFactor(Node* root);
    Node* balanceTree(Node* root);
    Node* rotateLeft(Node* root);
    Node* rotateRight(Node* root);
    Node* rotateLeftRight(Node* root);
    Node* rotateRightLeft(Node* root);
    void printInorder(Node* root);
    vector<string> makeInOrderNodeVect(Node* root, vector<string> &vect);
    void printPreorder(Node* root);
    vector<string> makePreOrderNodeVect(Node* root, vector<string> &vect);
    void printPostorder(Node* root);
    vector<string> makePostOrderNodeVect(Node* root, vector<string> &vect);
    vector<Node*> makeVectorOfNodes(Node* root, vector<Node*> &vect);
    void deleteCases(Node* root);
    Node* findInOrderSuccessor(Node* root);
    Node* findInorderNode(int num, Node* root);
    void copyNode(Node* lhs, Node* rhs, Node* parent, bool needRightPtr);
    bool checkChars(string name, string id);
    bool checkIDLength(string id);
    bool checkIDUnique(string id);
    Node* findID(string id, Node* root);
    Node* findLeafParent(Node* deleteNode, Node* root);
    void findNAME(string name, Node* root, vector<string> &vect);
    int getLevelCount();
    void addComma(Node* currNode);

public: // accessors

    AVLTree();
    ~AVLTree();

    bool checkValid(string name, string id);
    string insert(string name, string id);
    string removeID(string id);
    string searchID(string id);
    string searchNAME(string name);
    void printIn();
    void printPre();
    void printPost();
    vector<string> printAsVector(string order);
    int printLevelCount();
    string removeInorderN(int num);

};

























