//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeReverseIterator.h"

namespace Azul
{
	PCSTreeReverseIterator::PCSTreeReverseIterator(PCSNode *rootNode)
	{
		this->root = rootNode;
		this->prevNode = rootNode->GetReverse();
		this->current = this->prevNode;
	}

	PCSNode *PCSTreeReverseIterator::First()
	{
		return prevNode;
	}

	PCSNode *PCSTreeReverseIterator::Next()
	{
		if (this->current != nullptr)
		{
			this->current = this->current->GetReverse();
			if (this->current == this->prevNode)
				this->current = nullptr;
		}
		return this->current;
	}

	bool PCSTreeReverseIterator::IsDone()
	{
		return this->current == nullptr;
	}

	PCSNode *PCSTreeReverseIterator::CurrentItem()
	{
		return this->current;
	}

}

// ---  End of File ---------------
