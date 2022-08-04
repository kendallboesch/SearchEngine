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
 *      * DocumentParser()
 *      * ~DocumentParser()
 *      * void loadStopWords()
 *      * string fileManip(string&)
 *      * vector<string> getPersons(const string&)
 *      * vector<string> getOrgs(const string&)
 *      * string removeStopWords(const string&)
 *      * string stemText(const string&)
 *      * string stemTextII(const string&)
 *      * string removePunc(const string&)
 *      * bool isPunct(const char&)
 *      * bool isNum(const chat&)
 *
 ***************/
#include "DocumentParser.h"
#include "include/rapidjson/document.h"


/****************
 * Default Constructor
 *
 ****************/
DocumentParser::DocumentParser()
{
    this->loadStopWords();
    //this->loadNonStemWords();
}
/*******
 * Destructor
 *
 */
DocumentParser::~DocumentParser()
{

}
/************
 *     LOAD STOP WORDS
 *
 *     Reads in stop word file and pushes
 *     back each word read to the stopWord
 *     vector (<string>) used later for parsing
 *
 */
void DocumentParser::loadStopWords()
{
    // CREATE STREAM OBJECT
    ifstream inStop;
    // OPEN STOP WORDS FILE
    inStop.open("stopWords.txt");

    // IF THE FILE IS OPEN
    if(inStop.is_open())
    {
        cout << " STOP WORDS OPENED" << endl;

        // CHAR TO READ IN STOP WORDS
        char readIn[50];

        // WHILE HAVE NOT REACHED THE END OF THE FILE
        int c = 0;
       while(!inStop.eof())
        {
            // READ IN ANOTHER LINE
            inStop.getline(readIn, 50);
            // ADD READ IN STOP WORD TO THE STOPWORDS VECTOR
            stopWords.push_back(readIn);

        }
    }
    else
    {
        cout << "FAILED TO OPEN STOP WORD FILE" << endl;
    }
}

/***********
 *      FILE MANIP
 *
 *   opens .json document, name passed through
 *   as stinrg filename. reads in entire file
 *   and parses into sections. extracts the text
 *   (content) portion of the article and optimizes
 *   the text by removing stopwords & stemming.
 *   returns the optimized text as one long string
 *
 * @param fName
 *
 */
string DocumentParser::fileManip(const string& fName)
{
        // JSON FILE
    rapidjson::Document doc;

    // INITIALIZE FILE STREAM
    ifstream streamy (fName);

    // PUT THE WHOLE FILES DATA INTO WHOLE FILE
    string wholeFile;
    string temp;
    // WHILE THE FILE IS STILL BEING READ IN
    while(getline(streamy,temp))
    {
        wholeFile+= temp;
    }
    // CLOSE FILE
    streamy.close ();

    // CALL PARSE ON THE WHOLE FILE AS A C STR
    doc.Parse (wholeFile.c_str());

    // EXTRACT "TEXT" FROM DOC & CREATE STRING
    string unparsedText = doc["text"].GetString();
    // PARSE THE TEXT BY STEMMING & REMOVING STOP WORDS
    string parsed = stemText(unparsedText);
    // RETURN PARSED TEXT  VECTOR
    return parsed;
}
/***********
 *  GET PERSONS
 *
 * opens .json document, name passed through
 *   as stinrg filename. reads in entire file
 *   and parses into sections. Locates the
 *   array of persons associated with the inputed
 *   article name and creates a vector of each name.
 *   returns the vector of associated persons
 *
 * @param fName
 * @return
 */
vector<string> DocumentParser::getPersons(const string & fName)
{
    // JSON DOC OBJECT
    rapidjson::Document doc;

    // INITIALIZE STREAM
    ifstream streamy (fName);

    // COLLECT ALL DATA FROM FILE
    string wholeFile;
    string temp;
    string contents;
    while(getline(streamy,temp))
    {

        wholeFile+= temp;
    }
    streamy.close ();

    // CALL PARSE ON STRING
    doc.Parse (wholeFile.c_str());

    // VECTOR TO HOLD ALL ASSOCIATED PERSONS
    vector<string> persons;

    // ITERATE THORUGH THE ARRAY OF ASSOCIATED PERSONS
    for(auto &current : doc["entities"]["persons"].GetArray())
    {

        // RETRIEVE NAMES OF EACH PERSON
        string name = current["name"].GetString();
                if(name.find(' ') != variant_npos)
        {
            int indSp = name.find(' ');
            string first = name.substr(0, indSp - 1);
            string last = name.substr(indSp + 1);
            persons.push_back(first);
            persons.push_back(last);
        }
        else
        {
            // PUSH BACK TO PERSONS VECTOR
            persons.push_back(name);
        }
    }
    // RETURN VECTOR OF ASSOCIATED PERSONS
    return persons;
}
/*******************
 *      GET ORGS
 *
 *  opens .json document, name passed through
 *   as stinrg filename. reads in entire file
 *   and parses into sections. Locates the
 *   array of organiations associated with the inputed
 *   article name and creates a vector of each org.
 *   returns the vector of associated organizations
 *
 * @param fName
 * @return
 */
