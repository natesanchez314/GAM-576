//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "PCSTree.h"
#include "PCSNode.h"

#include <iostream>

namespace Azul
{
	// constructor
	PCSNode::PCSNode()
		: pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr), pForward(nullptr), pReverse(nullptr), pName()
	{
		memset(&this->pName[0], 0x0, PCSNode::NAME_SIZE);
	}

	// copy constructor
	PCSNode::PCSNode(const PCSNode & in)
		: pParent(in.GetParent()), pChild(in.GetChild()), pNextSibling(in.GetNextSibling()), pPrevSibling(in.GetPrevSibling()), pForward(in.GetForward()), pReverse(in.GetReverse())
	{
		in.GetName(this->pName, PCSNode::NAME_SIZE);
	}

	// Specialize Constructor
	PCSNode::PCSNode(PCSNode * const pInParent, PCSNode * const pInChild, PCSNode * const pInNextSibling, PCSNode * const pInPrevSibling, const char * const pInName)
		: pParent(pInParent), pChild(pInChild), pNextSibling(pInNextSibling), pPrevSibling(pInPrevSibling)
	{
		strcpy_s(this->pName, PCSNode::NAME_SIZE, pInName);
	}

	PCSNode::PCSNode(const char * const pInName)
		: pParent(nullptr), pChild(nullptr), pNextSibling(nullptr), pPrevSibling(nullptr), pForward(nullptr), pReverse(nullptr)
	{
		strcpy_s(this->pName, PCSNode::NAME_SIZE, pInName);
	}

	// destructor
	PCSNode::~PCSNode()
	{ }

	// assignment operator
	PCSNode & PCSNode::operator = (const PCSNode & in)
	{
		if (this != &in)
		{
			this->pParent = in.GetParent();
			this->pChild = in.GetChild();
			this->pNextSibling = in.GetNextSibling();
			this->pPrevSibling = in.GetPrevSibling();
			in.GetName(this->pName, PCSNode::NAME_SIZE);
		}
		return *this;
	}

	void PCSNode::SetParent(PCSNode* const pIn)
	{
		this->pParent = pIn;
	}

	void PCSNode::SetChild(PCSNode* const pIn)
	{
		this->pChild = pIn;
	}

	void PCSNode::SetNextSibling(PCSNode* const pIn)
	{
		this->pNextSibling = pIn;
	}

	void PCSNode::SetPrevSibling(PCSNode* const pIn)
	{
		this->pPrevSibling = pIn;
	}

	void PCSNode::SetForward(PCSNode* const pIn)
	{
		this->pForward = pIn;
	}

	void PCSNode::SetReverse(PCSNode* const pIn)
	{
		this->pReverse = pIn;
	}

	PCSNode* PCSNode::GetParent(void) const
	{
		return this->pParent;
	}

	PCSNode* PCSNode::GetChild(void) const
	{
		return this->pChild;
	}

	PCSNode* PCSNode::GetNextSibling(void) const
	{
		return this->pNextSibling;
	}

	PCSNode* PCSNode::GetPrevSibling(void) const
	{
		return this->pPrevSibling;
	}

	PCSNode* PCSNode::GetForward(void) const
	{
		return this->pForward;
	}

	PCSNode* PCSNode::GetReverse(void) const
	{
		return this->pReverse;
	}

	PCSNode::Code PCSNode::SetName(const char * const pInName)
	{
		if (pInName == nullptr)
			return PCSNode::Code::FAIL_NULL_PTR;
		memcpy(this->pName, pInName, PCSNode::NAME_SIZE - 1);
		return PCSNode::Code::SUCCESS;
	}

	PCSNode::Code PCSNode::GetName(char * const pOutBuffer, unsigned int sizeOutBuffer) const
	{
		if (pOutBuffer == nullptr)
			return PCSNode::Code::FAIL_NULL_PTR;
		if (sizeOutBuffer < PCSNode::NAME_SIZE)
		{
			memcpy(pOutBuffer, this->pName, sizeOutBuffer - 1);
			pOutBuffer[sizeOutBuffer - 1] = '\0';
		}
		else
			memcpy(pOutBuffer, this->pName, sizeOutBuffer);
		return PCSNode::Code::SUCCESS;
	}

	void PCSNode::PrintNode() const
	{
		std::cout << "Name: " << std::ends;
		std::cout << this->pName << std::endl;

		std::cout << "Parent: " << std::ends;
		if (this->pParent != nullptr)
			std::cout << this->pParent->pName << std::endl;
		else
			std::cout << "null" << std::endl;

		std::cout << "Prev Sibling: " << std::ends;
		if (this->pPrevSibling != nullptr)
			std::cout << this->pPrevSibling->pName << std::endl;
		else
			std::cout << "null" << std::endl;

		std::cout << "Next Sibling: " << std::ends;
		if (this->pNextSibling != nullptr)
			std::cout << this->pNextSibling->pName << std::endl;
		else
			std::cout << "null" << std::endl;

		std::cout << "Child: " << std::ends;
		if (this->pChild != nullptr)
			std::cout << this->pChild->pName << std::endl;
		else
			std::cout << "null" << std::endl;

		std::cout << "Reverse: " << std::ends;
		if (this->pReverse != nullptr)
			std::cout << this->pReverse->pName << std::endl;
		else
			std::cout << "null" << std::endl;

		std::cout << "Forward: " << std::ends;
		if (this->pForward != nullptr)
			std::cout << this->pForward->pName << std::endl;
		else
			std::cout << "null" << std::endl;
		std::cout << "\n" << std::endl;
	}

	void PCSNode::PrintChildren() const
	{
		PCSNode* node = this->pChild;
		while (node != nullptr)
		{
			node->PrintNode();
			node = node->GetNextSibling();
		}
	}


	void PCSNode::PrintSiblings() const
	{
		PCSNode* sib = this->pPrevSibling;
		while (sib != nullptr)
		{
			sib->PrintNode();
			sib = sib->GetPrevSibling();
		}
		sib = this->pNextSibling;
		while (sib != nullptr)
		{
			sib->PrintNode();
			sib = sib->GetNextSibling();
		}
	}

	int PCSNode::GetNumSiblings() const
	{
		int num = 1;
		PCSNode* sib = this->pPrevSibling;
		while (sib != nullptr)
		{
			num++;
			sib = sib->GetPrevSibling();
		}
		sib = this->pNextSibling;
		while (sib != nullptr)
		{
			num++;
			sib = sib->GetNextSibling();
		}
		return num;
	}

	int PCSNode::GetNumChildren() const
	{
		int num = 0;
		PCSNode* node = this->pChild;
		while (node != nullptr)
		{
			num++;
			node = node->GetNextSibling();
		}
		return num;
	}
}

// ---  End of File ---
