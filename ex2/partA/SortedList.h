#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdexcept>

namespace mtm {
	template<typename T>
	class SortedList {
	private:
		T** elements;
		unsigned int size;
		unsigned int max_size;
		static const unsigned int SIZE = 1;
		static const unsigned int RESIZE_FACTOR = 2;


		void deleteElements()
		{
			for (unsigned int i = 0; i < size; i++) {
				delete elements[i];
			}
			delete[] elements;
		}


		void resize()
		{
			T** copied_elements = new T* [max_size * RESIZE_FACTOR];
			for (unsigned int i = 0; i < size; i++) {
				copied_elements[i] = new T(*elements[i]);
			}
			deleteElements();
			elements = copied_elements;
			max_size *= RESIZE_FACTOR;
		}


	public:
		class const_iterator;


		SortedList() : elements(new T* [SIZE]), size(0), max_size(SIZE)
		{}


		SortedList(const SortedList& list) : elements(new T* [list.max_size]),
											 size(list.size),
											 max_size(list.max_size)
		{
			for (unsigned int i = 0; i < list.size; i++) {
				elements[i] = new T(*list.elements[i]);
			}
		}


		~SortedList()
		{
			deleteElements();
		}


		SortedList& operator=(const SortedList& list)
		{
			//The code can handle self-assignment but i don't see any reason to allocate new array for nothing
			if (this == &list) {
				return *this;
			}
			T** copied_elements = new T* [list.max_size];
			for (unsigned int i = 0; i < list.size; i++) {
				copied_elements[i] = new T(*list.elements[i]);
			}
			deleteElements();
			elements = copied_elements;
			size = list.size;
			max_size = list.max_size;
			return *this;
		}


		void insert(const T& element)
		{
			if (size == max_size) {
				resize();
			}
			unsigned int index = 0;
			while (index < size && !(element < *elements[index])) {
				index++;
			}
			for (unsigned int i = size; i > index; i--) {
				elements[i] = elements[i - 1];
			}
			elements[index] = new T(element);
			size++;
		}


		void remove(const const_iterator& iterator)
		{
			delete elements[iterator.index];
			elements[iterator.index] = nullptr;
			for (unsigned int i = iterator.index; i < size - 1; i++) {
				elements[i] = elements[i + 1];
			}
			size--;
		}


		unsigned int length() const
		{
			return size;
		}


		template<typename S>
		SortedList filter(const S& predicate) const
		{
			SortedList list;
			for (unsigned int i = 0; i < size; i++) {
				if (predicate(*elements[i])) {
					list.insert(*elements[i]);
				}
			}
			return list;
		}


		template<typename S>
		SortedList apply(const S& applier) const
		{
			SortedList list;
			for (unsigned int i = 0; i < size; i++) {
				T element = applier(*elements[i]);
				list.insert(element);
			}
			return list;
		}


		const_iterator begin() const
		{
			return const_iterator(*this, 0);
		}


		const_iterator end() const
		{
			return const_iterator(*this, size);
		}
	};

	template<class T>
	class SortedList<T>::const_iterator {
	private:
		T** elements;
		unsigned int size;
		unsigned int index;

		friend class SortedList<T>;


		const_iterator(const SortedList& list, unsigned int index) :
				elements(list.elements), size(list.size), index(index)
		{}


	public:
		const_iterator(const const_iterator& iterator) = default;

		~const_iterator() = default;

		const_iterator& operator=(const const_iterator& iterator) = default;


		const_iterator& operator++()
		{
			if (index >= size) {
				throw std::out_of_range("++const_iterator failed");
			}
			index++;
			return *this;
		}


		const_iterator operator++(int)
		{
			if (index >= size) {
				throw std::out_of_range("const_iterator++ failed");
			}
			const_iterator iterator(*this);
			index++;
			return iterator;
		}


		bool operator==(const const_iterator& iterator) const
		{
			return elements == iterator.elements && index == iterator.index;
		}


		const T& operator*() const
		{
			return *elements[index];
		}

	};
}

#endif //SORTED_LIST_H
