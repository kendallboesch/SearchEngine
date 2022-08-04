//
// Created by Kendalll Boesch on 4/15/22.
//
/************************************
 * Kendall Boesch & Akul
 * CS 2341 Data Structures
 * Final Project: Search Engine
 *
 *      ENGINE DRIVER (.H)
 *
 *   Driver class for search engine program.
 *   Contains the three AVL search trees and
 *   iterates through each provided article
 *   updating the appropriate trees when necessary

    EngineDriver();
    ~EngineDriver();
    // FILE READ
    void openWithFS(char* argv[]);
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
    void displayMenu();
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
    void executeAction();
    void printResults();
 *
 ************************************/

#include "EngineDriver.h"

using namespace std;
/***************
 *      DEFAULT CONSTRUCTOR
 */
EngineDriver::EngineDriver(char* argv[])
{
    // CREATE NEW DOCUMENT PARSER OBJECT
    d = new DocumentParser();
    q = new QueryProcessor();
    r = new RelevancyRanker();
    numArticles = 0;
    numWords = 0;
    numOrgs = 0;
    numPersons = 0;
    path[0] = "/Users/kendalllboesch/CLionProjects/22s-final-project-kendall-akul/cmake-build-debug/22s_final_proj'\'";

    displayMenu(argv);


}
/**************
 *  DESTRUCTOR
 *
 */
EngineDriver::~EngineDriver()
{
    delete d;
}
/***********
 *      OPEN WITH FS
 *
 *  Opens the json directory & recursively iterates
 *  through each file contained inside. If a regular
 *  .json file save the file names and parse the
 *  document, updating the three AVL trees
 *
 * @param directory
 *  source: https://github.com/AlexShock66/Reading_In_Directories_Example.git
 ***********/
void EngineDriver::openWithFS(char* arg[])
{
   int counter = 0;
    // RECURSIVELY ITERATE THROUGH DIRECTORY PASSES AS PROGRAM ARG #1
    for (const auto & entry : fs::recursive_directory_iterator(arg[1]))
    {
       // counter++;
//        if (counter == 100)
//        {
//            break;
//        }
            // ENSURE THE CURRENT FILE IS A REGULAR FILE
        if (entry.is_regular_file())
        {
                    // ENSURE THE CURRENT FILE (ENTRY) IS A JSON FILE
            if (entry.path().extension().string() == ".json")
            {
                counter++;
                    // SAVE FILE NAME
              string filename = entry.path().c_str();
                    // GET STEMED TEXT FROM FILE
              string ready = d->fileManip(filename);
                    // UPDATE WORD TREE W STEMMED TEXT & ASSOCIATED FILES
              updateWordTree(filename, ready);
                     //RETRIEVE VECTOR OF PERSONS
              vector<string> persons = d->getPersons(filename);
                    // IF THE VECTOR ISNT EMPTY
              if(persons.size() != 0)
              {
                    //UPDATE PERSON TREE W NEW NAMES
                  updatePersonsTree(filename, persons);
              }
                // RETRIEVE VECTOR OF ORGANIZATIONS & ASSOCITED FILES
              vector<string> organizations = d->getOrgs(filename);
                // IF THE VECTOR ISNT EMPTY
              if(organizations.size() != 0)
              {
                  // UPDATE ORG TREE W NEW ORGS & ASSOCIATED FILES
                  updateOrgTree(filename, organizations);
              }
            }
        }
    }
    numArticles = counter;
}
/*****************
 *  UPDATE WORD TREE
 * recieves a large string of an articles stemmed
 * text. Iterates through the string extracting
 * words (ignoring spaces & null terminator) and
 * creates words which are then inserted into the
 * word AVLTree
 *
 * @param file
 * @param text
 */
void EngineDriver::updateWordTree( string& file,  string& text)
{


        string f = file;
        // MUTABLE COPY OF TEXT
        string t = text;
        // ITERATOR TO MOVE THROUGH PASSED TEXT
            // SET TO BEGINNING OF STRING
        string::iterator itr = t.begin();
            // NUMBER OF CHARS IN TEXT
        int limit = t.size();
            // COUNT OF WHICH CAR CURRENTLY ON
                // (HAVING ISSUES W T.END() SO ^^)
        int count = 1;
            // CURRENT WORD BEING FORMED
        string curr;

        // WHILE THE END OF THE TEXT IS NOT REACHED
        while( count < limit)
        {
            // WHILE CHAR @ ITR IS A SPACE
            while(*itr == ' ')
            {
                // IGNORE, INCREMENT COUNTER & ITERATOR
                itr++;
                count++;
            }
                // WHILE CHAR @ ITR IS NOT A SPACE OR NULL CHARACTER
            while(*itr != ' ' && *itr != '\0')
            {
                    // PUSH BACK THE CURRENT CHAR TO THE WORD BEING FORMED
                curr.push_back(*itr);
                    // INCREMENT ITR & COUNTER
                itr++;
                count++;
            }
            // CREATE KEY STRING FROM WORD FORMED
            string key = curr;
           // cout << key << endl;
                // INSERT WORD FORMED INTO WORD TREE
           bool newWord = wordTree.insert(key, f);
          // cout << key << endl;
           if(newWord)
           {
             // cout << "NewWord: " << newWord <<endl;
              // cout << "NumWords: " << numWords << endl;
               numWords++;
           }

            curr = "";
        }
}
/*******
 *  UPDATE PERSONS TREE
 *
 *  Takes in current file name and a vector of the
 *  persons associated with that file. Then inserts
 *  the person into the persons AVL Tree
 *
 *
 * @param file
 * @param p
 */
