//
// Created by owner on 4/25/2022.
//

#ifndef INC_22S_FINAL_PROJ_RELEVANCYRANKER_H
#define INC_22S_FINAL_PROJ_RELEVANCYRANKER_H

#include <vector>
#include <string>
#include <iostream>
#include "DocumentParser.h"
#include <map>


using namespace std;
class RelevancyRanker{
public:
    RelevancyRanker();
    ~RelevancyRanker();
    void setDocs(vector <string>&);
    void setKeys(vector<string>&);
    void generateMap();
    void ranker();
    string openFile(string&);
    string getText(string&);
    string parseFile(string&);
    vector <string> getList();
    int countWordOccurrence(string&, string&);
    vector<string> orderRelevancies();
    std::vector <string> docs;

private:
    vector<string> keys;
    DocumentParser* d;
    map<string, int> articleRelevancy;
};


#endif //INC_22S_FINAL_PROJ_RELEVANCYRANKER_H
