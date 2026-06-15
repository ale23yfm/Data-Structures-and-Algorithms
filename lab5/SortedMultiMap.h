#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


class SortedMultiMap {
	friend class SMMIterator;
    private:
		 

        TElem* info;
        int* left;
        int* right;
        int* parent;
        int root;
        int cap;
        int nrElems;
        int firstEmpty;
        Relation rel;

        //Theta(newCapacity)
        void resize();

        //BC: Theta(1) - the root
        //WC: Theta(nrElems) - degenerate tree
        //AC: Theta(log n)  
        vector<TValue> searchRec(int node, TKey c) const ;
public:
    //Theta)capacity)
    // constructor
    SortedMultiMap(Relation r);

    //BC:Theta(1) - add the root
    //WC:Theta(nrElems) - biggest/smallest element
    //AC:O(nrElems)
	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //BC: Theta(1) - the root
    //WC: Theta(nrElems) - degenerate tree
    //AC: O(log n)
	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //BC:Theta(1) - remove the root
    //WC:Theta(nrElems) - biggest/smallest element
    //AC:O(nrElems)
	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //Theta(1)
    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //Theta(1)
    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    //Theta(1)
    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    //Theta(1)
    // destructor
    ~SortedMultiMap();
};
