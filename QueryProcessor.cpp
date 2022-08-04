//
// Created by Kendalll Boesch on 4/20/22.
//

#include "QueryProcessor.h"
#include <variant>

/**********
 * constructor
 *
 */
QueryProcessor::QueryProcessor()
{
    query = "";
    orgs = people = words = hasAnd = hasOr = hasNot = singleQuery = false;
}
QueryProcessor::~QueryProcessor()
{

}
string QueryProcessor::retrieveInput()
{
    cout << "ENTER SEARCH QUERY: " << endl;
    getline(cin, query);
    query = query;

    return query;
}
string QueryProcessor::getQuery()
{
    return query;
}
void QueryProcessor::setBools()
{
    if(query.find("ORG") != variant_npos)
    {
        orgs = true;

    }
    if(query.find("PERSON ") != variant_npos)
    {
        people = true;
    }
//
    if(query.find("AND ") != variant_npos)
    {
        hasAnd = true;
    }
    if(query.find("OR ") != variant_npos)
    {
        hasOr = true;
    }
    if(query.find("NOT ") != variant_npos)
    {
        hasNot = true;
    }
    if(!hasAnd && !hasOr && !hasNot)
    {
        singleQuery = true;
    }
}
void QueryProcessor::fillVecs()
{
    if(singleQuery)
    {
        q = query;
    }
    else if(hasAnd && !hasOr && !hasNot)
    {
        andOnly();
    }
    else if (hasOr && !hasAnd && ! hasNot)
    {
        orOnly();
    }
    else if(hasNot && !hasAnd && !hasOr)
    {
        notOnly();
    }
    else if( hasAnd && !hasOr && hasNot)
    {
        andNot();
    }
    else if(hasOr && hasNot && !hasAnd)
    {
        orNot();
    }
}
void QueryProcessor::andOnly()
{
    bool readingOrgs;
    bool readingPerson;
    bool reachedNot;
    // STRING STARTING AT FIRST TERM, EXCLUDES "AND"
    string tempQ = query.substr(4);
    string::iterator itr = tempQ.begin();
    readingOrgs = readingPerson  = reachedNot = false;
    int max = tempQ.size();
    int count = 0;
  //  while(itr != tempQ.end() && *itr != '\0')
  while(count <= max)
    {

        string curr = "";
        while(*itr!= ' ' && *itr != '\0')
        {
            curr.push_back(*itr);
            itr++;
            count++;
        }
        if(curr == "ORG")
        {
            readingOrgs = true;
            readingPerson = false;
            curr = "";
        }
        else if(curr == "PERSON")
        {
            readingPerson = true;
            readingOrgs = false;
            curr = "";
        }
        else if(curr == "NOT")
        {
            query = query.substr(count);
            break;
        }
        else
        {
            itr++;
            count++;
        }
        if (!readingOrgs && !readingPerson && curr != "")
        {
            curr = 'W' + curr;
            ands.push_back(curr);
            }
        else if (readingOrgs && curr != "")
        {
                curr = 'O' + curr;
                ands.push_back(curr);

        }
        else if (readingPerson && curr != "")
        {
                curr = 'P' + curr;
                ands.push_back(curr);
        }
    }

}
void QueryProcessor::orOnly()
{
    bool readingOrgs;
    bool readingPerson;
    // STRING STARTING AT FIRST TERM, EXCLUDES "OR"
    string tempQ = query.substr(3);
    string::iterator itr = tempQ.begin();
    readingOrgs = readingPerson  = false;
    int max = tempQ.size();
    int count = 0;

   //
   // while(itr != tempQ.end() && *itr != '\0')
   while(count < max)
   {
        string curr = "";
        while(*itr!= ' ' && *itr != '\0')
        {
            curr.push_back(*itr);
            itr++;
            count ++;
        }
        if(curr == "ORG")
        {
            readingOrgs = true;
            readingPerson = false;
            curr = "";
        }
        else if(curr == "PERSON")
        {
            readingPerson = true;
            readingOrgs = false;
            curr = "";
        }
        else if(curr == "NOT")
        {
            query = query.substr(count);
            break;
        }
        else
        {
            itr++;
            count++;
        }

        if( !readingOrgs && !readingPerson && curr != "")
        {
            curr = 'W' + curr;
            ors.push_back(curr);
        }
        else if(readingOrgs && curr != "")
        {
            curr = 'O' + curr;
            ors.push_back(curr);
        }
        else if(readingPerson && curr != "")
        {
            curr = 'P' + curr;
            ors.push_back(curr);
        }
    }
}
void QueryProcessor::notOnly()
{
    bool readingOrgs;
    bool readingPerson;
    bool notInc;
    string tempQ = query;
    string::iterator itr = tempQ.begin();
    notInc = false;
    readingOrgs = readingPerson = false;
    int count = 0;
    int max = tempQ.size();

    //while(itr != tempQ.end() && *itr != '\0')
    while(count < max)
    {
        string curr;
        while(*itr!= ' ' && *itr != '\0')
        {
            curr.push_back(*itr);
            itr++;
            count++;
        }
        if(curr == "ORG")
        {
            readingOrgs = true;
            readingPerson = false;
            curr = "";
        }
        else if(curr == "PERSON")
        {
            readingPerson = true;
            readingOrgs = false;
            curr = "";
        }
        else if(curr == "NOT")
        {
            notInc = true;
            curr = "";
        }
        else
        {
            itr++;
            count++;
        }
        if(notInc)
        {
            if(curr != "")
            {
                if(!readingOrgs && !readingPerson)
                {
                    curr = 'W' + curr;
                    nots.push_back(curr);
                }
                else if(readingOrgs)
                {
                    curr = 'O' + curr;
                    nots.push_back(curr);
                }
                else if(readingPerson)
                {
                    curr = 'P' + curr;
                    nots.push_back(curr);
                }
            }
        }
        else
        {
            if(!readingOrgs && !readingPerson && curr != "")
            {
                curr = 'W' + curr;
                q = curr;
            }
            else if (readingOrgs && curr != "")
            {
                curr = 'O' + curr;
                q = curr;
            }
            else if (readingPerson && curr != "")
            {
                curr = 'P' + curr;
                q = curr;
            }
            curr = "";
        }
    }
}
void QueryProcessor::andNot()
{
    andOnly();
    notOnly();
}
void QueryProcessor::orNot()
{
    orOnly();
    notOnly();
}
vector<string> QueryProcessor::findShared(vector<string>& x, vector<string>& y)
{
    vector<string> synthesized;
    for(int i = 0; i < x.size(); i++)
    {
        string xi = x[i];
        for(int j = 0; j < y.size(); j++)
        {
            string yj = y[j];
            if(xi == yj)
            {
                string a = xi;
                synthesized.push_back(a);
               // cout << "PUSHED" << endl;
            }
        }
    }
    if(synthesized.size() != 0)
    {
        return synthesized;
    }
    else
    {
        return {"NULL VECTOR"};

    }
}