void EngineDriver::updatePersonsTree(string &file, vector<string>& p)
{
    string key; //KEY TO BE INSERTED INTO PERSONS TREE
    string f = file;


        // ITERATE THROUGH THE VECTOR PASSED IN
    for(int i = 0; i < p.size(); i++)
    {
        // KEY IS EQUAL TO THE ELEMENT AT I IN THE PASSED VECTOR
        key = p[i];
            // INSERT THE KEY INTO THE NAME AVL TREE
        bool newNode = nameTree.insert(key,f);
        if(newNode)
        {
            numPersons++;
        }
    }
}
/*********
 *      UPDATE ORG TREE
 *
 *    Takes in a file name and a vector of
 *    associated organizations. Then iterates
 *    through the vector passed in, inserting
 *    each organization (string) into the
 *    organization AVL tree
 *
 * @param file
 * @param o
 */
void EngineDriver::updateOrgTree(string &file, vector<string> & o)
{
    // STRING FOR KEY
    string key;
    string f = file;
    // ITERATE THROUGH VECTOR PASSED IN
    for(int i = 0; i < o.size(); i++)
    {
            // KEY IS EQUAL TO THE ELEMENT AT I IN THE PASSED VECTOR
        key = o[i];
            // INSERT THE KEY INTO THE ORG AVL TREE
        bool newNode = orgTree.insert(key, f);
        if(newNode)
        {
            numOrgs++;
        }
    }
}
/***********
 *      SEARCH WORD
 *  Reads in search term provided in first program
 *  argument. Then searches the AVL tree word tree
 *  to lpocate the term. if the term exists in the
 *  tree, returns a vector of all the aricles in
 *  which the stemmed version of that serch term
 *  is present. if the search term does not
 *  exist in the tree, returns null vector
 *
 * @param argv
 * @return
 */
