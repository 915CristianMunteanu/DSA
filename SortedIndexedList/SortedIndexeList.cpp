#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>


SortedIndexedList::SortedIndexedList(Relation r) {
	this->head = nullptr;
	this->length = 0;
	this->relation = r;
}

int SortedIndexedList::size() const {
	return this->length;
}

bool SortedIndexedList::isEmpty() const {
	return length==0;
}

//WC- Theta(n)
//AC- Theta(n)
//BC- Theta(1)
TComp SortedIndexedList::getElement(int i) const{
	if (i >= length)
		throw exception();
	SLLNode* result = head;

	while (i--) {
		result = result->get_next();
	}
	return result->get_info();
}
//WC- Theta(n)
//AC- Theta(n)
//BC- Theta(1)
TComp SortedIndexedList::remove(int i) {
	if (i >= length || i < 0)
		throw exception();
	int index = 0;
	SLLNode* previous = head;
	while (index < (i - 1)) {
		previous = previous->get_next();
		index++;
	}
	this->length--;
	TComp save;
	if (previous->get_next() == nullptr) {
		//the case when we need to remove last element.
		save = previous->get_info();
		previous->set_next(nullptr);
	}
	if (previous == head) {
		//we need to remove the first element.
		if (i == 0) {
			SLLNode* value = head->get_next();
			save = previous->get_info();
			delete head;
			head = value;
		}
		else
		{
			SLLNode* value = head->get_next();
			save = previous->get_next()->get_info();
			previous->set_next(previous->get_next()->get_next());
			value->set_next(nullptr);
			delete value;
		}
	}
	else {

		SLLNode* value = previous->get_next();
		save = previous->get_next()->get_info();
		previous->set_next(previous->get_next()->get_next());
		value->set_next(nullptr);
		delete value;
	}
	return save;
	
}
//WC- Theta(n)
//AC- Theta(n)
//BC- Theta(1)
int SortedIndexedList::search(TComp e) const {
	int index = 0;
	SLLNode* result = head;
	while (result != nullptr) {
		if (result->get_info() == e)
			return index;
		result = result->get_next();
		index++;
	}
	return -1;
}

void SortedIndexedList::add(TComp e) {
	SLLNode* position = head;
	SLLNode* previous = nullptr;
	this->length++;
	if (position != nullptr && relation(position->get_info(), e)==false) {
		SLLNode* new_node = new SLLNode{ e,position };
		head = new_node;
		return;
	}
	while (position != nullptr && relation(position->get_info(), e)) {
		previous = position;
		position = position->get_next();
	}
	if (position == nullptr)
	{
		//beginning of the list and list is empty
		if (previous == nullptr)
		{
			SLLNode* new_node = new SLLNode(e, position);
			head = new_node;
		}
		else
		{   //final of the list
			SLLNode* new_node = new SLLNode(e, nullptr);
			previous->set_next(new_node);
		}
	}
	else { //between elements of the list
		SLLNode* new_node = new SLLNode(e, position);
		previous->set_next(new_node);
	}
}


ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
}

void SortedIndexedList::empty()
{
	SLLNode* node;
	while (head != nullptr)
	{
		node = head;
		head = head->get_next();
		delete node;
	}
	this->length = 0;
}

//destructor
SortedIndexedList::~SortedIndexedList() {
	//TODO - Implementation
	SLLNode* node;
	while (head != nullptr)
	{
		node = head;
		head = head->get_next();
		delete node;
	}
}
