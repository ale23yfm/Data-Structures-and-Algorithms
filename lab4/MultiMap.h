#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)
class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

private:
	struct Node
	{
		TElem data;
		Node* next;
	};

	Node** table;
	int nrElems;
	int capacity;
	double alpha;

	//Theta(1)
	int hash(TKey key) const;
	
	//Theta(nrElems)
	void resize();

public:
	//constructor
	//Theta(n)
	MultiMap();

	//adds a key value pair to the multimap
	//WC: Theta(nrElems) - resize
	//AC: Theta(1)
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	//WC: Theta(nrElems)
	//BC: Theta(1)
	//AC: O(nrElems)
	bool remove(TKey c, TValue v);

	//WC: Theta(nrElems)
	//BC: Theta(1)
	//AC: O(nrElems)
	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	//AC: Theta(1)
	int size() const;

	//checks whether the multimap is empty
	//AC: Theta(1)
	bool isEmpty() const;

	//returns an iterator for the multimap
	//AC: Theta(1)
	MultiMapIterator iterator() const;

	//descturctor
	//AC: Theta(nrElems)
	~MultiMap();
};

