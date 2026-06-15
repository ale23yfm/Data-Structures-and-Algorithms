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
	struct ValueNode {
		TValue value;
		ValueNode* next;
		ValueNode* prev;
	};

	struct KeyNode {
		TKey key;
		ValueNode* valuesHead;
		ValueNode* valuesTail;
		KeyNode* next;
		KeyNode* prev;
	};

	KeyNode* head;
	KeyNode* tail;
	int length;
	
public:
	//constructor
	//Tetha(1)
	MultiMap();

	//adds a key value pair to the multimap
	//BC: Tetha(1) - first value
	//AC/WC: Tetha(k)
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	//BC: Tetha(1) - first value
	//AC/WC: Tetha(k+v)
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	//BC: Tetha(1) - first value
	//AC/WC: Tetha(k+v)
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	//Tetha(1)
	int size() const;

	//checks whether the multimap is empty
	//Tetha(1)
	bool isEmpty() const;

	//returns an iterator for the multimap
	//Tetha(1)
	MultiMapIterator iterator() const;

	//descturctor
	//Tetha(k+v)
	~MultiMap();


};

