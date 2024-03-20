#include "SkelMan.h"
#include "Skeleton.h"

namespace Azul
{
	SkelMan* SkelMan::instance = nullptr;

	SkelMan::SkelMan(int reserveNum, int reserveGrow)
		: ManBase(reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	SkelMan::~SkelMan()
	{
		Iterator* iter = this->baseGetActiveIterator();
		DLink* node = iter->First();
		while (!iter->IsDone())
		{
			Skeleton* deleteNode = (Skeleton*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();
		node = iter->First();
		while (!iter->IsDone())
		{
			Skeleton* deleteNode = (Skeleton*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}
	}

	SkelMan* SkelMan::GetInstance()
	{
		return instance;
	}

	void SkelMan::Create(int reserveNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new SkelMan(reserveNum, reserveGrow);
	}

	void SkelMan::Destroy()
	{
		SkelMan* man = SkelMan::GetInstance();
		delete man;
		man = nullptr;
	}

	Skeleton* SkelMan::Add()
	{
		// TODO
		return nullptr;
	}

	Skeleton* SkelMan::Find()
	{
		// TODO
		return nullptr;
	}

	void SkelMan::Remove(Skeleton* skel)
	{
		SkelMan* man = SkelMan::GetInstance();
		// TODO
		//man->baseRemove(skel);
	}

	DLink* SkelMan::derivedCreateNode()
	{
		// TODO
		return nullptr;
	}
}