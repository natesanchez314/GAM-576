#include "DLink.h"

DLink::DLink()
	:next(nullptr), prev(nullptr)
{ }

void DLink::Clear()
{ 
	this->next = nullptr;
	this->prev = nullptr;
}

void DLink::Wash()
{
	this->Clear();
}

char* DLink::GetName()
{
	return "x";
}
bool DLink::Compare(DLink* pTargetNode)
{
	if (this == pTargetNode)
		return true;
	return false;
}

void DLink::Dump()
{

}