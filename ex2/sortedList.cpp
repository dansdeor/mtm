#include "sortedList.h"
#include <stdexcept>


void mtm::sortedList::resize()
{
	T* copied_elements = new T[max_size * RESIZE_FACTOR];
	for (unsigned int i = 0; i < size; i++) {
		copied_elements[i] = elements[i];
	}
	delete[] elements;
	elements = copied_elements;
	max_size *= RESIZE_FACTOR;
}


mtm::sortedList::sortedList() : elements(new T[SIZE]), size(0), max_size(SIZE)
{
}


mtm::sortedList::sortedList(const mtm::sortedList& list) : elements(new T[list.max_size]),
														   size(list.size),
														   max_size(list.max_size)
{
	for (unsigned int i = 0; i < list.size; i++) {
		elements[i] = list.elements[i];
	}
}


mtm::sortedList::~sortedList()
{
	delete[] elements;
}


mtm::sortedList& mtm::sortedList::operator=(const sortedList& list)
{
	//The code can handle self-assignment but i don't see any reason to allocate new array for nothing
	if (this == &list) {
		return *this;
	}
	T* copied_elements = new T[list.max_size];
	for (unsigned int i = 0; i < list.size; i++) {
		copied_elements[i] = list.elements[i];
	}
	delete[] elements;
	elements = copied_elements;
	size = list.size;
	max_size = list.max_size;
	return *this;
}


void mtm::sortedList::insert(T& element)
{
	if (size == max_size) {
		resize();
	}
	unsigned int index = 0;
	while (!(element < elements[index])) {
		index++;
	}
	for (unsigned int i = size - 1; i > index; i--) {
		elements[i] = elements[i - 1];
	}
	elements[index] = element;
	size++;
}


void mtm::sortedList::remove(const mtm::sortedList::const_iterator& iterator)
{
	for (unsigned int i = size - 1; i > iterator.index; i--) {
		elements[i - 1] = elements[i];
	}
	size--;
}


unsigned int mtm::sortedList::length() const
{
	return size;
}


mtm::sortedList mtm::sortedList::filter(bool (* predict)(const T&)) const
{
	sortedList list;
	for (unsigned int i = 0; i < size; i++) {
		if (predict(elements[i])) {
			list.insert(elements[i]);
		}
	}
	return list;
}


mtm::sortedList mtm::sortedList::apply(T (* applier)(T)) const
{
	sortedList list;
	for (unsigned int i = 0; i < size; i++) {
		T element = applier(elements[i]);
		list.insert(element);
	}
	return list;
}


mtm::sortedList::const_iterator mtm::sortedList::begin() const
{
	return const_iterator(*this, 0);
}


mtm::sortedList::const_iterator mtm::sortedList::end() const
{
	return const_iterator(*this, size - 1);
}


mtm::sortedList::const_iterator::const_iterator(const mtm::sortedList& list, unsigned int index) :
		elements(list.elements), size(list.size), index(index)
{
}


mtm::sortedList::const_iterator& mtm::sortedList::const_iterator::operator++()
{
	if (index >= size) {
		throw std::out_of_range("++const_iterator failed");
	}
	index++;
	return *this;
}


mtm::sortedList::const_iterator mtm::sortedList::const_iterator::operator++(int)
{
	if (index >= size) {
		throw std::out_of_range("const_iterator++ failed");
	}
	const_iterator iterator(*this);
	index++;
	return iterator;
}


bool mtm::sortedList::const_iterator::operator==(const mtm::sortedList::const_iterator& iterator) const
{
	return elements == iterator.elements && index == iterator.index;
}


const T& mtm::sortedList::const_iterator::operator*() const
{
	return elements[index];
}
