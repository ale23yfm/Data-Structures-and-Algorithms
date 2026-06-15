#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	 
	first();
}

void SMMIterator::first(){
	 
	stackTop = -1;
	int current = this->map.root;
	while (current != -1)
	{
		this->stack[++this->stackTop] = current;
		current = this->map.left[current];
	}

	if (this->stackTop != -1)
		this->lastPopped = this->stack[this->stackTop--];
	else
		this->lastPopped = -1;
}

void SMMIterator::next(){
	 
	if (this->lastPopped == -1)
		throw exception();
	int current = this->map.right[this->lastPopped];
	while (current != -1)
	{
		this->stack[++this->stackTop] = current;
		current = this->map.left[current];
	}
	if (this->stackTop != -1)
		this->lastPopped = this->stack[this->stackTop--];
	else
		this->lastPopped = -1;
}

bool SMMIterator::valid() const{
	 
	return this->lastPopped != -1;
}

TElem SMMIterator::getCurrent() const{
	 
	if (this->lastPopped == -1)
		throw exception();
	return this->map.info[this->lastPopped];
}


