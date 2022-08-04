//
// Created by Kendalll Boesch on 4/20/22.
//

#ifndef INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
#define INC_22S_FINAL_PROJ_QUERYPROCESSOR_H

#include <string>
#include<iostream>
#include<vector>
#include "AVLNode.h"


using namespace std;
class QueryProcessor{
public:
    QueryProcessor();
    ~QueryProcessor();
    string retrieveInput();
    string getQuery();
    void setBools();
    void fillVecs();
    void andOnly();
    void orOnly();
    void notOnly();
    void andOrNot();
    void andNot();
    void orNot();
    void resetAll();

    // CASE I: only keyword, no operators

    // CASE II: AND only
    // CASE III: OR only
    vector<string>findShared(vector<string>&, vector<string>&);
    vector<string> synthesis(vector<string>&, vector<string>&);
    //  CASE IV: NOT only
    vector<string> exclusion(vector<string>&, vector<string>&);

    // NEW VERSION

    char classification(string);



    bool orgs;
    bool people;
    bool words;
    bool hasAnd;
    bool hasOr;
    bool hasNot;
    bool singleQuery;
    string q;
    vector<string> ands;
    vector<string> ors;
    vector<string> nots;



private:
    string query;
    vector<string> results;




};


#endif //INC_22S_FINAL_PROJ_QUERYPROCESSOR_H