vector<string> DocumentParser::getOrgs(const string & fName)
{
    // JSON DOCUMENT OBJECT
    rapidjson::Document doc;

    // INITIALIZE INPUT FILE
    ifstream streamy (fName);

    // RETRIEVE DATA FROM WHOLE FILE, SAVE IN STRING WHOLE FILE
    string wholeFile;
    string temp;
    string contents;
    while(getline(streamy,temp))
    {
        wholeFile+= temp;
    }
    streamy.close ();

    // CALL PARSE ON STRING
    doc.Parse (wholeFile.c_str());
    // make sure the parsing worked

    // VECTOR TO HOLD ASSOCIATED ORGS
    vector<string> orgs;

    // ITERATE THROUGH THE ORGANIZATION ARRAY
    for(auto &current : doc["entities"]["organizations"].GetArray())
    {
        // SAVE THE ORGANIZATION AS AS STRING
        string name = current["name"].GetString();
        // PUSH SAVED STRING ORG TO ORG VECTOR
        if(name.find(' ') == variant_npos)
        {
            orgs.push_back(name);
        }
        else
        {
            name = name.substr(0, name.find(' ') - 1);
            orgs.push_back(name);
        }
    }

    // RETURN ORGANIZATION VECTOR
    return orgs;
}
/*****************
 *      REMOVE STOP WORDS
 *
 *      takes in text and iterates thorugh
 *      stopword array removing each instacne
 *      of each stop word, then returns the text
 *      with all stopwords removed
 *
 * @param textIn
 * @return
 */
string DocumentParser::removeStopWords(const string& textIn)
{
    // MUTABLE COPY OF TEXT IN
    string text = textIn;

    // ITERATE THROUGH VECTOR OF STOPWORDS
    for(int i = 0; i < stopWords.size(); i++)
    {
        string sw = " " + stopWords[i];
        // IF THE STOP WORD IS LOCATED IN THE TEXT
        if( textIn.find(sw) != variant_npos)
        {
            // WHILE THE STOP WORD IS LOCATED IN THE TEXT
            while(text.find(sw) != variant_npos)
            {

                int removalIndex = text.find(sw);
                int removalLength = sw.size();
                string replacement = " ";
                // REPLACE THE STOP WORD WITH A SPACE
                text.replace(removalIndex, removalLength, replacement);
            }
        }
    }
    // RETURN TEXT WITH STOPWORDS REMOVED
    return text;
}
/********
 *      STEM TEXT
 *
 *      removes punctuation and stop words then
 *      sends optimized text to stemTextII for
 *      stemming. Returns the stemmed text
 *
 * @param tIn
 * @return
 */
string DocumentParser::stemText(const string& tIn)
{
    // MUTABLE COPY OF TIN
    string t = tIn;
    // REMOVE PUNCTUATION
    string noPunc = this->removePunc(t);
    // REMOVE STOPWORDS
   // string noStop = this->removeStopWords(noPunc);
    // STEM TEXT
    string stemmed = this->stemTextIII(noPunc);

    // RETURN STEMMED TEXT
    return stemmed;
}
/*******8*****
 *      STEM TEXT II
 *
 *    Iterate through text passed in. Locates
 *    words longer than three chars and passes
 *    them to be stemmed by imported library
 *    Porter2Stemmer. Then creates a new long string
 *    of all of the stemmed words in the text.
 *    Returns the stemmed text
 *
 *
 * @param textIn
 * @return
 */
