#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
	this->capacity = 10;
	this->length = 0;
	this->head = -1;
	this->firstEmpty = 0;
	this->elems = new TElem[this->capacity];
	this->next = new int[this->capacity];
	this->rel = r;

	for (int i = 0; i < this->capacity-1; i++)
		this->next[i] = i + 1;
	this->next[this->capacity-1] = -1;
}

SortedMultiMap::SortedMultiMap(const SortedMultiMap& other)
{
	this->capacity = other.capacity;
	this->length = other.length;
	this->head = other.head;
	this->firstEmpty = other.firstEmpty;
	this->elems = new TElem[this->capacity];
	this->next = new int[this->capacity];
	this->rel = other.rel;

	for (int i = 0; i < this->capacity; i++)
	{
		this->elems[i].first = other.elems[i].first;
		this->elems[i].second = other.elems[i].second;
		this->next[i] = other.next[i];
	}
}

void SortedMultiMap::resize()
{
	TElem* aux = new TElem[this->capacity * 2];
	int* auxNext = new int[this->capacity *2];
	for (int i = 0; i < this->capacity; i++)
	{
		aux[i].first = this->elems[i].first;
		aux[i].second = this->elems[i].second;
		auxNext[i] = this->next[i];
	}
	auxNext[this->capacity * 2 - 1] = -1;
	for (int i = this->capacity; i < this->capacity*2-1; i++)
		auxNext[i] = i+1;

	this->firstEmpty = this->capacity;
	this->capacity *= 2;
	delete[] this->elems;
	delete[] this->next;
	this->elems = aux;
	this->next = auxNext;
}

void SortedMultiMap::add(TKey c, TValue v) 
{
	if (this->firstEmpty == -1)
		resize();
	int pos = this->firstEmpty;
	this->firstEmpty = this->next[pos];
	this->elems[pos].first = c;
	this->elems[pos].second = v;

	int prev = -1, current = this->head;
	while (current != -1 && this->rel(this->elems[current].first, c) && this->elems[current].first != c)
		{
			prev = current;
			current = this->next[current];
		}

	if (prev == -1)
	{
		this->next[pos] = this->head;
		this->head = pos;
	}
	else
	{
		this->next[pos] = this->next[prev];
		this->next[prev] = pos;
	}

	this->length++;
}

vector<TValue> SortedMultiMap::search(TKey c) const 
{
	vector<TValue> res;
	int current = this->head;
	while (current != -1 && rel(this->elems[current].first, c) && this->elems[current].first != c)
		current = this->next[current];
	while (current != -1 && this->elems[current].first == c)
	{
		res.push_back(this->elems[current].second);
		current = this->next[current];
	}
	return res;
}

bool SortedMultiMap::remove(TKey c, TValue v) 
{
	int current = this->head;
	int prev = -1;
	while (current != -1 && this->rel(this->elems[current].first, c) && this->elems[current].first != c)
	{
		prev = current;
		current = this->next[current];
	}
	while (current != -1 && this->elems[current].first == c)
		if (this->elems[current].second == v)
		{
			if (prev != -1)
			{
				this->next[prev] = this->next[current];
				
			}
			else
				//delete the head
			{
				this->head = this->next[this->head];
			}
			this->next[current] = this->firstEmpty;
			this->firstEmpty = current;
			this->length--;
			return true;
		}
		else
		{
			prev = current;
			current = this->next[current];
		}

    return false;
}

int SortedMultiMap::size() const 
{
	return this->length;
}

bool SortedMultiMap::isEmpty() const 
{
	return this->length == 0;
}

SMMIterator SortedMultiMap::iterator() const 
{
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() 
{
	delete[] elems;
	delete[] next;
}
