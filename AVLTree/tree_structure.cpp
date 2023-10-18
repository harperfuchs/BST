//
// Created by fuchs on 9/27/2023.
//
#include "tree_structure.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

AVLTree::AVLTree() {
}

AVLTree::~AVLTree() {
}

void AVLTree::addComma(Node* currNode){
    // this function is adding the comma as the nodes are printed out
    if(currNode){
        cout << ", ";
    }
}

void AVLTree::updateHeight(Node* currNode) {
    // this function updates the height of a node based on the height of its children
    int heightL = 0;
    int heightR = 0;
    int newHeight = 0;
    if(currNode != nullptr){
        if (currNode->left == nullptr && currNode->right == nullptr) { // there are no children
            newHeight = 1;
            currNode->height = newHeight;
        }
        if (currNode->left != nullptr || currNode->right != nullptr) { // at least one child exits
            if (currNode->left != nullptr) { // if left child exists
                heightL = currNode->left->height;
            }
            if (currNode->right != nullptr) { // if right child exists
                heightR = currNode->right->height;
            }
            newHeight = 1 + max(heightL, heightR);
            currNode->height = newHeight; // take max of children's heights (one could be 0 if no children) and add 1
        }
    }

}

AVLTree::Node* AVLTree::insertNAMEID(AVLTree::Node *currNode, string name, string id) {
    // this funtion inserts a node given a name and an id
    if(currNode == nullptr){
        currNode = new Node(name, id);
    }
    else if(id < currNode->id){
        currNode->left = insertNAMEID(currNode->left, name, id); // use recursion to work way down the branches
    }
    else {
        currNode->right = insertNAMEID(currNode->right, name, id);
    }
    updateHeight(currNode);
    currNode = balanceTree(currNode);
    updateHeight(currNode);
    return currNode;
}

string AVLTree::insert(string name, string id) {
    // this is a public function to call the private class function
    root = insertNAMEID(root, name, id);
    cout << "successful" << endl;
    return "successful";
}

AVLTree::Node *AVLTree::findInOrderSuccessor(Node* currNode) {
    // finds the parent of the in order successor (so the pointer can be accounted for when deleting the node)
    if(currNode->left->left != nullptr){ // fond node before inorder successor
        currNode = findInOrderSuccessor(currNode->left);
    }
    return currNode;
}

void AVLTree::deleteCases(Node* currNode) {
    // deletes nodes depending on the case it matches
    Node* successor = nullptr;
    Node* successorParent = nullptr;
    Node* tempNode = nullptr;
    if(currNode == root){
        if(currNode->right != nullptr) {
            if(currNode->right->left != nullptr){
                successorParent = findInOrderSuccessor(currNode->right);
                successor = successorParent->left;
                copyNode(currNode, successor, successorParent, true);
                if(successorParent != nullptr){
                    successorParent->left = successor->right;
                }
                delete successor;
                updateHeight(successorParent);
                updateHeight(root);
            }
            else{
                successor = currNode->right;
                root->right = successor->right;
                copyNode(currNode, successor, currNode, true); // false is for not needing to preserve l and r pointers
                //currNode->left = nullptr;
                delete successor;
                updateHeight(currNode);
                updateHeight(root);
            }
        }
        else if(currNode->left != nullptr){
            root = currNode->left;
            delete currNode;
            updateHeight(root);
        }
        else if(currNode->right == nullptr && currNode->left == nullptr){
            root = nullptr;
            delete currNode;
            updateHeight(root);
        }
    }
    else {
        if (currNode->right == nullptr) { // no inorder successor so just use node before
            if (currNode->left == nullptr) { //no children
                string id = currNode->id;
                successorParent = findLeafParent(currNode, root);
                if (successorParent->right == currNode) { //successor is right child
                    successorParent->right = currNode->right;
                } else {
                    successorParent->left = currNode->left;
                }
                updateHeight(successorParent);
                updateHeight(currNode);
                delete currNode; // it has no subtrees
            } else {
                successor = currNode->left;
                copyNode(currNode, successor, successorParent,
                         false); // false is for not needing to preserve l and r pointers
                currNode->left = nullptr;
                delete successor;
                updateHeight(successorParent);
                updateHeight(currNode);
            }
        } else { // find the inorder successor and use that to replace
            if (currNode->right->left == nullptr) {
                // this means the right child has no left subtree thus the right child is the inorder successor
                successor = currNode->right;
                tempNode = currNode;
                copyNode(currNode, successor, currNode,true); // true is for needing to preserve l and r pointers
                tempNode->right = nullptr;
                updateHeight(currNode);
                delete successor;
            } else {
                successorParent = findInOrderSuccessor(currNode->right); // successor will be one to the left of sParent
                successor = successorParent->left;
                copyNode(currNode, successor, successorParent, true); // true is for needing to preserve l and r pointers
                updateHeight(successorParent);
                updateHeight(currNode);
                delete successor;
            }
            updateHeight(currNode);
        }
    }
}

