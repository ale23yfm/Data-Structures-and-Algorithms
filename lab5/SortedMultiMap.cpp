#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

void SortedMultiMap::resize()
{
    int newCap = this->cap * 2;
    TElem* newArray = new TElem[newCap];
    int* newLeft = new int[newCap];
    int* newRight = new int[newCap];
    int* newParent = new int[newCap];

    //copying
    for (int i = 0; i < this->cap; i++)
    {
        newArray[i] = this->info[i];
        newLeft[i] = this->left[i];
        newRight[i] = this->right[i];
        newParent[i] = this->parent[i];
    }
    int i;
    for(i = this->cap; i < newCap-1; i++)
    {
        newLeft[i] = i + 1;
        newRight[i] = -1;
        newParent[i] = -1;
    }
    newLeft[i] = -1;
    newRight[i] = -1;
    newParent[i] = -1;

    delete[] this->info;
    delete[] this->left;
    delete[] this->right;
    delete[] this->parent;

    this->info = newArray;
    this->left = newLeft;
    this->right = newRight;
    this->parent = newParent;
    this->firstEmpty = this->cap;
    this->cap = newCap;
}

SortedMultiMap::SortedMultiMap(Relation r) {
    this->root = -1;
    this->cap = 10;
    this->nrElems = 0;
    this->firstEmpty = 0;
    this->rel = r;

    this->info = new TElem[this->cap];
    this->left = new int[this->cap];
    this->right = new int[this->cap];
    this->parent = new int[this->cap];
    int i;
    for (i = 0; i < this->cap - 1; i++)
    {
        this->left[i] = i + 1;
        this->right[i] = -1;
        this->parent[i] = -1;
    }

    this->left[i] = -1;
    this->right[i] = -1;
    this->parent[i] = -1;
}

void SortedMultiMap::add(TKey c, TValue v) {
     
    if (this->cap == this->nrElems)
        resize();

    int newNode = this->firstEmpty;
    this->info[newNode] = { c,v };
    this->firstEmpty = this->left[this->firstEmpty];
    this->left[newNode] = -1;
    this->right[newNode] = -1;
    this->parent[newNode] = -1;
    this->nrElems++;

    if (this->root == -1)
    {
        this->root = newNode;
        return;
    }

    int current = this->root;
    while (true)
        if (rel(c, this->info[current].first))
        {
            //go left
            if (this->left[current] == -1)
            {
                this->left[current] = newNode;
                this->parent[newNode] = current;
                return;
            }
            current = this->left[current];
        }
        else {
            //go right
            if (this->right[current] == -1)
            {
                this->right[current] = newNode;
                this->parent[newNode] = current;
                return;
            }
            current = this->right[current];
        }
}

vector<TValue> SortedMultiMap::searchRec(int node, TKey c) const
{
    vector<TValue> res;
    if (node == -1)
        return vector<TValue>();
    else
    {
        if (this->info[node].first == c)
        {
            res.push_back(this->info[node].second);
            vector<TValue> rest = searchRec(this->left[node], c);
            res.insert(res.end(), rest.begin(), rest.end());
            return res;
        }
        if (this->rel(c, this->info[node].first))
            return searchRec(this->left[node], c);
        else return searchRec(this->right[node], c);
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
	 
    return this->searchRec(this->root, c);
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	//search for the node
    int current = this->root;
    while (current != -1)
    {
        if (this->info[current].first == c && this->info[current].second == v)
            break;
        if (this->rel(c, this->info[current].first))
            current = this->left[current];
        else
            current = this->right[current];
    }
    if (current == -1)
        return false;

    //Remove
    if (this->left[current] == -1 && this->right[current] == -1)
    {
        //set it to NIL
        if (this->parent[current] == -1)//root
            this->root = -1;
        else if (current == this->left[this->parent[current]])
            this->left[this->parent[current]] = -1; 
        else
            this->right[this->parent[current]] = -1;
        this->info[current] = { -1,-1 };
        this->left[current] = this->firstEmpty;
        this->firstEmpty = current;
        this->nrElems--;
        return true;
    }
    //one child
    else if (this->left[current] == -1 || this->right[current] == -1)
    {
        int child;
        //skip it
        if (this->left[current] != -1)
            child = this->left[current];
        else child = this->right[current];

        if (this->parent[current] == -1)//root
            this->root = child;

        else if (current == this->left[this->parent[current]])
                this->left[this->parent[current]] = child;
            else
                this->right[this->parent[current]] = child;
        this->left[current] = this->firstEmpty;
        this->parent[child] = this->parent[current];
        this->firstEmpty = current;
        this->nrElems--;        
        return true;
    }
    //2 children
    else 
    {
        //replace with the predecessor
        int pred = this->left[current];
        while (this->right[pred] != -1)
            pred = this->right[pred];

        this->info[current] = this->info[pred];
            
        int predChild = this->left[pred];

        if (this->left[this->parent[pred]] == pred)
            this->left[this->parent[pred]] = predChild;
        else 
            this->right[this->parent[pred]] = predChild;

        if (predChild != -1)
            this->parent[predChild] = this->parent[pred];

        this->left[pred] = this->left[current];
        this->firstEmpty = current;
        this->nrElems--;
        return true;
    }
}


int SortedMultiMap::size() const {
	return this->nrElems;
}

bool SortedMultiMap::isEmpty() const {
	return this->nrElems == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	 
    delete[] this->info;
    delete[] this->left;
    delete[] this->right;
    delete[] this->parent;
}
