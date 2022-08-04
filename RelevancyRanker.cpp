#include "RelevancyRanker.h"

RelevancyRanker::RelevancyRanker()
{
    d = new DocumentParser();
}
RelevancyRanker::~RelevancyRanker()
{

}

void RelevancyRanker::setDocs(vector<string>& list)
{
    for(int i = 0 ; i < list.size(); i++)
    {
        string k = list[i];
        this->docs.push_back(list[i]);
    }
}
void RelevancyRanker::setKeys(vector<string>& inKeys)
{
    keys = inKeys;
}

string RelevancyRanker::openFile(string& fileName)
{
    rapidjson::Document doc;
    ifstream inFS (fileName);
    string wholeFile;
    string temp;
    string contents;

    while(getline(inFS, temp))
    {
        wholeFile+= temp;
    }
    inFS.close();
    doc.Parse(wholeFile.c_str());

    string up = doc["text"].GetString();
    return up;

}
string RelevancyRanker::getText(string& path)
{

}
void RelevancyRanker::ranker()
{

}

vector<string> RelevancyRanker::getList()
{
    return docs;
}

int RelevancyRanker::countWordOccurrence(string &textIn, string &key)
{
    string t = textIn;
    int freq = 0;
    int len = key.size();
    if(t.find(key) == variant_npos)
    {
        return 0;
    }
    else
    {
        while(t.find(key) != variant_npos)
        {
            freq++;
            t.erase(0, t.find(key) + len);
        }
        return freq;
    }

}

vector<string> RelevancyRanker::orderRelevancies()
{
    vector<string> orderedResults;
    map<int, string> order;
    map<int, vector<string>> ordered;
    auto itr = articleRelevancy.begin();
    while(itr != articleRelevancy.end())
    {

        pair<int, vector<string>> rev;
        string a = itr->first;
        int n = itr->second;
        vector<string> s;
        s.push_back(a);
        if(ordered.find(n) == ordered.end())
        {
            rev = make_pair(n, s);
            ordered.insert(rev);
        }
        else
        {
            ordered.find(n)->second.push_back(a);
        }
        itr++;

    }
    auto itr2 = ordered.begin();

    while(itr2 != ordered.end())
    {
//       cout << itr2->first << ": " << endl;
        for(int i = 0; i < itr2->second.size(); i++)
        {
//           cout << '\t' << '\t' << itr2->second[i] << endl;
            orderedResults.push_back(itr2->second[i]);
        }
        itr2++;

    }

    return orderedResults;

}