void AVLTree::copyNode(Node* lhs, Node* rhs, Node* parent, bool saveSubTrees) {
    // lhs is the node being "deleted", rhs is the successor
    lhs->id = rhs->id;
    lhs->name = rhs->name;
    lhs->height = rhs->height;
    // keep lhs->right pointer intact (save its subtree)
    if(saveSubTrees){
        // the currNode needs its right and left pointer to be preserved
        if(rhs->height > 1 && rhs != lhs->right && parent != root){
            //account for the right subtree of the successor
            Node* tempRight = rhs->right;
            parent->left = tempRight;
        }
        else if(rhs->height > 1 && rhs == lhs->right){
            lhs->right = rhs->right;
        }
    }
    else if(lhs != root){ // dont need to preserve pointers
        lhs->left = rhs->left;
        lhs->right = rhs->right;
    }
}

string AVLTree::removeID(string id) {
    // public function for removing id, calls private function and determines result
    Node* tempNode = nullptr;
    tempNode = findID(id, root);
    if(tempNode == nullptr){
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    else{
        deleteCases(tempNode);
        cout << "successful" << endl;
        return "successful";
    }
}

string AVLTree::searchID(string id) {
    // private function for finding a node by id
    Node* tempNode = nullptr;
    if(root == nullptr){ // no tree
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    tempNode = findID(id, root);
    if(tempNode == nullptr){ // not in tree
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    else if(tempNode->id != id){ // in case it returns last node, but its not the node
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    else{ // fount it
        return tempNode->name;
    }
}

string AVLTree::searchNAME(string name) {
    // public function for finding a name, calls private function and determines results
    Node* tempNode = nullptr;
    vector<string> ids;
    string output;
    findNAME(name, root, ids);
    if(ids.size() == 0){ // didn't find it :(
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    else{
        for(int i = 0; i < ids.size(); i++){
            output += ids[i];
            if(ids.size() > 1){
                output += "\n";
            }
        }
    }
    return output;
}

AVLTree::Node* AVLTree::findID(string id, Node* currNode) {
    // private function for finding a node by id
    if(currNode != nullptr){ // go until reaches the end of the branch
        if(currNode->id == id){
            return currNode;
        }
        else{
            Node* tempNode = findID(id, currNode->left); // use recursion
            if(tempNode != nullptr){
                return tempNode;
            }
            else{
                Node* tempNode = findID(id, currNode->right);
                return tempNode;
            }
        }
    }
    return currNode;
}

AVLTree::Node* AVLTree::findLeafParent(Node* toDelete, Node* currNode) {
    // private function to find the parent of a node with matching id, used to find parent of Nth node or parent of a leaf node that needs to be deleted
    if(currNode == nullptr){
        return currNode;
    }
    if(currNode->left == nullptr && currNode->right == nullptr){
        return nullptr;
    }
    if(currNode->right == toDelete || currNode->left == toDelete){ // then curr is the parent
        return currNode;
    }
    if(toDelete->id < currNode->id){
        currNode = findLeafParent(toDelete, currNode->left);
        return currNode;
    }
    if(toDelete->id > currNode->id){
        currNode = findLeafParent(toDelete, currNode->right );
        return currNode;
    }
}

void AVLTree::findNAME(string name, Node* currNode, vector<string> &ids) {
    // private function to find the node by name
    if(currNode != nullptr){ // go until reaches the end of the branch
        if(currNode->name == name){ // add id to vector
            ids.push_back(currNode->id);
        }
        findNAME(name, currNode->left, ids); // use recursion
        findNAME(name, currNode->right, ids);
    }
}

void AVLTree::printInorder(Node* currNode) {
    // private function to print the nodes in order
    if(currNode != nullptr){ // go until reaches the end of the branch
        printInorder(currNode->left);
        addComma(currNode->left);
        cout << currNode->name;
        addComma(currNode->right);
        printInorder(currNode->right);
    }
}

vector<string> AVLTree::makeInOrderNodeVect(Node* currNode, vector<string> &vect) {
    // used for my test cases to check in order return value
    if(currNode != nullptr){
        makeInOrderNodeVect(currNode->left, vect);
        vect.push_back(currNode->name);
        makeInOrderNodeVect(currNode->right, vect);
    }
    return vect;
}

void AVLTree::printPreorder(Node* currNode) {
    // private function to print in preorder
    if(currNode != nullptr){ // go until it reaches the end of the branch
        cout << currNode->name;
        addComma(currNode->left);
        printPreorder(currNode->left);
        addComma(currNode->right);
        printPreorder(currNode->right);
    }
}

vector<string> AVLTree::makePreOrderNodeVect(Node* currNode, vector<string> &vect) {
    // used for my test cases to check preorder return value
    if(currNode != nullptr){
        vect.push_back(currNode->name);
        makeInOrderNodeVect(currNode->left, vect);
        makeInOrderNodeVect(currNode->right, vect);
    }
    return vect;
}

void AVLTree::printPostorder(Node* currNode) {
    // private function to print post order
    if(currNode != nullptr){ // go until it reaches the end of the branch
        printPostorder(currNode->left);
        addComma(currNode->left);
        printPostorder(currNode->right);
        addComma(currNode->right);
        cout << currNode->name;
    }

}

vector<string> AVLTree::makePostOrderNodeVect(Node* currNode, vector<string> &vect) {
    // used for my test cases to check postorder return value
    if(currNode != nullptr){
        makeInOrderNodeVect(currNode->left, vect);
        makeInOrderNodeVect(currNode->right, vect);
        vect.push_back(currNode->name);
    }
    return vect;
}

int AVLTree::getLevelCount() {
    // private function to get level count
    if(root == nullptr){
        cout << 0 << endl;
        return 0;
    }
    else{
        cout << root->height << endl;
        return root->height;
    }
}

int AVLTree::printLevelCount() {
    // public function to get level count
    return getLevelCount();
}

vector<AVLTree::Node*> AVLTree::makeVectorOfNodes(Node* currNode, vector<Node*> &vect) {
    if(currNode != nullptr){
        makeVectorOfNodes(currNode->left, vect);
        vect.push_back(currNode);
        makeVectorOfNodes(currNode->right, vect);
    }
    return vect;
}

AVLTree::Node *AVLTree::findInorderNode(int num, Node* currNode) {
    // private function to find Nth node
    vector<Node*> vectNodes;
    makeVectorOfNodes(root, vectNodes);
    if(num < vectNodes.size()){
        currNode = vectNodes.at(num);
        return currNode;
    }
    else{
        return nullptr;
    }
}

string AVLTree::removeInorderN(int num) {
    // public function for removing nth node and determining result
    int counter = 0;
    Node* currNode = findInorderNode(num, root);
    if(currNode == nullptr){
        cout << "unsuccessful" << endl;
        return "unsuccessful";
    }
    else{
        deleteCases(currNode);
        cout << "successful" << endl;
        return "successful";
    }
}

void AVLTree::printIn() {
    // public function to print
    printInorder(root);
}

void AVLTree::printPre() {
    // public function to print
    printPreorder(root);
}

void AVLTree::printPost() {
    // public function to print
    printPostorder(root);
}

string AVLTree::checkRotate(Node* currNode) {
    // private function to check if a node needs to rotate (determines flags to pass back)
    string flag = "none";
    int balanceFactorParent = getBalanceFactor(currNode);
    int balanceFactorChild = 0;
    if(balanceFactorParent == 2 || balanceFactorParent == -2){
        if(balanceFactorParent == 2){
            balanceFactorChild = getBalanceFactor(currNode->left);
            if(balanceFactorChild == 1 || balanceFactorChild == -1){
                if(balanceFactorChild == 1){ // left left case
                    flag = "right";
                }
                else{ // left right case
                    flag = "leftRight";
                }
            }
            else{
                currNode = currNode->left;
                flag = checkRotate(currNode);
            }
        }
        else{
            balanceFactorChild = getBalanceFactor(currNode->right);
            if(balanceFactorChild == 1 || balanceFactorChild == -1){
                if(balanceFactorChild == 1){ // right left case
                    flag = "rightLeft";
                }
                else{ // right right case
                    flag = "left";
                }
            }
        }
    }
    return flag;
}

AVLTree::Node* AVLTree::rotateLeft(Node* currNode) { // currNode is root of subtree
    // private function for left rotate case
    Node* looseLeaf = nullptr; // a child that may need to be reassigned
    Node* newRoot = nullptr; // of subtree
    if(currNode->right != nullptr){ // child that needs to be accounted for
        looseLeaf = currNode->right->left;
        newRoot = currNode->right;
        currNode->right = looseLeaf;
    }
    else {
        newRoot = currNode->right;
        currNode->right = nullptr;
    }
    newRoot->left = currNode;
    //cout << "rotated" << endl;
    updateHeight(currNode);
    return newRoot;
}

AVLTree::Node *AVLTree::rotateRight(Node* currNode) {
    // private function for right rotate case
    Node* looseLeaf = nullptr;
    Node* newRoot = nullptr;
    if(currNode->left != nullptr){ // there is a child that needs to be accounted for
        looseLeaf = currNode->left->right;
        newRoot = currNode->left;
        currNode->left = looseLeaf;
    }
    else {
        newRoot = currNode->left;
        currNode->left = nullptr;
    }
    newRoot->right = currNode;
    updateHeight(currNode);
    return newRoot;
}

AVLTree::Node *AVLTree::rotateLeftRight(Node* currNode) {
    // private funciton for left right rotate case
    Node* elbow = currNode->left;
    Node* newParent = currNode->left->right;
    Node* looseLeaf = currNode->left->right->left;
    //if(looseLeaf == nullptr){
    //looseLeaf = currNode->left->right->right;
    //}

    currNode->left->right = looseLeaf;
    currNode->left = newParent;
    newParent->left = elbow;
    updateHeight(looseLeaf);
    updateHeight(currNode);
    updateHeight(elbow);
    updateHeight(newParent);
    // completed left rotation
    currNode = rotateRight(currNode);
    return currNode;
}

AVLTree::Node *AVLTree::rotateRightLeft(AVLTree::Node* currNode) {
    // private function for right left rotate case
    Node* elbow = currNode->right;
    Node* newParent = currNode->right->left;
    Node* looseLeaf = currNode->right->left->right;

    currNode->right->left = looseLeaf;
    currNode->right = newParent;
    newParent->right = elbow;
    updateHeight(currNode);
    // completed rotate to the right
    currNode = rotateLeft(currNode);
    updateHeight(currNode);
    return currNode;
}

int AVLTree::getBalanceFactor(Node* currNode) {
    // private function finds balance factor of a node
    int balanceFactor = 0;
    int heightL = 0;
    int heightR = 0;
    if(currNode != nullptr){
        if (currNode->left == nullptr && currNode->right == nullptr) { // there are no children
            balanceFactor = 0;
            return balanceFactor;
        }
        if (currNode->left != nullptr || currNode->right != nullptr) { // at least one child exits
            if (currNode->left != nullptr) { // if left child exists
                heightL = currNode->left->height;
            }
            if (currNode->right != nullptr) { // if right child exists
                heightR = currNode->right->height;
            }
            balanceFactor = heightL - heightR;
            return balanceFactor;
        }
    }
    return balanceFactor;
}

AVLTree::Node* AVLTree::balanceTree(Node* currNode) {
    // if a case is flag, the tree will rotate
    string flag = checkRotate(currNode);
    if(flag != "none"){ // no rotation needed
        if(flag == "left"){ // rotate to the left (rr case)
            currNode = rotateLeft(currNode);
        }
        else if(flag == "right"){ // rotate to the right (ll case)
            currNode = rotateRight(currNode);
        }
        else if(flag == "leftRight"){ // rotate to the left then right (lr case)
            currNode = rotateLeftRight(currNode);
        }
        else if(flag == "rightLeft"){ // rotate to the right then left (rl case)
            currNode = rotateRightLeft(currNode);
        }
        updateHeight(currNode);
    }
    return currNode;
}

bool AVLTree::checkChars(string name, string id) {
    // private function confirms name is valid
    bool isValid = false;
    for(int i = 0; i < name.length(); i++){
        if((name.at(i) >= 65 && name.at(i) < 91) || (name.at(i) >= 97 && name.at(i) < 123) || (name.at(i) == 32)){
            isValid = true;
        }
        else{
            return isValid = false;
        }
    }
    for(int i = 0; i < id.length(); i++){
        if(id.at(i) >= 48 && id.at(i) < 58){
            isValid = true;
        }
        else{
            return isValid = false;
        }
    }
    return isValid;
}

bool AVLTree::checkIDLength(string id) {
    // private function confirms valid id length
    if(id.size() == 8){
        return true;
    }
    return false;
}

bool AVLTree::checkIDUnique(string id) {
    // private function confirms unique
    Node* comparisonID = findID(id, root);
    if(comparisonID == nullptr){
        return true;
    }
    return false;
}

vector<string> AVLTree::printAsVector(string order) {
    // public function for my test cases
    vector<string> vectNodes;
    if(order == "in"){
        makeInOrderNodeVect(root, vectNodes);
    }
    else if(order == "pre"){
        makePreOrderNodeVect(root, vectNodes);
    }
    else if(order == "post"){
        makePostOrderNodeVect(root, vectNodes);
    }
    else{
        cout << "incorrect input" << endl;
    }
    return vectNodes;
}

bool AVLTree::checkValid(string name, string id) {
    bool isValidName = false;
    bool isValidIDLength = false;
    bool isValidIDUnique = false;
    isValidName = checkChars(name, id);
    isValidIDLength = checkIDLength(id);
    isValidIDUnique = checkIDUnique(id);
    if(isValidName && isValidIDLength && isValidIDUnique){ // valid node data
        return true;
    }
    else{
        return false;
    }
}


AVLTree::Node::Node(string name, string id) {
    this -> name = name;
    this -> id = id;
    height = 0;
}

AVLTree::Node::~Node() {

}


