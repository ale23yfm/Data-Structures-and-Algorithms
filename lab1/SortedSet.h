#pragma once
//DO NOT INCLUDE SETITERATOR

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef TElem TComp;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TELEM -11111
class SortedSetIterator;


class SortedSet {
	friend class SortedSetIterator;
private:
	//TODO - Representation
	TElem* elements;
	int capacity;
	int len;
	Relation rel;

	//AC:O(n)
	void resize();

public:
	//AC:O(1)
	//constructor
	SortedSet(Relation r);

	//AC:O(n)
	//copy constructor
	SortedSet(const SortedSet& other);

	//AC, WC: Theta(n)
	//BC: Theta(1) - when the sets are already the same
	//assignment operator
	SortedSet& operator=(const SortedSet& other);

	//AC: Theta(n)
	//adds an element to the sorted set
	//if the element was added, the operation returns true, otherwise (if the element was already in the set) 
	//it returns false
	bool add(TComp e);

	//WC, AC: Theta(n)
	//BC: Theta(n) - last element to delete
	//removes an element from the sorted set
	//if the element was removed, it returns true, otherwise false
	bool remove(TComp e);

	//AC: Theta(n)
	//checks if an element is in the sorted set
	bool search(TComp elem) const;

	//AC: Theta(n)
	//returns the number of elements from the sorted set
	int size() const;

	//AC: Theta(1)
	//checks if the sorted set is empty
	bool isEmpty() const;

	//AC: Theta(1)
	//returns an iterator for the sorted set
	SortedSetIterator iterator() const;

	//
	// destructor
	~SortedSet();


};
