#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;


int MultiMap::hash(TKey key) const
{
	return abs(key) % this->capacity;
}

void MultiMap::resize()
{
	int cap = this->capacity;
	this->capacity *= 2;
	Node** newTable = new Node * [this->capacity];
	for (int i = 0; i < this->capacity; i++) //Theta(capacity)
		newTable[i] = nullptr;
	for (int i = 0; i < cap; i++) //Theta(cap)
	{
		Node* current = this->table[i];
		while (current != nullptr) // Theta(nrElems)
		{
			Node* nextNode = current->next;
			int h = this->hash(current->data.first); 
			current->next = newTable[h];  
			newTable[h] = current;
			current = nextNode;
		}
	}
	delete[] this->table;
	this->table = newTable;
}

MultiMap::MultiMap() {
	this->capacity = 10;
	this->nrElems = 0;
	this->alpha = 0.7;
	this->table = new Node*[this->capacity];
	for (int i = 0; i < this->capacity; i++)
		this->table[i] = nullptr;
}

void MultiMap::add(TKey c, TValue v) {
	if ((double)this->nrElems / this->capacity > this->alpha)
		this->resize();
	int h = hash(c);
	Node* newNode = new Node;
	newNode->data.first = c;
	newNode->data.second = v;
	newNode->next = table[h];
	table[h] = newNode;
	this->nrElems++;
}

bool MultiMap::remove(TKey c, TValue v) {
	int h = hash(c);
	Node* prev = nullptr;
	Node* current = table[h];
	if (table[h] == nullptr)
		return  false;
	while (current != nullptr)
	{
		if (current->data.first == c && current->data.second == v)
		{
			if (prev == nullptr) //head
				table[h] = current->next;
			else //skip this node
				prev->next = current->next;
			delete current;
			this->nrElems--;
			return true;
		}
		prev = current;
		current = current->next;
	}
	return false;
}

vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> res;
	int h = hash(c);
	Node* current = table[h];
	while (current != nullptr)
		{
			if (current->data.first == c)
				res.push_back(current->data.second);
			current = current->next;
		}
	return res;
}

int MultiMap::size() const {
	return this->nrElems;
}

bool MultiMap::isEmpty() const {
	return this->nrElems == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

MultiMap::~MultiMap() {
	for (int i = 0; i < this->capacity; i++)
	{
		Node* current = this->table[i];
		while (current != nullptr)
		{
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		}
	}
	delete[] this->table;
}