vector<string> QueryProcessor::synthesis(vector<string>& vi, vector<string>& vii)
{
    vector<string> syn;
    for(int i = 0; i < vi.size(); i++)
    {
        syn.push_back(vi[i]);
    }

    for(int j = 0; j < vii.size(); j++)
    {
        bool insert = true;
        string check = vii[j];
        for(int k = 0; k < syn.size(); k++)
        {
            string curr = syn[k];
            if(check == curr)
            {
                insert = false;
               // cout << "already exists" << endl;
            }
        }
        if(insert)
        {
            syn.push_back(check);
        }
    }

    return syn;
}
vector<string> QueryProcessor::exclusion(vector<string>& inc, vector<string>& exc)
{
    vector<string> result;
    for(int i = 0; i < inc.size(); i++)
    {
        bool insert = true;
        string curr = inc[i];
        for(int j = 0; j < exc.size(); j++)
        {
            string notInc = exc[j];
            if(curr == notInc)
            {
                insert = false;
              //  cout << "Omitted " << endl;
                break;
            }
        }
        if(insert)
        {
            result.push_back(curr);
        }
    }

    return result;
}
void QueryProcessor::resetAll()
{
    ands.clear();
    ors.clear();
    nots.clear();
    query.clear();
    q.clear();
    orgs = people = words = hasAnd = hasOr = hasNot = singleQuery = false;
}
char QueryProcessor::classification(string in)
{
    return in[0];
}

