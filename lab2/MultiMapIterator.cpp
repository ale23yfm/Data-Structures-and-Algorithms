#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	first();
}

TElem MultiMapIterator::getCurrent() const{
	if (!valid())
		throw exception();
	return TElem(currentKey->key, currentValue->value);
}

bool MultiMapIterator::valid() const {
	return currentKey != nullptr && currentValue != nullptr;
}

void MultiMapIterator::next() {
	if (!valid())
		throw exception();

	if (currentValue->next != nullptr)
		currentValue = currentValue->next;
	else
	{
		currentKey = currentKey->next;
		if (currentKey == nullptr)
			currentValue = nullptr;
		else
			currentValue = currentKey->valuesHead;	
	}
}

void MultiMapIterator::first() {
	currentKey = col.head;
	if (currentKey == nullptr)
		currentValue = nullptr;
	else
		currentValue = currentKey->valuesHead;
}

