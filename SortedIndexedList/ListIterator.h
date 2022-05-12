#pragma once
#include "SortedIndexedList.h"
#include "../../source/repos/SortedIndexedList/SortedIndexedList/SLLNode.h"


//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIndexedList;
private:

	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);
	int pos;

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;

};


