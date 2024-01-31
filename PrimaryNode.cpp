#include "PrimaryNode.h"

/**
 * Creates a primaryNode with NULL values
 */
PrimaryNode::PrimaryNode() {
    left = NULL;
    right = NULL;
    data = "";
    secondaryTree = NULL;
    height = 1;
}

/**
 * Insertion algorithm of a node by given parameters.
 * @param part = the part of the insertion ( 1 = AVL insertion) ( 2 = LLRBT insertion)
 * @param data = string data to insert
 * @param price = string price of the node named data
 */
void PrimaryNode::insert(int part, string data, string price) {
    if( part == 1){ // AVL insertion
        secondaryTree = AVLinsertHelper(data, secondaryTree, price);
    }
    else if( part == 2){
        secondaryTree = LLRBTinsertHelper(data,secondaryTree, price);
        secondaryTree->color = 1;
    }
}

/**
 * Deletion algorithm of a node by given parameters.
 * @param part = the part of the delete ( 1 = AVL insertion) ( 2 = LLRBT insertion)
 * @param data = string data to delete
 */
void PrimaryNode::remove(int part, string data) {
    if( part == 1){ // AVL delete
        secondaryTree = AVLdeleteHelper(data, secondaryTree);
    }
    else if( part == 2){
        if(isBlack(secondaryTree->left) && isBlack(secondaryTree->right) && secondaryTree != NULL)
            secondaryTree->color = 0;
        //secondaryTree = LLRBTdeleteHelper(data,secondaryTree);
        if( secondaryTree != NULL) secondaryTree->color = 1;
    }
}

/**
 * Deletion algorithm of a node by given parameters. (recursive)
 * @param word = the string data of the node to delete.
 * @param node = pointer to the current node.
 * @return node after deletion.
 */
SecondaryNode* PrimaryNode::LLRBTdeleteHelper(string word, SecondaryNode* node){

    /*ToDo did not work
    if (node == NULL){
        return node;
    }
    if( word < node->data){
        if(isBlack(node->left) && isBlack(node->left->left))
            node = moveRedLeft(node);
        node->left = LLRBTdeleteHelper(data,node->left);
    }
    else {
        if(!isBlack(node->left))
            node = AVLrightRotate(node);
        if( word == node->data && node->right == NULL)
            return NULL;
        if( isBlack(node->right) && isBlack(node->right->left))
            node = moveRedRight(node);
        if( node->data == word){
            SecondaryNode* tmp = findMin(node->right);
            node->data = tmp->data;
            node->right = deleteMinimum(node->right);
        }
        else{
            node->right = LLRBTdeleteHelper(word, node->right);
        }
    }
    return fix(node);
    */
}

/**
 * Insertion helper algorithm of a node by given parameters. (recursive part2)
 * @param word = the string data of the node to insert.
 * @param nodePtr = current node pointer
 * @param price = string price of the node.
 * @return node after creation.
 */
SecondaryNode* PrimaryNode::LLRBTinsertHelper(string word, SecondaryNode* nodePtr, string price) {
    if( nodePtr == NULL)
        return new SecondaryNode(NULL,NULL,word,0, price);
    if( nodePtr->data < word){
        nodePtr->right = LLRBTinsertHelper(word, nodePtr->right, price);
    }
    else if( nodePtr->data > word)
        nodePtr->left = LLRBTinsertHelper(word,nodePtr->left, price);
    else
        return nodePtr;
    nodePtr->height = 1+ max(nodePtr->getHeight(nodePtr->left), nodePtr->getHeight(nodePtr->right));
    if( isBlack(nodePtr->left) && !isBlack(nodePtr->right)){ //Right is red and left is black
        nodePtr = AVLleftRotate(nodePtr);
        colorChange(nodePtr, nodePtr->left);
    }
    if( !isBlack(nodePtr->left) && !isBlack(nodePtr->left->left)){
        nodePtr = AVLrightRotate(nodePtr);
        colorChange(nodePtr, nodePtr->right);
    }
    if(!isBlack(nodePtr->left) && !isBlack(nodePtr->right)){ //Left and right is red
        int control = nodePtr->color;
        if( control == 1)
            nodePtr->color = 0;
        else if( control == 0)
            nodePtr->color = 1;
        nodePtr->left->color = 1;
        nodePtr->right->color = 1;
    }
    return nodePtr;
}

