#include "ManBase.h"

ManBase::ManBase(int grow)
	:active(nullptr), reserve(nullptr), grow(grow), activeCount(0), reserveCount(0)
{
	this->active = new DLinkMan();
	this->reserve = new DLinkMan();
}

ManBase::ManBase(int reserve, int grow)
	:active(nullptr), reserve(nullptr), grow(grow), activeCount(0), reserveCount(reserve)
{ 
	this->active = new DLinkMan();
	this->reserve = new DLinkMan();
}

ManBase::~ManBase()
{
	delete this->active;
	delete this->reserve;
}

DLink* ManBase::baseAddToFront()
{
	if (this->reserveCount <= 0)
		proFillReservedPool(this->grow);

	DLink* dlink = this->reserve->Pop();
	this->active->AddFront(dlink);
	this->activeCount++;
	this->reserveCount--;

	return dlink;
}

DLink* ManBase::baseAddToEnd()
{
	if (this->reserveCount <= 0)
		proFillReservedPool(this->grow);

	DLink* dlink = this->reserve->Pop();
	this->active->AddEnd(dlink);
	this->activeCount++;
	this->reserveCount--;

	return dlink;
}

void ManBase::baseRemove(DLink* node)
{
	this->active->Remove(node);
	node->Clear();
	this->reserve->AddFront(node);
	this->activeCount--;
	this->reserveCount++;
}
 
void ManBase::proFillReservedPool(int count)
{ 
	for (int i = 0; i < count; i++)
	{
		DLink* node = this->derivedCreateNode();
		this->reserve->AddFront(node);
		this->reserveCount++;
	}
}

DLink* ManBase::baseFind(DLink* target)
{
	Iterator* iter = this->baseGetActiveIterator();
	for (DLink* dlink = iter->First(); !iter->IsDone(); dlink = iter->Next())
	{
		if (dlink->Compare(target))
			return dlink;
	}
	return nullptr;
}

void ManBase::baseDump()
{

}

Iterator* ManBase::baseGetActiveIterator()
{
	return this->active->GetIterator();
}

Iterator* ManBase::baseGetReserveIterator()
{
	return this->reserve->GetIterator();
}