void RelevancyRanker::generateMap()
{
    for (int i =0; i< docs.size(); i++)
    {
        string path = docs[i];
        string text = openFile(docs[i]);
        text = parseFile(text);

        int freq = 0;
        int numKeys = keys.size();
        for(int j = 0; j < numKeys; j++)
        {

            string keyStemmed = keys[j];
            if(keyStemmed.empty())
            {
                break;
            }
            //keyStemmed = keyStemmed.substr(1);
            keyStemmed = parseFile(keyStemmed);
            freq = freq + countWordOccurrence(text, keyStemmed);
        }
        pair<string, int> a;
        a = make_pair(path, freq);
        articleRelevancy.insert(a);
    }
}
string RelevancyRanker::parseFile(string& unparsedText)
{
    string t = unparsedText;
    t = d->stemText(t);
    return t;
}
//#include "RelevancyRanker.h"
//
//RelevancyRanker::RelevancyRanker()
//{
//    d = new DocumentParser();
//}
//RelevancyRanker::~RelevancyRanker()
//{
//
//}
//
//void RelevancyRanker::setDocs(vector<string>& list)
//{
//    for(int i = 0 ; i < list.size(); i++)
//    {
//        string k = list[i];
//        this->docs.push_back(list[i]);
//    }
//}
//void RelevancyRanker::setKeys(vector<string>& inKeys)
//{
//    keys = inKeys;
//}
//
//string RelevancyRanker::openFile(string& fileName)
//{
//    rapidjson::Document doc;
//    ifstream inFS (fileName);
//    string wholeFile;
//    string temp;
//    string contents;
//
//    while(getline(inFS, temp))
//    {
//        wholeFile+= temp;
//    }
//    inFS.close();
//    doc.Parse(wholeFile.c_str());
//
//    string up = doc["text"].GetString();
//    return up;
//
//}
//string RelevancyRanker::getText(string& path)
//{
//
//}
//void RelevancyRanker::ranker()
//{
//
//}
//
//vector<string> RelevancyRanker::getList()
//{
//    return docs;
//}
//
//int RelevancyRanker::countWordOccurrence(string &textIn, string &key)
//{
//    string t = textIn;
//    int freq = 0;
//    int len = key.size();
//    if(t.find(key) == variant_npos)
//    {
//        return 0;
//    }
//    else
//    {
//        while(t.find(key) != variant_npos)
//        {
//            freq++;
//            t = t.substr(t.find(key) + len);
//        }
//        return freq;
//    }
//
//}
//
//vector<string> RelevancyRanker::orderRelevancies()
//{
//    vector<string> orderedResults;
//    map<int, string> order;
//    map<int, vector<string>> ordered;
//    auto itr = articleRelevancy.begin();
//    while(itr != articleRelevancy.end())
//    {
//
//        pair<int, vector<string>> rev;
//        string a = itr->first;
//        int n = itr->second;
//        vector<string> s;
//        s.push_back(a);
//        if(ordered.find(n) == ordered.end())
//        {
//            rev = make_pair(n, s);
//            ordered.insert(rev);
//        }
//        else
//        {
//            ordered.find(n)->second.push_back(a);
//        }
//        itr++;
//
//    }
//    auto itr2 = ordered.begin();
//
//    while(itr2 != ordered.end())
//    {
////       cout << itr2->first << ": " << endl;
//        for(int i = 0; i < itr2->second.size(); i++)
//        {
////           cout << '\t' << '\t' << itr2->second[i] << endl;
//            orderedResults.push_back(itr2->second[i]);
//        }
//        itr2++;
//
//    }
//
//    return orderedResults;
//
//}
//
//
//void RelevancyRanker::generateMap()
//{
//    for (int i =0; i< docs.size(); i++)
//    {
//        string path = docs[i];
//        string text = openFile(docs[i]);
//        text = parseFile(text);
//
//        int freq = 0;
//        int numKeys = keys.size();
//        for(int j = 0; j < numKeys; j++)
//        {
//
//            string keyStemmed = keys[j];
//            if(keyStemmed.empty())
//            {
//                break;
//            }
//            //keyStemmed = keyStemmed.substr(1);
//            keyStemmed = parseFile(keyStemmed);
//            freq = freq + countWordOccurrence(text, keyStemmed);
//        }
//        pair<string, int> a;
//        a = make_pair(path, freq);
//        articleRelevancy.insert(a);
//    }
//}
//string RelevancyRanker::parseFile(string& unparsedText)
//{
//    string t = unparsedText;
//    t = d->stemText(t);
//    return t;
//}
//
//
//////
////// Created by owner on 4/25/2022.
//////
////
////#include "RelevancyRanker.h"
////
////RelevancyRanker::RelevancyRanker()
////{
////    d = new DocumentParser();
////}
////RelevancyRanker::~RelevancyRanker()
////{
////
////}
////
////void RelevancyRanker::setDocs(vector<string>& list)
////{
////   for(int i = 0 ; i < list.size(); i++)
////   {
////       string k = list[i];
////       this->docs.push_back(list[i]);
////   }
////}
////void RelevancyRanker::setKeys(vector<string>& inKeys)
////{
////    keys = inKeys;
////}
////
////string RelevancyRanker::openFile(string& fileName)
////{
////    rapidjson::Document doc;
////    ifstream inFS (fileName);
////    string wholeFile;
////    string temp;
////    string contents;
////
////    while(getline(inFS, temp))
////    {
////        wholeFile+= temp;
////    }
////    inFS.close();
////    doc.Parse(wholeFile.c_str());
////
////    string up = doc["text"].GetString();
////    return up;
////
////}
////string RelevancyRanker::getText(string& path)
////{
////
////}
////void RelevancyRanker::ranker()
////{
////
////}
////
////vector<string> RelevancyRanker::getList()
////{
////    return docs;
////}
////
////int RelevancyRanker::countWordOccurrence(string &textIn, string &key)
////{
////    cout << "ENTER COUNT WORD OCCURRENCE" << endl;
////    string t = textIn;
////    int freq = 0;
////    int len = key.size();
////    if(t.find(key) == string::npos)
////    {
////        return freq;
////    }
////    else
////    {
////        cout << "ENTER ELSE" << endl;
////        while(t.find(key) != variant_npos)
////        {
////            cout << "ENTER WHILE" << endl;
////            freq++;
////            t = t.substr(t.find(key) + len);
////            cout << t << endl;
////        }
////        return freq;
////    }
////
////}
////
////vector<string> RelevancyRanker::orderRelevancies()
////{
////    cout << "ENTER ORDER RELEVANCIES" << endl;
////    vector<string> orderedResults;
////    map<int, string> order;
////    map<int, vector<string>> ordered;
////    auto itr = articleRelevancy.begin();
////    while(itr != articleRelevancy.end())
////    {
////
////        pair<int, vector<string>> rev;
////        string a = itr->first;
////        int n = itr->second;
////        vector<string> s;
////        s.push_back(a);
////        if(ordered.find(n) == ordered.end())
////        {
////            rev = make_pair(n, s);
////            ordered.insert(rev);
////        }
////        else
////        {
////            ordered.find(n)->second.push_back(a);
////        }
////        itr++;
////
////    }
////    auto itr2 = ordered.begin();
////
////    while(itr2 != ordered.end())
////    {
//////       cout << itr2->first << ": " << endl;
////       for(int i = 0; i < itr2->second.size(); i++)
////       {
//////           cout << '\t' << '\t' << itr2->second[i] << endl;
////           orderedResults.push_back(itr2->second[i]);
////       }
////       itr2++;
////
////    }
////
////    return orderedResults;
////
////}
////
////
////void RelevancyRanker::generateMap()
////{
////    cout << "ENTER MAP GENERATION " << endl;
////    for (int i =0; i< docs.size(); i++)
////    {
////        string path = docs[i];
////        string text = openFile(docs[i]);
////        text = parseFile(text);
////
////        int freq = 0;
////        int numKeys = keys.size();
////        for(int j = 0; j < numKeys; j++)
////        {
////
////            string keyStemmed = keys[j];
////            if(keyStemmed.empty())
////            {
////                cout << "REACHED BREAK " << endl;
////                break;
////            }
////            //keyStemmed = keyStemmed.substr(1);
////            keyStemmed = parseFile(keyStemmed);
////            freq = freq + countWordOccurrence(text, keyStemmed);
////        }
////        pair<string, int> a;
////        a = make_pair(path, freq);
////        articleRelevancy.insert(a);
////    }
////
////}
////string RelevancyRanker::parseFile(string& unparsedText)
////{
////    cout << "ENTER PARSE FILE" << endl;
////    string t = unparsedText;
////    t = d->stemText(t);
////    return t;
////}
