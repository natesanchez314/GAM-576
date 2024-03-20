//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"
#include "PCSTreeForwardIterator.h"
#include "PCSTreeReverseIterator.h"

namespace Azul
{

	// constructor
	PCSTree::PCSTree()
		:mInfo({ 0, 0, 0, 0 }), pRoot(nullptr)
	{ };

	// destructor
	PCSTree::~PCSTree()
	{ 
		/*if (this->pRoot != nullptr)
			Remove(this->pRoot);*/
	};

	// get Root
	PCSNode * PCSTree::GetRoot() const
	{
		return this->pRoot;
	}

	// insert
	void PCSTree::Insert(PCSNode * const pInNode, PCSNode * const pParent)
	{
		if (pInNode == pParent || pInNode == nullptr) // Prevent self reference and adding of null node
			return;
		if (this->pRoot == nullptr)
		{
			this->pRoot = pInNode;
			this->mInfo.currNumLevels = 1;
		}
		else
		{
			int depth = GetDepth(pParent);
			if (depth == this->mInfo.currNumLevels) // this is the lowest we can go
				this->mInfo.currNumLevels++;
			PCSNode* oldChild = pParent->GetChild(); // Update siblings
			if (oldChild != nullptr)
			{
				oldChild->SetPrevSibling(pInNode);
				oldChild->SetReverse(pInNode);
				pInNode->SetNextSibling(oldChild);
				pInNode->SetForward(oldChild);
			}
			else
			{
				pInNode->SetForward(pParent->GetForward());
				if (pParent->GetForward() != nullptr)
					pParent->GetForward()->SetReverse(pInNode);
			}
			pInNode->SetParent(pParent);
			pInNode->SetReverse(pParent);
			pParent->SetChild(pInNode);
			pParent->SetForward(pInNode);

			if (pInNode->GetForward() == nullptr) // this is the end node
				this->pRoot->SetReverse(pInNode);
		}
		this->mInfo.currNumNodes++;
		if (this->mInfo.currNumLevels > this->mInfo.maxNumLevels)
			this->mInfo.maxNumLevels = this->mInfo.currNumLevels;
		if (this->mInfo.currNumNodes > this->mInfo.maxNumNodes)
			this->mInfo.maxNumNodes = this->mInfo.currNumNodes;
	}

	// Remove
	void PCSTree::Remove(PCSNode * const pInNode)
	{
		assert(pInNode);
		// Remove children too
		while (pInNode->GetChild() != nullptr)
			Remove(pInNode->GetChild());
		
		PCSNode* parent = pInNode->GetParent();
		PCSNode* prev = pInNode->GetPrevSibling();
		PCSNode* next = pInNode->GetNextSibling();
		PCSNode* reverse = pInNode->GetReverse();
		PCSNode* forward = pInNode->GetForward();

		// Update curr num levels
		// Need to account for other nodes at the same level in different branches
		int depth = GetDepth(pInNode);
		if (depth == this->mInfo.currNumLevels)
		{
			if (pInNode->GetParent() != nullptr)
			{
				if (pInNode->GetParent()->GetNumChildren() == 1)
				{
					if (!MultipleAtBottom())
						this->mInfo.currNumLevels--;
				}
			}
			else
				this->mInfo.currNumLevels--;
		}

		// Fix parent's link to child
		if (parent != nullptr && parent->GetChild() == pInNode)
			parent->SetChild(pInNode->GetNextSibling());

		// Merge siblings
		if (prev != nullptr)
			prev->SetNextSibling(next);
		if (next != nullptr)
			next->SetPrevSibling(prev);

		// Fix links for iterator
		if (reverse != nullptr)
			reverse->SetForward(forward);
		if (forward != nullptr)
			forward->SetReverse(reverse);
		if (this->pRoot->GetReverse() == pInNode)
			this->pRoot = pInNode->GetReverse();

		// Clean node
		pInNode->SetChild(nullptr);
		pInNode->SetParent(nullptr);
		pInNode->SetNextSibling(nullptr);
		pInNode->SetPrevSibling(nullptr);
		pInNode->SetReverse(nullptr);
		pInNode->SetForward(nullptr);
		this->mInfo.currNumNodes--;
	}

	// get tree info
	void PCSTree::GetInfo(Info& info)
	{
		info = this->mInfo;
	}

	void PCSTree::Print() const
	{
		PCSTreeForwardIterator iter = PCSTreeForwardIterator(this->pRoot);
		for (PCSNode* node = iter.First(); !iter.IsDone(); node = iter.Next())
		{
			node->PrintNode();
		}
	}

	void PCSTree::PrintHelper(PCSNode* inNode) const
	{
		inNode->PrintNode();
		if (inNode->GetChild() != nullptr)
		{
			PCSNode* node = inNode->GetChild();
			while (node != nullptr)
			{
				PrintHelper(node);
				node = node->GetNextSibling();
			}
		}
	}

	int PCSTree::GetCountAtBottom(PCSNode* inNode) const
	{
		int count = 0;
		if (inNode->GetChild() == nullptr)
		{
			if (GetDepth(inNode) == this->mInfo.currNumLevels)
				count++;
		}
		else
		{
			PCSNode* node = inNode->GetChild();
			while (node != nullptr)
			{
				count += GetCountAtBottom(node);
				node = node->GetNextSibling();
			}
		}
		return count;
	}

	int PCSTree::GetCountAtBottom() const
	{
		int count = 0;
		PCSTreeReverseIterator iter = PCSTreeReverseIterator(this->pRoot);
		for (PCSNode* node = iter.First(); !iter.IsDone(); node = iter.Next())
		{
			if (node->GetChild() == nullptr)
			{
				if (GetDepth(node) == this->mInfo.currNumLevels)
					count++;
			}
		}
		return count;
	}

	bool PCSTree::MultipleAtBottom() const
	{
		// Reverse iterator might be faster here
		int count = 0;
		PCSTreeForwardIterator iter = PCSTreeForwardIterator(this->pRoot);
		for (PCSNode* node = iter.First(); !iter.IsDone(); node = iter.Next())
		{
			if (node->GetChild() == nullptr)
			{
				if (GetDepth(node) == this->mInfo.currNumLevels)
					count++;
				if (count > 1)
					return true;
			}
		}
		return false;
	}

	int PCSTree::GetDepth(PCSNode* inNode) const
	{
		int depth = 0;
		PCSNode* node = inNode;
		while (node != nullptr)
		{
			depth++;
			node = node->GetParent();
		}
		return depth;
	}
}

// ---  End of File ---
