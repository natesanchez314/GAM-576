#ifndef DLINK_MAN_H
#define DLINK_MAN_H

#include "DLinkIterator.h"
#include "DLink.h"
#include "Iterator.h"

class DLinkMan
{
protected:
	DLinkIterator* iter;

public:
	DLink* head;

public:
	DLinkMan();
	virtual ~DLinkMan();

	virtual void AddFront(DLink* node);
	virtual void AddEnd(DLink* node);
	virtual void Remove(DLink* node);
	virtual DLink* Pop();
	virtual Iterator* GetIterator();
};

#endif // !DLINK_MAN_H
