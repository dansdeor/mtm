#ifndef SORTED_LIST_H
#define SORTED_LIST_H

#include <stdexcept>

namespace mtm {
	template<class T>
	class SortedList {
	private:
		class Element;

		Element* head;


		static Element* copyElements(const SortedList& list)
		{
			if (list.head == nullptr) {
				return nullptr;
			}
			Element* head = new Element(*list.head);
			Element* iterator = head;
			Element* list_iterator = list.head->next;
			while (list_iterator != nullptr) {
				iterator->next = new Element(*list_iterator);
				iterator = iterator->next;
				list_iterator = list_iterator->next;
			}
			return head;
		}


		void deleteElements()
		{
			Element* iterator = head;
			while (iterator != nullptr) {
				Element* next_element = iterator->next;
				delete iterator;
				iterator = next_element;
			}
		}


	public:

		class const_iterator;


		SortedList() : head(nullptr)
		{}


		SortedList(const SortedList& list) : head(copyElements(list))
		{}


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
			Element* new_head = copyElements(list);
			deleteElements();
			head = new_head;
			return *this;
		}


		void insert(const T& element)
		{
			if (head == nullptr) {
				head = new Element(element);
			}
			else if (element < head->data) {
				Element* head_next = head;
				head = new Element(element);
				head->next = head_next;
			}
			else {
				Element* iterator = head;
				while (iterator->next != nullptr && !(element < iterator->next->data)) {
					iterator = iterator->next;
				}
				Element* new_element = new Element(element);
				new_element->next = iterator->next;
				iterator->next = new_element;
			}
		}


		void remove(const const_iterator& it)
		{
			if (head == it.iterator) {
				Element* element = head;
				head = head->next;
				delete element;
			}
			else {
				Element* iterator = head;
				while (iterator->next != nullptr) {
					if (iterator->next == it.iterator) {
						Element* element = iterator->next;
						iterator->next = iterator->next->next;
						delete element;
					}
					iterator = iterator->next;
				}
			}
		}


		int length() const
		{
			int size = 0;
			for (const_iterator it = this->begin(); it != this->end(); it++) {
				size++;
			}
			return size;
		}


		template<typename S>
		SortedList filter(const S& predicate) const
		{
			SortedList list;
			for (const_iterator it = this->begin(); !(it == this->end()); it++) {
				if (predicate(*it)) {
					list.insert(*it);
				}
			}
			return list;
		}


		template<typename S>
		SortedList apply(const S& applier) const
		{
			SortedList list;
			for (const_iterator it = this->begin(); !(it == this->end()); it++) {
				T element = applier(*it);
				list.insert(element);
			}
			return list;
		}


		const_iterator begin() const
		{
			return const_iterator(head);
		}


		const_iterator end() const
		{
			return const_iterator(nullptr);
		}
	};

	template<class T>
	class SortedList<T>::Element {
	private:
		T data;
		Element* next;

		friend class SortedList<T>;


		Element(const Element& element) : data(element.data), next(nullptr)
		{}


		explicit Element(const T& data) : data(data), next(nullptr)
		{}
	};

	template<class T>
	class SortedList<T>::const_iterator {
	private:
		Element* iterator;

		friend class SortedList<T>;


		explicit const_iterator(Element* list) : iterator(list)
		{}


	public:
		const_iterator(const const_iterator& iterator) = default;

		~const_iterator() = default;

		const_iterator& operator=(const const_iterator& iterator) = default;


		const_iterator& operator++()
		{
			if (iterator == nullptr) {
				throw std::out_of_range("++const_iterator failed");
			}
			iterator = iterator->next;
			return *this;
		}


		const_iterator operator++(int)
		{
			if (iterator == nullptr) {
				throw std::out_of_range("const_iterator++ failed");
			}
			const_iterator new_iterator(*this);
			iterator = iterator->next;
			return new_iterator;
		}


		bool operator==(const const_iterator& other) const
		{
			return iterator == other.iterator;
		}


		const T& operator*() const
		{
			return iterator->data;
		}

	};

}

#endif //SORTED_LIST_H
