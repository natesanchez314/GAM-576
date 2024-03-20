#include "DLinkIterator.h"

DLinkIterator::DLinkIterator()
	:head(nullptr), curr(nullptr), isDone(false)
{ }

DLink* DLinkIterator::First()
{
	return this->head;
}

DLink* DLinkIterator::Next()
{
	if (this->curr != nullptr)
		this->curr = this->curr->next;
	if (this->curr == nullptr)
		this->isDone = true;
	return this->curr;
}

DLink* DLinkIterator::Curr()
{
	return this->curr;
}

bool DLinkIterator::IsDone()
{
	return this->isDone;
}

void DLinkIterator::Reset(DLink* _head)
{
	this->head = _head;
	this->curr = _head;
	this->isDone = false;
}

void DLinkIterator::Clear()
{
	this->head = nullptr;
	this->curr = nullptr;
	this->isDone = true;
}