#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


MultiMap::MultiMap() {
	this->head = nullptr;
	this->tail = nullptr;
	length = 0;
}


void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	MultiMap::KeyNode* current = head;
	while (current != nullptr && current->key != c)
			current = current->next;
	if (current == nullptr)
	{
		//new node
		MultiMap::KeyNode* newKey = new MultiMap::KeyNode;
		newKey->key = c;
		newKey->valuesHead = nullptr;
		newKey->valuesTail = nullptr;
		newKey->next = nullptr;
		newKey->prev = tail;

		if (tail == nullptr)
		{
			head = newKey;
			tail = newKey;
		}
		else
		{
			tail->next = newKey;
			newKey->prev = tail;
			tail = newKey;
			tail->next = nullptr;
		}
		current = newKey;
	}
	//new value
	MultiMap::ValueNode* newValue = new MultiMap::ValueNode;
	newValue->value = v;
	newValue->next = nullptr;
	newValue->prev = current->valuesTail;

	if (current->valuesTail == nullptr)
	{
		current->valuesHead = newValue;
		current->valuesTail = newValue;
	}
	else
	{
		current->valuesTail->next = newValue;
		current->valuesTail = newValue;
	}
	length++;
}


bool MultiMap::remove(TKey c, TValue v) {
	MultiMap::KeyNode* currentKey = head;
	while (currentKey != nullptr && currentKey->key != c)
		currentKey = currentKey->next;
	//no key
	if (currentKey == nullptr) return false;
	//got the key => parse the values
	MultiMap::ValueNode* currentValue = currentKey->valuesHead;
	while (currentValue != nullptr && currentValue->value != v)
		currentValue = currentValue->next;
	//the key does not have this value
	if (currentValue == nullptr) return false;
	//got the value
	//only one value
	if (currentKey->valuesHead == currentKey->valuesTail)
	{
		delete currentValue;
		currentKey->valuesHead = nullptr;
		currentKey->valuesTail = nullptr;
		length--;
		if (currentKey == head) head = currentKey->next;
		if (currentKey == tail) tail = currentKey->prev;
		if (currentKey->prev) currentKey->prev->next = currentKey->next;
		if (currentKey->next) currentKey->next->prev = currentKey->prev;
		delete currentKey;
		return true;
	}
	//remove head
	else if (currentValue == currentKey->valuesHead)
	{
		MultiMap::ValueNode* nextValue = currentValue->next;
		currentKey->valuesHead = nextValue;
		nextValue->prev = nullptr;
		delete currentValue;
		length--;
		return true;
	}
	//remove tail
	else if (currentValue == currentKey->valuesTail)
	{
		currentKey->valuesTail = currentValue->prev;
		currentKey->valuesTail->next = nullptr;
		delete currentValue;
		length--;
		return true;
	}
	//remove from the middle
	currentValue->prev->next = currentValue->next;
	currentValue->next->prev = currentValue->prev;
	delete currentValue;
	length--;
	return true;
}


vector<TValue> MultiMap::search(TKey c) const {
	MultiMap::KeyNode* currentKey = head;
	while (currentKey != nullptr && currentKey->key != c)
		currentKey = currentKey->next;
	if (currentKey == nullptr)
		return vector<TValue>();

	MultiMap::ValueNode* currentValue = currentKey->valuesHead;
	vector<TValue> result;
	while (currentValue != nullptr)
	{
		result.push_back(currentValue->value);
		currentValue = currentValue->next;
	}
	return result;
}


int MultiMap::size() const {
	return length;
}


bool MultiMap::isEmpty() const {
	return length == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


MultiMap::~MultiMap() {
	MultiMap::KeyNode* currentKey = head;
	while (currentKey != nullptr)
	{
		MultiMap::ValueNode* currentValue = currentKey->valuesHead;
		while (currentValue != nullptr)
		{
			MultiMap::ValueNode* nextValue = currentValue->next;
			delete currentValue;
			currentValue = nextValue;
		}
		MultiMap::KeyNode* nextKey = currentKey->next;
		delete currentKey;
		currentKey = nextKey;
	}
	head = nullptr;
	tail = nullptr;
	length = 0;
}

