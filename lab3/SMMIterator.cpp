#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	first();
}

void SMMIterator::first(){
	//TODO - Implementation
	this->current = this->map.head;
}

void SMMIterator::next(){
	if (!valid())
		throw exception();
	this->current = this->map.next[current];
}

bool SMMIterator::valid() const{
	return current != -1;
}

TElem SMMIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return this->map.elems[current];
}


