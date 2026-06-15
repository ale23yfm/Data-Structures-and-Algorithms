#include "MultiMapIterator.h"
#include "MultiMap.h"

MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	first();
}

TElem MultiMapIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return this->currentNode->data;
}

bool MultiMapIterator::valid() const {
	return this->currentPos < this->col.capacity && this->currentNode != nullptr;
}

void MultiMapIterator::next() {
	if (!valid())
		throw exception();
	if (this->currentNode->next != nullptr)
		this->currentNode = this->currentNode->next;
	else
	{
		this->currentPos++;
		while (this->valid() && this->col.table[this->currentPos] == nullptr)
			this->currentPos++;
		if (!this->valid())
		{
			this->currentNode = nullptr;
		}
		else this->currentNode = this->col.table[this->currentPos];
	}
}

void MultiMapIterator::first() {
	currentNode = nullptr;
	this->currentPos = 0;
	for (int i = 0; i < this->col.capacity; i++)
		if (this->col.table[i] != nullptr)
		{
			this->currentPos = i;
			this->currentNode = this->col.table[i];
			break;
		}
}