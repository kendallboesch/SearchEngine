//
// Created by Akul & Kendall on 4/25/2022.
//
//https://www.codezclub.com/cpp-hash-table-using-template-class/
#ifndef DSHASHTABLE_DSHASHTABLE_H
#define DSHASHTABLE_DSHASHTABLE_H
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

template <class E, class K>
class DSHashTable {
public:
    DSHashTable(int divisor = 11);
    ~DSHashTable();
    int Search(const K& k, E& e) const;
    DSHashTable<E,K>& Insert(const E& e);
    void Output();
    void del(E e);

private:
    int hSearch(const K& k) const;
    int D; // hash function divisor
    E *ht; // hash table array
    int *empty; //1D array

};

template<class E, class K>
DSHashTable<E, K>::DSHashTable(int divisor) {//constructor
    D = divisor;
    ht = new E[D];
    empty = new int [D];

    for(int i = 0; i < D; i++){
        empty[i] = 1;
    }

}

template<class E, class K>
DSHashTable<E, K>::~DSHashTable() {
    delete [] ht;
}

template<class E, class K>
int DSHashTable<E, K>::Search(const K &k, E &e) const {
    int b = hSearch(k);
    if(empty[b] ||  ht[b] != k){
        return 0;
    }
    e = ht[b];
    return 1;
}

template<class E, class K>
DSHashTable<E, K> &DSHashTable<E, K>::Insert(const E &e) {
    K k = e;//extract key
    int b = hSearch(k);
    if(empty[b]){
        empty[b] = 0;
        ht[b] = e;
        return *this;
    }
    if(ht[b] == k){cout << "\nbad input"; return *this;}//duplicate
    cout << "\nNo memory";//table full
    return *this;
}

template<class E, class K>
void DSHashTable<E, K>::Output() {
    cout << endl;
    for( int i = 0; i < D; i++){
        if(empty[i]) cout << "0 ";
        else cout << ht[i] << " ";
    }
    cout << endl;
}

template<class E, class K>
void DSHashTable<E, K>::del(E e) {
    int b = hSearch(e);
    if(!empty[b] && ht[b] == e){
        ht[b] = 0;
        empty[b] =1;
    }
    else
        cout << "\nelement not found";
}

template<class E, class K>
int DSHashTable<E, K>::hSearch(const K &k) const {
    int i = k % D;
    int j = 1;
    do{
        if(empty[j] || ht[j] == k) return j;
        j = (j + 1) % D; // next bucket
    }while(j != i);//returned hme?
    return j; //table is full
}

class  element {
public:
    operator long() const{return key;}

private:
    int data;
    long key;
};

#endif //DSHASHTABLE_DSHASHTABLE_H