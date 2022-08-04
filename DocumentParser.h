//
// Created by Kendalll Boesch on 4/13/22.
//

/****************
 * Kendall Boesch & Akul
 * CS 2341 Data Structures
 * Final Program: Search Engine
 *
 *      DOCUMENT PARSER (.h)
 *
 *      Class for .json file accessing, reading,
 *      and manipulating. Part I of search engine
 *      architecture
 *
 ***************/

#ifndef INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
#define INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
// INCLUDES
#include "AVLTree.h"
#include <iostream>
#include "include/rapidjson/document.h"
#include <string>
#include <fstream>
#include <vector>
#include "porter2_stemmer.h"
#include <filesystem>
#include <variant>
#include <algorithm>

// NAMESPACES
using namespace std;
namespace fs = std::filesystem;
class DocumentParser{
public:
    // CONSTRUCTOR / DESTRUCTOR
    DocumentParser();
    ~DocumentParser();
    // SET UP FUNCS
    void loadStopWords();
    void loadNonStemWords();
    // FILE MANIPULATION FUNCS
    string fileManip(const string&);
    string articleName(const string&);
    vector<string> getPersons(const string&);
    vector<string> getOrgs(const string&);
    string removeStopWords(const string&);
    string stemText(const string&);
    string stemTextII(const string&);
    string stemTextIII(const string&);
    void fillWordTree(const string&, const string&);
    // STEMMING HELPER FUNCTIONS
    string removePunc(const string&);
    bool isMonthOrDay(const string&);
    bool isPunct(const char&);
    bool isNum(const char&);
    bool allSpace(const string&);





private:

    // VECTORS FOR ARTICLE OPTIMIZATION
    vector<string> stopWords;
    vector<string> nonStem;

};


#endif //INC_22S_FINAL_PROJ_DOCUMENTPARSER_H
