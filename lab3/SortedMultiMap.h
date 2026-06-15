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
		//TODO - Representation
        TElem* elems;
        int* next;
        Relation rel;
        int capacity;
        int length;
        int head;
        int firstEmpty;

        //BC = WC = AC = Theta(n)
        //resize
        void resize();

    public:

    //BC = WC = AC = Theta(n)
    // constructor
    SortedMultiMap(Relation r);

    //BC = WC = AC = Theta(n)
    // copy constructor
    SortedMultiMap(const SortedMultiMap& other);

    //BC = Theta(1) - first element
    //WC = Theta(n) - resizing/last element
    //AC = O(n) 
	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //BC = Theta(1) - first element
    //WC = Theta(n) - last element
    //AC = O(n)
	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //BC = Theta(1) - first element
    //WC = Theta(n) - last element
    //???????????????????????????????????????//AC = O(n) din cauza ca e while care la un moment dat se opreste, poate fi si 0 si 1 si n si 43567----------???????????????????????????????
	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //BC = WC = AC = Theta(1)
    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //BC = WC = AC = Theta(1)
    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    //BC = WC = AC = Theta(1)
    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    //BC = WC = AC = Theta(1)
    // destructor
    ~SortedMultiMap();
};
