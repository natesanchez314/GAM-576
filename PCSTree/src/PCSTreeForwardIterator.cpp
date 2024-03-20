//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTreeForwardIterator.h"

namespace Azul
{
	PCSTreeForwardIterator::PCSTreeForwardIterator(PCSNode *rootNode)
	{
		this->root = rootNode;
		this->current = rootNode;
	}

	PCSNode *PCSTreeForwardIterator::First()
	{
		return this->root;
	}

	PCSNode *PCSTreeForwardIterator::Next()
	{
		if (this->current != nullptr)
			this->current = this->current->GetForward();
		return this->current;
	}

	bool PCSTreeForwardIterator::IsDone()
	{
		return this->current == nullptr;
	}

	PCSNode *PCSTreeForwardIterator::CurrentItem()
	{
		return this->current;
	}

}

// ---  End of File ---------------
