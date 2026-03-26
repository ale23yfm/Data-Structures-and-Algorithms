#include "SortedSet.h"
#include "SortedSetIterator.h"

void SortedSet::resize()
{
	this->capacity = 2 * this->capacity;
	TElem* aux = new TElem[this->capacity];
	for (int i = 0; i < this->len; i++)
		aux[i] = this->elements[i];
	delete[] this->elements;
	this->elements = aux;
}

SortedSet::SortedSet(Relation r) {	
	this->rel = r;
	this->capacity = 10;
	this->len = 0;
	this->elements = new TElem[capacity];
}

SortedSet::SortedSet(const SortedSet& other) {
	this->rel = other.rel;
	this->capacity = other.capacity;
	this->len = other.len;

	this->elements = new TElem[this->capacity];
	for (int i = 0; i < this->len; i++) {
		this->elements[i] = other.elements[i];
	}
}

SortedSet& SortedSet::operator=(const SortedSet& other) {
	if (this == &other)
		return *this;

	this->rel = other.rel;
	this->capacity = other.capacity;
	this->len = other.len;

	delete[] this->elements;
	this->elements = new TElem[this->capacity];

	for (int i = 0; i < this->len; i++) {
		this->elements[i] = other.elements[i];
	}

	return *this;
}

bool SortedSet::add(TComp elem) {
	if (this->capacity == this->len)
		this->resize();
	for (int i = 0; i < this->len; i++)
		if (elements[i] == elem)
			return false; //duplicate
	int pos = 0;
	while (pos < this->len and rel(elements[pos], elem))
		pos++;
	for (int i = this->len - 1; i >= pos; i--)
		elements[i + 1] = elements[i];
	elements[pos] = elem;
	this->len++;
	return true;
}

bool SortedSet::remove(TComp elem) {
	int pos = -1;
	for (int i = 0; i < this->len; i++)
		if (this->elements[i] == elem)
			pos = i;
	if (pos == -1)
		return false;
	for (int i = pos; i < this->len - 1; i++)
		this->elements[i] = this->elements[i + 1];
	this->len--;
	return true;
}

bool SortedSet::search(TComp elem) const {
	for (int i = 0; i < this->len; i++)
		if (this->elements[i] == elem)
			return true;
	return false;
}

int SortedSet::size() const {
	return this->len;
}

bool SortedSet::isEmpty() const {
	return this->len == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}

SortedSet::~SortedSet() {
	delete[] this->elements;
}