#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	 
	int stack[1000];
	int stackTop;
	int lastPopped;

public:
	//WC:Theta(n) - degenerate 
	//AC/BC:Theta(log n) 
	void first();

	//WC:Theta(log n) 
	//AC:Theta(1) - pop out 
	//BC:O(n)
	void next();

	//Theta(1)
	bool valid() const;

	//Theta(1)
   	TElem getCurrent() const;
};

