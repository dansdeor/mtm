#ifndef SORTED_LIST_H
#define SORTED_LIST_H


typedef int T;


namespace mtm {
	class sortedList {
	private:
		T* elements;
		unsigned int size;
		unsigned int max_size;
		static const unsigned int SIZE = 1;
		static const unsigned int RESIZE_FACTOR = 2;

		void resize();

	public:
		sortedList();

		sortedList(const sortedList& list);

		~sortedList();

		sortedList& operator=(const sortedList& list);

		class const_iterator;

		void insert(T& element);

		void remove(const const_iterator& iterator);

		unsigned int length() const;

		sortedList filter(bool (* predict)(const T&)) const;

		sortedList apply(T (* applier)(T)) const;

		const_iterator begin() const;

		const_iterator end() const;
	};

	class sortedList::const_iterator {
	private:
		T* elements;
		unsigned int size;
		unsigned int index;

		friend class sortedList;

		const_iterator(const sortedList& list, unsigned int index);

	public:
		const_iterator(const const_iterator& iterator) = default;

		~const_iterator() = default;

		const_iterator& operator=(const const_iterator& iterator) = default;

		const_iterator& operator++();

		const_iterator operator++(int);

		bool operator==(const const_iterator& iterator) const;

		const T& operator*() const;

	};
}

#endif //SORTED_LIST_H
