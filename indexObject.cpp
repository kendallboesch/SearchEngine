//
// Created by Kendalll Boesch on 4/13/22.
//

#include "indexObject.h"

indexObject::indexObject()
{

}
indexObject::indexObject(const string keyIn)
{
    key = keyIn;
}
indexObject::~indexObject()
{

}
string indexObject::getKey()
{
    return key;
}
void indexObject::setKey(string keyIn)
{
    key = keyIn;
}
vector<string>& indexObject::getArticles()
{
    return foundOn;
}