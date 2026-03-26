#pragma once
#include "SortedSet.h"

//DO NOT CHANGE THIS PART
class SortedSetIterator
{
	friend class SortedSet;
private:
	const SortedSet& multime;
	SortedSetIterator(const SortedSet& m);

	//TODO - Representation
	int currentPos;
public:
	//Theta(1)
	void first();

	//Theta(1)
	void next();

	//Theta(1)
	TElem getCurrent();

	//Theta(1)
	bool valid() const;
};

