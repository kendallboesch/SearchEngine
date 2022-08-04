//
// Created by Kendalll Boesch on 4/18/22.
//

#ifndef INC_22S_FINAL_PROJ_AVLNODE_H
#define INC_22S_FINAL_PROJ_AVLNODE_H
//#include <string>
#include <vector>
template <typename T>
class AVLNode {
public:
    T key;
    std::vector<T> articles;
    AVLNode *left;
    AVLNode *right;
    int height;
    AVLNode( const T& inKey, AVLNode<T>* ln, AVLNode<T>* rn)
    {
        key = inKey;
        left = ln;
        right = rn;
    }

    AVLNode(const T& inKey, T& inId, AVLNode<T>* ln, AVLNode<T>* rn)
    {
        key = inKey;
        articles.push_back(inId);
        left = ln;
        right = rn;
        height = 0;

    }


    ~AVLNode()
    {
        key = "";
        left = nullptr;
        right = nullptr;
        height = 0;
    }
    AVLNode()
    {
        //element = NULL;
        left = right = nullptr;
        height = -1;
    }
    void setData(T& inKey)
    {
        this->key = inKey;
    }
    AVLNode<T>&operator=(const AVLNode<T>& n) const
    {
        this-> key = n.key;
        this->left = n.left;
        this->right = n.right;
        this->height = n.height;

        this->articles.empty();
        for(int i = 0; i < n.articles.size(); i++)
        {
            this->articles.push_back(n.articles[i]);
        }

        return *this;
    }
    AVLNode<T>(const AVLNode<T>& arg)
    {
        this->key = arg.key;
        this->left = arg.left;
        this->right = arg.right;
        this->height = arg.height;

        this->articles.empty();
        for( int i = 0; i < arg.articles.size(); i++)
        {
            this->articles.push_back(arg.articles[i]);
        }
    }
    void addId( T& inId)
    {
        this->articles.push_back(inId);
    }
    bool operator==(const AVLNode<T>& t) const
    {
        return(this->key == t.key);
    }
    bool operator>(const AVLNode<T>& t) const
    {
        return this->key > t.key;
    }
    bool operator<(const AVLNode<T>& t) const
    {
        return this->key < t.key;
    }
    T& getKey()
    {
        return this->key;
    }
    void setKey(T& inKey)
    {
        this->key = inKey;
    }
    void setArticles(std::vector<T> &temp){
        for(int i =0; i< temp.size();i++){
            articles.push_back(temp[i]);
        }
    }
std::vector<T> getArticles(){
    return this->articles;
    }

};

#endif //INC_22S_FINAL_PROJ_AVLNODE_H
