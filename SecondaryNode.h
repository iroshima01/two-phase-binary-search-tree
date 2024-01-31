#ifndef BM4_SECONDARYNODE_H
#define BM4_SECONDARYNODE_H
#include "iostream"
#include "sstream"
#include "fstream"
using namespace std;

class SecondaryNode {
public:
    SecondaryNode* left;
    SecondaryNode* right;
    string data;
    int color;
    string price;
    SecondaryNode();
    SecondaryNode(SecondaryNode*, SecondaryNode*, string, int, string);
    int height;
    int getHeight(SecondaryNode* curr){
        if( curr == NULL)
            return 0;
        return curr->height;
    }
    int getBalance(SecondaryNode* curr){
        if( curr == NULL)
            return 0;
        return getHeight(curr->left) - getHeight(curr->right);
    }
    void printLevel(int ,SecondaryNode*, int&, fstream&);
    void printLevelByLevel(SecondaryNode*, fstream&);
};


#endif //BM4_SECONDARYNODE_H