/**
 * Swaps the colors of the given nodes:
 * @param first = first node
 * @param second = second node
 */
void PrimaryNode::colorChange(SecondaryNode* first, SecondaryNode* second) {
    int tmp = first->color;
    first->color = second->color;
    second->color = tmp;
}

/**
 * Gets the color information of the given node
 * @param nodePtr = node pointer
 * @return 1 if it is black( or null) 0 if it is red.
 */
bool PrimaryNode::isBlack(SecondaryNode* nodePtr) {
    if( nodePtr == NULL)
        return true;
    return (nodePtr->color == 1);
}

/**
 * Insertion helper algorithm of a node by given parameters. (recursive part1)
 * @param word = the string data of the node to insert.
 * @param nodePtr = current node pointer
 * @param price = string price of the node.
 * @return node after creation.
 */
SecondaryNode* PrimaryNode::AVLinsertHelper(string word, SecondaryNode* nodePtr, string price) {
    if(nodePtr == NULL){
        SecondaryNode* temp = new SecondaryNode(NULL,NULL,word, -1, price);
        return temp;
    }

    if( nodePtr->data < word ){
        nodePtr->right = AVLinsertHelper(word,nodePtr->right, price);
    }
    else if( nodePtr->data > word){
        nodePtr->left = AVLinsertHelper(word,nodePtr->left, price); //Assuming there won't be any same words.
    }
    else{
        return nodePtr; //Data is the same did not insert anything
    }

    nodePtr->height = 1+ max(nodePtr->getHeight(nodePtr->left), nodePtr->getHeight(nodePtr->right));
    int balance = nodePtr->getHeight(nodePtr->left) - nodePtr->getHeight(nodePtr->right);
    if( balance > 1){
        if( nodePtr->left->data > word){
            return AVLrightRotate(nodePtr);
        }
        else{
            nodePtr->left = AVLleftRotate(nodePtr->left);
            return AVLrightRotate(nodePtr);
        }
    }
    else if( balance < -1){
        if( nodePtr->right->data < word){
            return AVLleftRotate(nodePtr);
        }
        else{
            nodePtr->right = AVLrightRotate(nodePtr->right);
            return AVLleftRotate(nodePtr);
        }
    }

    return nodePtr;
}

/**
 * Deletion helper algorithm of a node by given parameters. (recursive part1)
 * @param data = the string data of the node to delete.
 * @param node = current node pointer
 * @return node after deletion.
 */
SecondaryNode* PrimaryNode::AVLdeleteHelper(string data, SecondaryNode * node) {
    if( node == NULL){
        return node;
    }
    if( node->data > data)
        node->left = AVLdeleteHelper(data, node->left);
    else if( node->data < data)
        node->right = AVLdeleteHelper(data,node->right);
    else{
        if( node->left == NULL || node->right == NULL){
            SecondaryNode* tmp = node->left ? node->left : node->right;
            if( tmp == NULL){ //Both children are null
                tmp = node;
                node = NULL;
            }
            else //There is only one child
                *node = *tmp;
            free(tmp);
        }
        else{ //Left and right both exists.
            SecondaryNode* tmp = getLeftMostLeaf(node->right);
            node->data = tmp->data;
            node->right = AVLdeleteHelper(node->data,node->right);
        }
    }

    if( node == NULL)
        return node;
    node->height = 1 + max(node->getHeight(node->left), node->getHeight(node->right));
    int bal = node->getHeight(node->left) - node->getHeight(node->right);

    if( bal > 1 && node->getBalance(node->left) >= 0){
        return AVLrightRotate(node);
    }
    else if( bal > 1 && node->getBalance(node->left) < 0 ){
        node->left = AVLleftRotate(node->left);
        return AVLrightRotate(node);
    }
    else if( bal < -1 && node->getBalance(node->right) <= 0){
        return AVLleftRotate(node);
    }
    else if( bal < -1 && node->getBalance(node->right) > 0){
        node->right = AVLrightRotate(node->right);
        return AVLleftRotate(node);
    }

    return node;
}

