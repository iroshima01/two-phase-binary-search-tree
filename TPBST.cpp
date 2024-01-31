#include "TPBST.h"
/**
 * Creating a TPBST object with NULL value.
 */
TPBST::TPBST() {
    primaryHead = NULL;
}

/**
 * Insertion algorithm of a node by given parameters.
 * @param part = the part of the insertion ( 1 = AVL insertion) ( 2 = LLRBT insertion)
 * @param data = string data to insert (primaryNode)
 * @param data2 = string data to insert (secondaryNode)
 * @param price = string price of the node named data2
 */
void TPBST::insert(int part,string data,string data2,string price){
    insertItem(part,primaryHead, data, data2,price);
}

/**
 * Insertion algorithm of a node by given parameters.
 * @param part = the part of the insertion ( 1 = AVL insertion) ( 2 = LLRBT insertion)
 * @param node = pointer to the current node
 * @param data = string data to insert (primaryNode)
 * @param data2 = string data to insert (secondaryNode)
 * @param price = string price of the node named data2
 */
void TPBST::insertItem(int part, PrimaryNode*& node, string data,string data2,string price){
    if( node == NULL){
        node = new PrimaryNode();
        node->data = data;
        node->insert(part,data2,price);
    }
    else{
        if( data < node->data ){
            insertItem(part,node->left,data,data2,price);
        }
        else if( data > node->data){
            insertItem(part,node->right,data,data2,price);
        }
        else if(data == node->data){
            node->insert(part,data2,price);
        }
    }
    node->height = 1+ max(node->getHeight(node->left), node->getHeight(node->right));
}

/**
 * Remove algorithm of a node by given parameters.
 * @param part = the part of the deletion ( 1 = AVL deletion) ( 2 = LLRBT deletion)
 * @param data = string data to delete (primaryNode)
 * @param data2 = string data to delete (secondaryNode)
 */
void TPBST::remove(int part,string data,string data2){
    removeItem(part,primaryHead, data, data2);
}

/**
 * Remove helper algorithm of a node by given parameters.
 * @param part = the part of the deletion ( 1 = AVL deletion) ( 2 = LLRBT deletion)
 * @param node = pointer to the current node
 * @param data = string data to delete (primaryNode)
 * @param data2 = string data to delete (secondaryNode)
 */
void TPBST::removeItem(int part, PrimaryNode*& node, string data,string data2){
    if( node == NULL)
        return;
    else{
        if( data < node->data ){
            removeItem(part,node->left,data,data2);
        }
        else if( data > node->data){
            removeItem(part,node->right,data,data2);
        }
        else{
            node->remove(part,data2);
        }
    }
    if( node != NULL)
        node->height = 1+ max(node->getHeight(node->left), node->getHeight(node->right));
}

/**
 * Prints the TPBST level by level and writes to the given file
 * @param out = outputFile
 */
void TPBST::print(fstream& out) {
    primaryHead->printLevelByLevel(primaryHead, out);
}

/**
 * Prints the given TPBST node and writes to the given file if it exists.
 * @param data = primaryNode data.
 * @param out = outputFile
 */
void TPBST::print(string data, fstream& out){
    PrimaryNode* curr = primaryHead;
    int i = 0;
    for(; curr != NULL;){
        if( i == 0)
            out << "\n";
        i++;
        if( curr->data == data){
            out << "\"" << curr->data << "\":";
            if( curr->secondaryTree == NULL){
                out << "{}\n";
            }
            else{
                curr->secondaryTree->printLevelByLevel(curr->secondaryTree,out);
                out << "\n";
            }
            break;
        }
        else if( curr->data < data)
            curr = curr->right;
        else if( curr->data > data)
            curr = curr->left;
    }
}

/**
 * Finds the given TPBST node and writes to the given file if it exists.
 * @param data = primaryNode data.
 * @param data2 = secondaryNode data.
 * @param out = outputFile
 */
void TPBST::find(string data, string data2, fstream& out) {
    PrimaryNode* curr = primaryHead;
    SecondaryNode* temp = NULL;
    for(; curr != NULL;){
        if( curr->data == data){
            temp = curr->find(data2);
            break;
        }
        else if( curr->data < data)
            curr = curr->right;
        else if( curr->data > data)
            curr = curr->left;
    }
    if( temp != NULL){
        out << "\n\"" << curr->data << "\":\n\t\"" << temp->data << "\":\"" << temp->price << "\"\n";
    }
}

/**
 * Finds the given TPBST node and changes it's price with the given value if it exists.
 * @param data = primaryNode data.
 * @param data2 = secondaryNode data.
 * @param value = new price.
 */
void TPBST::update(string data, string data2, string value){
    PrimaryNode* curr = primaryHead;
    SecondaryNode* temp = NULL; //ToDo delete if it crashes (?)
    for(; curr != NULL;){
        if( curr->data == data){
            temp = curr->find(data2);
            break;
        }
        else if( curr->data < data)
            curr = curr->right;
        else if( curr->data > data)
            curr = curr->left;
    }
    if( temp != NULL){
        temp->price = value;
    }
}