#ifndef DLINK_ITERATOR_H
#define DLINK_ITERATOR_H

#include "Iterator.h"
#include "DLink.h"

class DLinkIterator : public Iterator
{
private:
	DLink* head;
	DLink* curr;
	bool isDone;

public:
	DLinkIterator();

	virtual DLink* First() override;
	virtual DLink* Next() override;
	virtual DLink* Curr() override;
	virtual bool IsDone() override;

	void Reset(DLink* head);

private:
	void Clear();
};

#endif // !1
