#include "SecondaryNode.h"

/**
 * Creates a secondaryNode with NULL values
 */
SecondaryNode::SecondaryNode() {
    left = NULL;
    right = NULL;
    data = "";
}

/**
 * Creates a secondaryNode with given values
 * @param l = leftNode
 * @param r = rightNde
 * @param d = data
 * @param c = color data (1 if black 0 if red)
 * @param p = price
 */
SecondaryNode::SecondaryNode(SecondaryNode* l, SecondaryNode* r, string d, int c, string p){
    left = l;
    right = r;
    data = d;
    color = c;
    height = 1;
    price = p;
}

/**
 * Prints the level if it is the turn of that level (recursively checks)
 * @param count = control variable of the level
 * @param nodePtr = pointer to the current node
 * @param isFirst = control variable prints a tab if it is a new value
 * @param out = fstream to write the data
 */
void SecondaryNode::printLevel(int count, SecondaryNode* nodePtr, int& isFirst, fstream& out) {
    if( nodePtr == NULL)
        return;

    if( count == 1){
        if( isFirst == 1) {
            out << "\n\t";
            isFirst++;
        }
        else
            out << ",";
        out<< "\"" << nodePtr->data << "\":\"" << nodePtr->price << "\"";
    }
    else if( count > 1){
        printLevel(count-1,nodePtr->left, isFirst, out);
        printLevel(count-1,nodePtr->right,isFirst, out);
    }
}

/**
 * Prints the level if it is the turn of that level (recursively checks)
 * @param out = fstream to write the data to.
 * @param nodePtr = pointer to the current node
 */
void SecondaryNode::printLevelByLevel(SecondaryNode* nodePtr, fstream& out) {
    int i = getHeight(nodePtr);
    for(int j = 1; j <= i; j++){
        int first = 1;
        printLevel(j,nodePtr,first,out);
    }
}

