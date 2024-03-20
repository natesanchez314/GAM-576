#ifndef MAN_BASE_H
#define MAN_BASE_H

#include "DLinkMan.h"

class ManBase
{
protected:
	DLinkMan* active;
	DLinkMan* reserve;
	int grow;
	int activeCount;
	int reserveCount;

protected:
	ManBase(int grow);
	ManBase(int reserve, int grow); 
	ManBase(const ManBase&) = delete;
	ManBase& operator=(const ManBase&) = delete;
	virtual ~ManBase();

	DLink* baseAddToFront();
	DLink* baseAddToEnd();
	DLink* baseFind(DLink* targetNode);
	void baseRemove(DLink* node);
	void baseDump();

	Iterator* baseGetActiveIterator();
	Iterator* baseGetReserveIterator();

	void proFillReservedPool(int count);

	virtual DLink* derivedCreateNode() = 0;
};

#endif // !MAN_BASE_H
