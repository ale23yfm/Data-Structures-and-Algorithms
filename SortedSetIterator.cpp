#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	this->currentPos = 0;
}

void SortedSetIterator::first() {
	this->currentPos = 0;
}

void SortedSetIterator::next() {
	if (!valid())
		throw exception();
	this->currentPos++;
}

TElem SortedSetIterator::getCurrent()
{
	if (!valid())
		throw exception();
	return this->multime.elements[this->currentPos];
}

bool SortedSetIterator::valid() const {
	return this->currentPos < this->multime.len;
}

