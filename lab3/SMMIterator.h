#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	//TODO - Representation
	int current;
public:
	//AC= Theta(1)
	void first();
	//AC= Theta(1)
	void next();
	//AC= Theta(1)
	bool valid() const;
	//AC= Theta(1)
   	TElem getCurrent() const;
};