/**
 * Rotation algorithm of a node by given parameters.
 * @param nodePtr = current node pointer to rotate
 * @return node after rotation.
 */
SecondaryNode* PrimaryNode::AVLrightRotate(SecondaryNode*& nodePtr){
    SecondaryNode* newNode = nodePtr->left;
    nodePtr->left = newNode->right;
    newNode->right = nodePtr;
    newNode->height = 1 + max(newNode->getHeight(newNode->left), newNode->getHeight(newNode->left));
    nodePtr->height = 1 + max(newNode->getHeight(nodePtr->right), newNode->getHeight(nodePtr->left));
    return newNode;
}

/**
 * Rotation algorithm of a node by given parameters.
 * @param nodePtr = current node pointer to rotate
 * @return node after rotation.
 */
SecondaryNode* PrimaryNode::AVLleftRotate(SecondaryNode*& nodePtr){
    SecondaryNode* newNode = nodePtr->right;
    nodePtr->right = newNode->left;
    newNode->left = nodePtr;
    newNode->height = 1 + max(newNode->getHeight(newNode->left), newNode->getHeight(newNode->left));
    nodePtr->height = 1 + max(newNode->getHeight(nodePtr->right), newNode->getHeight(nodePtr->left));
    return newNode;
}

/**
 * Search algorithm of a node by given parameters.
 * @param word = data of the node to be found.
 * @return node after search.
 */
SecondaryNode* PrimaryNode::find(string word){
    if( secondaryTree == NULL){
        return NULL;
    }
    else{
        SecondaryNode* curr = secondaryTree;
        for(; curr != NULL;){
            if( curr->data == word){
                return curr;
            }
            else if( curr->data < word){
                curr = curr->right;
            }
            else if( curr->data > word){
                curr = curr->left;
            }
        }
    }
    return NULL;
}

/**
 * Prints the level if it is the turn of that level (recursively checks)
 * @param count = control variable of the level
 * @param nodePtr = pointer to the current node
 * @param out = fstream to write the data
 */
void PrimaryNode::printLevel(int count, PrimaryNode* nodePtr, fstream& out) {
    if (nodePtr == NULL)
        return;
    if (count == 1){
        out << "\n\"" << nodePtr->data << "\":";
        if( nodePtr->secondaryTree == NULL)
            out << "{}";
        else{
            nodePtr->secondaryTree->printLevelByLevel(nodePtr->secondaryTree,out);
        }
    }
    else if( count > 1){
        printLevel(count-1,nodePtr->left, out);
        printLevel(count-1,nodePtr->right, out);
    }
}

/**
 * Prints the level if it is the turn of that level
 * @param outputFile = fstream to write the data to.
 * @param nodePtr = pointer to the current node
 */
void PrimaryNode::printLevelByLevel(PrimaryNode* nodePtr, fstream &outputFile) {
    int i = getHeight(nodePtr);
    for(int j = 1; j <= i; j++){
        printLevel(j,nodePtr,outputFile);
    }
}

/**
 * Prints the level if it is the turn of that level (recursively checks)
 * @param nodePtr = pointer to the current node
 * @return nodePtr = pointer to the leftMost node
 */
SecondaryNode* PrimaryNode::getLeftMostLeaf(SecondaryNode* nodePtr){
    SecondaryNode* tmp = nodePtr;
    for(; tmp->left != NULL; tmp = tmp->left){}
    return tmp;
}

