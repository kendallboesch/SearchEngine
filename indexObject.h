//
// Created by Kendalll Boesch on 4/13/22.
//

#ifndef INC_22S_FINAL_PROJ_INDEXOBJECT_H
#define INC_22S_FINAL_PROJ_INDEXOBJECT_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;
class indexObject {
public:
    indexObject();
    indexObject(const string);
    ~indexObject();
    string getKey();
    void setKey(string);
    vector<string>& getArticles();




private:

    vector<string> foundOn;
    string key;

};


#endif //INC_22S_FINAL_PROJ_INDEXOBJECT_H