string DocumentParser::stemTextII(const string& textIn)
{
    int len = textIn.size();
    int counter = 1;
    string text = textIn;       // MUTABLE COPY OF TEXT DATA
    string::iterator itr;       // ITERATOR
    string parsed = "";         // WILL HOLD STEMMED TEXT
    itr = text.begin();         // SET ITERATOR TO FIRST CHAR
    string curr = "";
    while(counter < len)      // WHILE THE ITERATOR HAS NOT REACHED THE END OF THE TEXT
    {
            // CURR WILL HOLD THE WORD BEING STEMMED
            // WHILE THE ITERATOR IS NOT ON A SPACE

            curr = "";
        while(*itr != ' ' && *itr != '\0')
        {
            if(!isPunct(*itr) && !isNum(*itr))
            {
                char c = *itr;
                c = tolower(c);
                // PUSH THE CHAR BACK TO THE CURR WORD
                curr.push_back(c);
            }
            itr++;
            counter++;
        }
        if(curr.size() >= 3) // IF THE SIZE OF CURR IS GREATER THAN OR EQUAL TO 3
        {
                Porter2Stemmer::stem(curr);

            if (curr.size() >= 3)
            {
                if(!allSpace(curr) && curr.find('\'') == variant_npos && curr.find('\"') == variant_npos)
                {
                    curr = ' ' + curr;
                    //cout << curr;
                    // ADD CURR TO THE PARSED WORDS
                    parsed = parsed + curr;
                }
            }

            curr.empty();
        }
        // INCREMENT ITERATOR
        itr++;
        counter++;

        curr.empty();
    }
    return parsed;
}
string DocumentParser::stemTextIII(const string& inp)
{
    string t = inp;
    int pos = 0;
    string curr = "";
    string parsed = "";
    while((pos = t.find(' ')) != string::npos)
    {
        curr = t.substr(0, pos);
        char * f;
        vector<string>::iterator itr = find(stopWords.begin(), stopWords.end(), curr);
        if(curr.size() > 3 && itr == stopWords.end())
        {

            Porter2Stemmer::stem(curr);
            if(!allSpace(curr) && curr.find('\"') == string::npos)
            {
                parsed = parsed + ' ' + curr;
            }
        }
        t.erase(0, pos + 1);
        curr = "";

    }
    return parsed;
}
// STEMMING HELPER FUNCTIONS
/**********
 *
 * @param in
 * @return
 */
bool DocumentParser::isMonthOrDay(const string & in)
{
    for(int i = 0; i < nonStem.size(); i++)
    {
        if (in == nonStem[i])
        {
            return true;
        }
    }
    return false;
}
/********
 *  IS PUNCT
 *
 *  checks if the character passed
 *  in is a punctuation mark.
 *  Returns true or false
 *
 * @param c
 * @return
 */
bool DocumentParser::isPunct(const char& c)
{
    char* puncs = "'!@#$%^&'\"'*().<>/|?,;:-_'\'";

    for(int i = 0; i < strlen(puncs); i++)
    {
        if(c == puncs[i])
        {
            return true;
        }
    }
    return false;
}
/**********
 *      IS NUM
 *
 *     Checks if the character passed in is
 *     an integer. Returns true or false
 *
 * @param c
 * @return
 */
bool DocumentParser::isNum(const char& c)
{
    char* nums = "1234567890";
    for(int i = 0; i < strlen(nums); i++)
    {
        if (c == nums[i])
        {
            return true;
        }
    }
    return false;
}
/******************
 *      REMOVE PUNCT
 *
 *   Iterates through string passed in creating
 *   a new string that replaces all numbers and
 *   punctuation marks with spaces
 *
 * @param tIn
 * @return
 */
string DocumentParser::removePunc(const string& tIn)
{
    // MUTABLE COPY OF STRING PASSED IN
    string t = tIn;
    // ITERATOR TO MOVE THROUGH STRING
    string::iterator itr;
    itr = t.begin();
    string r = "";

    // WHILE THE ITERATOR HAS NOT REACHED THE END OF THE STRING
    while (itr!= t.end())
    {
        // IF THE CHAR @ ITERATOR IS PUNCTUATION OR NUMBER
        if(isPunct(*itr) || isNum(*itr))
        {
            // REPLACE WITH SPACE
            r.push_back(' ');
        }
        else
        {
            // ADD THE CHAR TO THE STRING BEING BUILT
            r.push_back(*itr);
        }
        // INCREMENT ITERATOR
        itr++;
    }

    return r;
}
bool DocumentParser::allSpace(const string &  in)
{
        for(int i = 0; i < in.size(); i++)
        {
            if(in[i] != ' ')

            {
                return false;
            }
        }
        return true;
}
string DocumentParser::articleName(const string& fName)
{
    // JSON FILE
    rapidjson::Document doc;

    // INITIALIZE FILE STREAM
    ifstream streamy (fName);

    // PUT THE WHOLE FILES DATA INTO WHOLE FILE
    string wholeFile;
    string temp;
    // WHILE THE FILE IS STILL BEING READ IN
    while(getline(streamy,temp))
    {
        wholeFile+= temp;
    }
    // CLOSE FILE
    streamy.close ();

    // CALL PARSE ON THE WHOLE FILE AS A C STR
    doc.Parse (wholeFile.c_str());

    // EXTRACT "TEXT" FROM DOC & CREATE STRING
    string title = doc["title"].GetString();
    string site = doc["url"].GetString();
   // string retVal = title + ": " + site;
    // PARSE THE TEXT BY STEMMING & REMOVING STOP WORDS
    //string parsed = stemText(unparsedText);
    // RETURN PARSED TEXT  VECTOR
    string retVal = title + '\n' + site;
    return retVal;
}

