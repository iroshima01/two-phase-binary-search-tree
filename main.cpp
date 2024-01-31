#include "TPBST.h"

int main(int argc, char** args) {
    fstream newFile;
    fstream newFile2;
    ifstream inputFile;
    string line;
    string word;
    string word2;
    string data;
    string data2;
    string num;
    TPBST myTree;
    TPBST secondTree;
    inputFile.open(args[1],ios::in);
    newFile.open(args[2], ios::out);
    newFile2.open(args[3], ios::out);

    if( inputFile){
        while( getline(inputFile,line)){
            string out = "command:" + line + "\n{";
            size_t found = line.find_first_of('\t');

            word = line.substr(0,found);
            line = line.substr(found+1);
            if( word == "insert"){
                found = line.find_first_of('\t');
                data = line.substr(0,found);
                line = line.substr(found+1);
                found = line.find_first_of('\t');
                data2 = line.substr(0, found);
                num = line.substr(found+1);
                myTree.insert(1,data,data2,num);
                secondTree.insert(2,data,data2,num);
            }
            else if( word == "printAllItems"){
                newFile << out;
                myTree.print(newFile);
                newFile << "\n}\n";

                newFile2 << out;
                secondTree.print(newFile2);
                newFile2 << "\n}\n";
            }
            else if( word == "updateData"){
                found = line.find_first_of('\t');
                data = line.substr(0,found);
                line = line.substr(found+1);
                found = line.find_first_of('\t');
                data2 = line.substr(0, found);
                found = line.find_last_of('\t');
                num = line.substr(found+1);
                myTree.update(data,data2,num);
                secondTree.update(data,data2,num);
            }
            else if( word == "printItem"){
                found = line.find_first_of('\t');
                data = line.substr(0,found);
                line = line.substr(found+1);
                found = line.find_first_of('\t');
                data2 = line.substr(0, found);
                newFile << out;

                myTree.find(data,data2,newFile);
                newFile << "}\n";

                newFile2 << out;
                secondTree.find(data,data2,newFile2);
                newFile2 << "}\n";
            }
            else if( word == "remove"){
                found = line.find_first_of('\t');
                data = line.substr(0,found);
                line = line.substr(found+1);
                found = line.find_first_of('\t');
                data2 = line.substr(0, found);
                myTree.remove(1,data,data2);
                secondTree.remove(2,data,data2);
            }
            else if( word == "printAllItemsInCategory"){
                data = line;
                newFile << out;
                myTree.print(data,newFile);
                newFile << "}\n";

                newFile2 << out;
                secondTree.print(data,newFile2);
                newFile2 << "}\n";
            }
            else if( word == "find"){
                found = line.find_first_of('\t');
                data = line.substr(0,found);
                line = line.substr(found+1);
                found = line.find_first_of('\t');
                data2 = line.substr(0, found);

                newFile << out;
                myTree.find(data,data2,newFile);
                newFile << "}\n";

                newFile2 << out;
                secondTree.find(data,data2,newFile2);
                newFile2 << "}\n";
            }
        }
    }
}
