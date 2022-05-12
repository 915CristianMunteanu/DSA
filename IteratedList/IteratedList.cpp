
#include <exception>
#include "ListIterator.h"
#include "IteratedList.h"
#include <iostream>
using namespace std;
void IteratedList::filter(Condition cond)
{
	
	ListIterator iterator = this->first();
	int current = iterator.getCurrent();
	while (current != -1) {
		if (cond(iterator.getCurrent()) == false)
			this->remove(iterator);
		iterator.next();
	}
}
int IteratedList::allocateP()
{
	if (dllaList.firstFree==-1) {
		resize(dllaList.cap * 2);
	}
	int newFreePos = dllaList.firstFree;
	dllaList.firstFree = dllaList.nodes[dllaList.firstFree].next;
	return newFreePos;
}

void IteratedList::resize(int newCap)
{
	auto* newNodes = new DLLANode[newCap];
	for (int i = 0; i < this->dllaList.cap; i++) {
		newNodes[i].info = this->dllaList.nodes[i].info;
		newNodes[i].next = this->dllaList.nodes[i].next;
		newNodes[i].prev = this->dllaList.nodes[i].prev;
	}
	for (int i = this->dllaList.cap; i < newCap-1; i++) {
		newNodes[i].next = i + 1;
	}
	for (int i = this->dllaList.cap+1; i < newCap; i++) {
		newNodes[i].prev = i - 1;
	}
	newNodes[newCap - 1].next = -1;
	newNodes[this->dllaList.cap].prev = this->dllaList.head;

	delete[] this->dllaList.nodes;

	this->dllaList.nodes = newNodes;
	dllaList.firstFree = dllaList.cap;
	dllaList.cap = newCap;
}//Theta(n)

IteratedList::IteratedList() {
	dllaList.cap = 10;
	dllaList.head = -1;
	dllaList.tail = -1;
	dllaList.size = 0;
	dllaList.nodes = new DLLANode[this->dllaList.cap];
	for (int i = 0; i < dllaList.cap-1; i++)
		dllaList.nodes[i].next = i + 1;
	dllaList.nodes[dllaList.cap-1].next = -1;
	dllaList.firstFree = 0;
	for (int i = 1; i < dllaList.cap-1; i++)
		dllaList.nodes[i].prev = i - 1;
	dllaList.nodes[0].prev = -1;
}

int IteratedList::size() const {
	//TODO - Implementation
	return this->dllaList.size;
}//theta(1)

bool IteratedList::isEmpty() const {
	//TODO -  Implementation
	if (dllaList.size == 0)
		return true;
	return false;
}//theta(1)

ListIterator IteratedList::first() const {
	return ListIterator(*this);
}//theta(1)

TElem IteratedList::getElement(ListIterator pos) const {
	if (!pos.valid())
		throw exception();
	return pos.getCurrent();
}//theta(1)

TElem IteratedList::remove(ListIterator& pos) {
	if (!pos.valid())
		throw exception();
	DLLANode node = dllaList.nodes[pos.current];
	//we need to remove the head
	if (pos.list.dllaList.head == pos.current) {
		dllaList.head = dllaList.nodes[dllaList.head].next;
		dllaList.nodes[pos.current].prev = -1;
		dllaList.nodes[pos.current].next = dllaList.firstFree;
		dllaList.firstFree = pos.current;
		dllaList.size--;
		pos.current = this->dllaList.head;
		return node.info;
	}
	//we need to remove the tail
	if (pos.list.dllaList.tail == pos.current) {
		dllaList.tail = dllaList.nodes[dllaList.tail].prev;
		dllaList.nodes[dllaList.tail].next = -1;
		dllaList.nodes[pos.current].next = dllaList.firstFree;
		dllaList.firstFree = pos.current;
		dllaList.size--;
		pos.current = this->dllaList.head;
		return node.info;
	}

	int prev = dllaList.nodes[pos.current].prev;
	int next= dllaList.nodes[pos.current].next;
	dllaList.nodes[prev].next = next;
	dllaList.nodes[next].prev = prev;
	dllaList.size--;
	dllaList.nodes[pos.current].next = dllaList.firstFree;
	dllaList.firstFree = pos.current;
	pos.current = next;
	return node.info;

}//theta(1)

ListIterator IteratedList::search(TElem e) const{
	//TODO - Implementation
	ListIterator it = this->first();
	int current = dllaList.head;
	while (current != -1 && dllaList.nodes[current].info != e) {
		it.next();
		current = it.current;
	}
	return it;
}//theta(n)=Worst case. theta(1)-best case

TElem IteratedList::setElement(ListIterator pos, TElem e) {
	if (!pos.valid())
		throw exception();
	int old = dllaList.nodes[pos.current].info;
	dllaList.nodes[pos.current].info = e;
	return old;
}//theta(1)

void IteratedList::addToPosition(ListIterator& pos, TElem e) {
	if (!pos.valid())
		throw exception();
	if (dllaList.cap == dllaList.size)
		resize(dllaList.cap * 2);
	if (pos.current == 0) {

		addToBeginning(e);
		return;
	}
	else if (pos.current == dllaList.size) {
		addToEnd(e);
		return;
	}
	else {
		int newPosition = allocateP();
		dllaList.nodes[newPosition].info = e;
		dllaList.nodes[newPosition].next = pos.current;
		int prev_of_current = dllaList.nodes[pos.current].prev;
		int next_of_prev_of_current = dllaList.nodes[dllaList.nodes[pos.current].prev].next;
		dllaList.nodes[newPosition].prev = next_of_prev_of_current;
		dllaList.nodes[pos.current].prev = newPosition;
		dllaList.nodes[prev_of_current].next = newPosition;
		this->dllaList.size += 1;
	}
}//theta(1)

void IteratedList::addToEnd(TElem e) {
	int newPosition = allocateP();
	dllaList.nodes[newPosition].info = e;
	dllaList.nodes[newPosition].next = -1;
	dllaList.nodes[newPosition].prev = dllaList.tail;
	if (dllaList.head == -1) {
		//when the list is empty
		dllaList.head = newPosition;
		dllaList.tail = newPosition;
	}
	else {
		dllaList.nodes[dllaList.tail].next = newPosition;
		dllaList.tail = newPosition;
	}
	this->dllaList.size += 1;
}//theta(1)

void IteratedList::addToBeginning(TElem e)
{
	int newPosition = allocateP();
	dllaList.nodes[newPosition].info = e;
	dllaList.nodes[newPosition].next = dllaList.head;
	dllaList.nodes[newPosition].prev = -1;
	if (dllaList.head == -1) {
		dllaList.head = newPosition;
		dllaList.tail = newPosition;
	}
	else {
		dllaList.head = newPosition;
		dllaList.nodes[dllaList.head].prev = newPosition;
	}
	dllaList.size += 1;
}//theta(1)
void IteratedList::print() {
	ListIterator iterator = this->first();
	int current = this->dllaList.head;
	std::cout << "Beginning of list:" << endl;
	while (current != -1) {
		std::cout << "Element: " << this->dllaList.nodes[current].info << "(index: " << current << ") " " | Prev: " << this->dllaList.nodes[current].prev << "(" << this->dllaList.nodes[this->dllaList.nodes[current].prev].info << ")" << " | Next: " << this->dllaList.nodes[current].next << endl;
		iterator.next();
		current = iterator.current;
	}
	std::cout << "End of list:" << endl << endl;
}//theta(n)-n=size

IteratedList::~IteratedList() {
	
}