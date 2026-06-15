#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;

	int currentPos;
	MultiMap::Node* currentNode;

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	//Theta(1);
	TElem getCurrent()const;

	//Theta(1);
	bool valid() const;

	//O(n)
	void next();

	//BC: Theta(1)
	//WC: Theta(n)
	//AC: O(n)
	void first();
};

