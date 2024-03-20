#include "DLinkMan.h"

DLinkMan::DLinkMan()
	:iter(new DLinkIterator()), head(nullptr)
{ }

DLinkMan::~DLinkMan()
{ 
	delete this->iter;
	this->iter = nullptr;
}

void DLinkMan::AddFront(DLink* node)
{
	if (this->head == nullptr)
	{
		this->head = node;
		node->next = nullptr;
		node->prev = nullptr;
	}
	else
	{
		node->next = head;
		head->prev = node;
		this->head = node;
		node->prev = nullptr;
	}
}

void DLinkMan::AddEnd(DLink* node)
{
	if (this->head == nullptr)
	{
		this->head = node;
		node->next = nullptr;
		node->prev = nullptr;
	}
	else
	{
		DLink* tmp = this->head;
		while (tmp->next != nullptr)
			tmp = tmp->next;

		tmp->next = node;
		node->prev = tmp;
		node->next = nullptr;
	}
}

void DLinkMan::Remove(DLink* node)
{
	if (node == nullptr)
		return;
	if (node == this->head)
		this->head = node->next;
	if (node->next != nullptr)
		node->next->prev = node->prev;
	if (node->prev != nullptr)
		node->prev->next = node->next;
	node->Clear();
}

DLink* DLinkMan::Pop()
{ 
	DLink* node = this->head;
	if (this->head != nullptr)
	{
		this->head = this->head->next;
		if (this->head != nullptr)
			this->head->prev = nullptr;
		node->Clear();
	}
	return node;
}

Iterator* DLinkMan::GetIterator()
{
	this->iter->Reset(this->head);
	return this->iter;
}