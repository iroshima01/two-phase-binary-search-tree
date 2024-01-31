#ifndef BM4_PRIMARYNODE_H
#define BM4_PRIMARYNODE_H
#include "SecondaryNode.h"

class PrimaryNode {
public:
    PrimaryNode* left;
    PrimaryNode* right;
    string data;
    SecondaryNode* secondaryTree;
    int height;
    PrimaryNode();
    void insert(int , string, string);
    void remove(int, string);
    SecondaryNode* LLRBTinsertHelper(string, SecondaryNode*, string);
    bool isBlack(SecondaryNode*);
    SecondaryNode* AVLinsertHelper(string, SecondaryNode*, string);
    SecondaryNode* AVLdeleteHelper(string, SecondaryNode*);
    SecondaryNode* AVLrightRotate(SecondaryNode*&);
    SecondaryNode* AVLleftRotate(SecondaryNode*&);
    SecondaryNode* getLeftMostLeaf(SecondaryNode*);
    void colorChange(SecondaryNode*, SecondaryNode*);
    SecondaryNode* find(string key);
    void printLevelByLevel(PrimaryNode* nodePtr, fstream& );
    void printLevel(int count, PrimaryNode* nodePtr, fstream&);
    int getHeight(PrimaryNode* curr){
        if( curr == NULL)
            return 0;
        return curr->height;
    }
    //ToDo LLRBT insertion and remove
    SecondaryNode* LLRBTdeleteHelper(string, SecondaryNode*);
};


#endif //BM4_PRIMARYNODE_H
