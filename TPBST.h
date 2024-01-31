#ifndef BM4_TPBST_H
#define BM4_TPBST_H
#include "PrimaryNode.h"

class TPBST {
public:
    TPBST();
    PrimaryNode* primaryHead;
    void insert(int, string, string,string);
    void insertItem(int, PrimaryNode*&, string,string,string);
    void print(fstream& );
    void find(string data, string data2, fstream&);
    void print(string, fstream&);
    void update(string,string,string);
    void remove(int, string, string);
    void removeItem(int, PrimaryNode*&, string, string);
};


#endif //BM4_TPBST_H
