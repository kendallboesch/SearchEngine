//
// Created by Kendalll Boesch on 4/15/22.
//
/************************************
 * Kendall Boesch & Akul
 * CS 2341 Data Structures
 * Final Project: Search Engine
 *
 *      ENGINE DRIVER (.cpp)
 *
 *   Driver class for search engine program.
 *   Contains the three AVL search trees and
 *   iterates through each provided article
 *   updating the apropriate trees when necessary
 *
 ************************************/
#ifndef INC_22S_FINAL_PROJ_ENGINEDRIVER_H
#define INC_22S_FINAL_PROJ_ENGINEDRIVER_H

// INCLUDES
#include "DocumentParser.h"
#include "QueryProcessor.h"
#include "RelevancyRanker.h"
#include "AVLTree.h"
#include <vector>
#include <string>
#include <iostream>
#include "porter2_stemmer.h"
#include <cstring>
#include <chrono>



// NAMESPACES
using namespace std;
namespace fs = std::filesystem;
class EngineDriver{

public:
    // CONSTRUCTOR // DESTRUCTOR
    EngineDriver(char*[]);
    ~EngineDriver();
    // FILE READ
    void openWithFS(char*[]);
    // TREE FORMING
    void updateWordTree( string&,  string&);
    void updatePersonsTree(string&, vector<string>&);
    void updateOrgTree(string&, vector<string>&);
    // SEARCH TERM LOCATION
    vector<string> searchWord(string);
    vector<string> searchOrg(string);
    vector<string> searchPerson(string);
    string readInQuery();
    vector<string> processQuery();
    // NEW VERSION
    vector<string> getArticles(string&);
    void displayMenu(char*[]);
    char requestedAction;
    vector<string> auxIntersection(vector<string>& , vector<string>&, int);
    vector<string> intersection();
    vector<string> auxCombination(vector<string>&, vector<string>&, int);
    vector<string> combination();
    vector<string> auxExclusion(vector<string>&, vector<string>&, int);
    vector<string> exclusion();
    vector<string> binaryExclusion(vector<string>&);
    vector<string> auxBinaryExclusion(vector<string>&, vector<string>&, int);
    vector<string> generateRelevancyRanking(vector<string>&);
    int promptSelection();
    string openSelectedArticle(int);
    void executeAction(char*[]);
    void printResults();
    void getUIPath();
private:
        // AVL TREES FOR SEARCHING
    AVLTree<string> wordTree;
    vector<string> top25Words;
    AVLTree<string> nameTree;
    AVLTree<string> orgTree;
        // PROGRAM OBJECTS
    DocumentParser* d;
    QueryProcessor* q;
    RelevancyRanker* r;
    vector<string> results;
    //string path;
    int numArticles;
    unsigned long long numWords;
    unsigned long long numOrgs;
    unsigned long long numPersons;
    char* path[10];


};



#endif //INC_22S_FINAL_PROJ_ENGINEDRIVER_H