vector<string> EngineDriver::searchWord(string src)
{
    cout << endl << endl << "SEARCH WORD" << endl << endl;
    // STRING WORD IS ASSIGNED TO THE FIRST PROGRAM ARGUMENT
 string word = src;
    // STEM THE SEARCH TERM
 Porter2Stemmer::stem(word);
 cout << word << endl;
    //RETRIEVE THE ASSOCIATED VECTOR
 vector<string> results = wordTree.locate(word);
    // RETURN RESULTS
 return results;
}
vector<string> EngineDriver::searchOrg(string src)
{
    cout << endl << endl << "SEARCH ORG" << endl << endl;

    string org = src;
    cout << org << endl;
    vector<string> results = orgTree.locate(org);
    return results;
}
vector<string> EngineDriver::searchPerson(string src)
{
    cout << endl << endl << "SEARCH PERSON" << endl << endl;

    string person = src;
    cout << person << endl;
    vector<string> results = nameTree.locate(person);
    return results;
}
string EngineDriver::readInQuery()
{
 string inQuery = q->retrieveInput();
 q->setBools();
 cout << inQuery << endl;
 return inQuery;
}
vector<string> EngineDriver::processQuery()
{
    q->fillVecs();
    vector<string> results;
    if(q->singleQuery)
    {
        if(q->orgs)
        {
            string srch = q->q.substr(4);
            results = searchOrg(srch);
        }
        else if(q->people)
        {
            string src = q->q.substr(7);
            results = searchPerson(src);
        }
        else
        {
            results = searchWord(q->q);
        }

        return results;
    }
    else if(q->hasAnd && !q->hasNot && !q->hasOr)
    {
          vector<string> n = intersection();
          return n;
    }
    else if(q->hasOr && !q->hasAnd && !q->hasNot)
    {
        vector<string> u = combination();
        return u;
    }
    else if(q->hasNot && !q->hasAnd && !q->hasOr)
    {
        vector<string> exc = exclusion();
        return exc;
    }
    else if(q->hasNot && q->hasAnd && !q->hasOr)
    {
        vector<string> n = intersection();
        vector<string> exc = binaryExclusion(n);
        vector<string> res = q->exclusion(n, exc);
        return res;
    }
    else if(q->hasNot && q->hasOr && !q->hasAnd)
    {
        vector<string> u = combination();
        vector<string> exc = binaryExclusion(u);
        vector<string> res = q->exclusion(u, exc);
        return res;
    }
    else if(q->hasOr && q->hasAnd)
    {
        cout <<  endl << "INVALID QUERY ENTRY" << endl;
        return {"NULL VECTOR"};
    }
}
void EngineDriver::displayMenu(char* arg[])
{
    if(requestedAction == 'Q')
    {
        return;
    }
   q->resetAll();

    char input;
    string inp;
    cout << "SEARCH ENGINE OPERATIONS: " << endl;
    if(wordTree.isEmpty() || wordTree.getRoot()->height == 0)
    {
        cout << "L - Load corpus" << endl;
        cout << "P - Provide path for corpus" << endl;
        cout << "Q - Quit search engine" << endl;
        getline(cin, inp);
        input = inp[0];

        if(input == 'L' || input == 'l')
        {
            requestedAction = 'L';
        }
        else if(input == 'P' || input == 'p')
        {
            requestedAction = 'P';
        }
        else if(input == 'Q' || input == 'q')
        {
            requestedAction = 'Q';
        }
    }
    else
    {


        cout << '\t' << "S - New search query" << endl;
        if (!results.empty())
        {
            cout << '\t' << "R - Select an article to view" << endl;

        }
        if (requestedAction == 'R')
        {
            cout << '\t' << "V - View results again" << endl;
        }
        cout << '\t' << "C - Clear index" << endl;
        cout << '\t' << "Q - Quit search engine" << endl;
        getline(cin, inp);
        input = inp[0];

        if (input == 'S' || input == 's')
        {
            requestedAction = 'S';

        } else if (input == 'R' || input == 'r')
        {
            requestedAction = 'R';
        } else if (input == 'Q' || input == 'q')
        {
            requestedAction = 'Q';

        } else if (input == 'V' || input == 'v')
        {
            requestedAction = 'V';
        }
        else if(input == 'L' || input == 'l')
        {
            requestedAction = 'L';
        }
        else if(input == 'C' || input == 'c')
        {
            requestedAction = 'C';
        }
    }
    executeAction(arg);
    displayMenu(arg);
}
vector<string> EngineDriver::getArticles(string& in)
{
    vector<string> result;
    char type = q->classification(in);
    string term = in.substr(1);
    if(type == 'W')
    {
        result = searchWord(term);
    }
    else if(type == 'O')
    {
        result = searchOrg(term);
    }
    else if(type == 'P')
    {
        result = searchPerson(term);
    }
    return result;
}
vector<string> EngineDriver::intersection()
{
    vector<string> vi = getArticles(q->ands[0]);
    vector<string> vii = getArticles(q->ands[1]);
    return auxIntersection(vi, vii, 1);
}
vector<string> EngineDriver::auxIntersection(vector<string>& vi, vector<string>& vii, int ind)
{
    vector<string> intersect = q->findShared(vi, vii);
    if(ind + 1 < q->ands.size())
    {
        ind++;
        vector<string> nextSrch = getArticles(q->ands[ind]);
        return auxIntersection(intersect, nextSrch, ind);
    }
    else
    {
        return intersect;
    }
}
vector<string> EngineDriver::combination()
{
    vector<string> vi = getArticles(q->ors[0]);
    vector<string> vii = getArticles(q->ors[1]);
    return auxCombination(vi, vii, 1);
}
vector<string> EngineDriver::auxCombination(vector<string>& vi, vector<string> & vii, int ind)
{
    vector<string>combo = q->synthesis(vi, vii);
    if(ind + 1 < q->ors.size())
    {
        ind++;
        vector<string>nextSrch = getArticles(q->ors[ind]);
        return auxCombination(combo, nextSrch, ind);
    }
    else
    {
        return combo;
    }
}
vector<string> EngineDriver::auxExclusion(vector<string>& vi, vector<string>& vii, int ind)
{
    vector<string>excl = q->exclusion(vi, vii);
    if(ind + 1 < q->nots.size())
    {
        ind++;
        vector<string>nextSrch = getArticles(q->nots[ind]);
        while(ind+1 < q->nots.size())
        {
            excl = q->synthesis(excl, nextSrch);
        }
    }
    return excl;

}
vector<string> EngineDriver::exclusion()
{
    vector<string> vi = getArticles(q->q);
    vector<string> vii = getArticles(q->nots[0]);
    return auxExclusion(vi, vii, 0);
}
vector<string> EngineDriver::auxBinaryExclusion(vector<string>& vi, vector<string>& vii, int ind)
{
    vector<string> excl = q->exclusion(vi, vii);
    if(ind + 1 < q->nots.size())
    {
        ind++;
        vector<string> nextSrch = getArticles(q->nots[ind]);
        while(ind + 1 < q->nots.size())
        {
            excl = q->synthesis(excl, nextSrch);
        }
    }
    return excl;
}
vector<string> EngineDriver::binaryExclusion(vector<string>& includes)
{
    vector<string> vii = getArticles(q->nots[0]);
    return auxBinaryExclusion(includes, vii, 0);

}
vector<string> EngineDriver::generateRelevancyRanking(vector<string>& unorderedResults)
{
    vector<string> keys;
    r->setDocs(unorderedResults);
//   for(int i = 0; i < unorderedResults.size(); i++)
//   {
//       r->docs.push_back(unorderedResults[i]);
//   }
    if(q->hasAnd)
    {
        keys = q->ands;
    }
    else if(q->hasOr)
    {
        keys = q->ors;
    }
    else
    {
        keys.push_back(q->q);
    }
    r->setKeys(keys);
    r->generateMap();

    vector<string> orderedResults = r->orderRelevancies();

    return orderedResults;
}
string EngineDriver::openSelectedArticle(int selection)
{
    string fName = results[results.size() - selection];
    rapidjson::Document doc;
    ifstream inFS(fName);
    string wholeFile, temp, text;
    while(getline(inFS, temp))
    {
        wholeFile+= temp;
    }
    inFS.close();
    doc.Parse(wholeFile.c_str());
    text = doc["text"].GetString();
    return text;
}
void EngineDriver::getUIPath()
{
    cout << "Enter absolute path: " << endl;
    string p;
    getline(cin, p);
    char p1[p.size()];
    strcpy(p1, p.c_str());

    path[1] = new char[p.size()];
    strcpy(path[1], p1);
}
int EngineDriver::promptSelection()
{

    string selection;
    cout << "Enter selection: " << endl;
    getline(cin, selection);
    int request = atoi(selection.c_str());
    return request;
}
void EngineDriver::executeAction(char* argv[])
{
    chrono::time_point<chrono::high_resolution_clock> runStart, runStop;
    runStart = chrono::high_resolution_clock::now();
    if(requestedAction == 'S')
    {
        for(int i = 0; i < results.size(); i++)
        {
            results.pop_back();
        }
        readInQuery();
        vector<string> res = processQuery();
        if(res[0] != "NULL VECTOR")
        {
            vector<string> orderedResults = res; //generateRelevancyRanking(res);

            cout << "RESULTS: " << endl;
            int ind = 1;
            for(int i = orderedResults.size() - 1; i >= 0; i--)
            {
                results.push_back(orderedResults[i]);
                ind++;
            }
            runStop = chrono::high_resolution_clock::now();
            chrono::duration<double> t = runStop - runStart;
            cout << endl << endl << "Query Processing & execution time: " << t.count() << endl;
            printResults();
        }
        else
        {
            cout << "No articles match this search" << endl << endl << endl;
            runStop = chrono::high_resolution_clock::now();
            chrono::duration<double> t = runStop - runStart;


        }


    }
    else if(requestedAction == 'L')
    {

        this->openWithFS(argv);
        cout<< endl << "Articles Parsed: " << numArticles << endl;
        cout << "Unique words indexed: " <<  numWords  << endl;
        cout << "Unique Organiaztions indexed: " << numOrgs << endl;
        cout << "Unique Persons indexed: " << numPersons << endl << endl;
    }
    else if(requestedAction == 'P')
    {
        getUIPath();
        this->openWithFS(path);

        cout<< endl << "Articles Parsed: " << numArticles << endl;
        cout << "Unique words indexed: " <<  numWords  << endl;
        cout << "Unique Organiaztions indexed: " << numOrgs << endl;
        cout << "Unique Persons indexed: " << numPersons << endl << endl;

    }
    else if(requestedAction == 'Q')
    {

    }
    else if (requestedAction == 'R')
    {
        int selection = promptSelection();
        string text = openSelectedArticle(selection);
        cout << endl << endl << '\t' << text << endl << endl;
    }
    else if(requestedAction == 'V')
    {
        printResults();
    }
    else if(requestedAction == 'C')
    {
        wordTree.emptyTree();
        orgTree.emptyTree();
        nameTree.emptyTree();
        numWords = numPersons = numArticles = numOrgs = 0;
        q->resetAll();
    }
}
void EngineDriver::printResults()
{
    if(results.size() < 15)
    {
        for(int i = 0; i < results.size(); i++)
        {
            cout << '[' << i + 1 << ']' << '\t' << d->articleName(results[i]) << endl;
        }
    }
    else
    {
        for(int i = 0; i < 15; i++)
        {
            cout << '[' << i + 1 << ']' << '\t' << d->articleName(results[i]) << endl;
        }
    }

}
