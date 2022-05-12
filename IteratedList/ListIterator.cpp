#include "ListIterator.h"
#include "IteratedList.h"
#include <exception>
using namespace std;
ListIterator::ListIterator(const IteratedList& list) : list(list) {
	current = list.dllaList.head;
	
}

void ListIterator::first() {
	current = list.dllaList.head;
}

void ListIterator::next() {
	if (current==-1)
		throw exception();
	this->current = this->list.dllaList.nodes[current].next;
}

bool ListIterator::valid() const {
	if (current == -1)
		return false;
	return  true;
}


TElem ListIterator::getCurrent() const {
	if (current == -1)
		throw exception();
	return list.dllaList.nodes[current].info;
}
