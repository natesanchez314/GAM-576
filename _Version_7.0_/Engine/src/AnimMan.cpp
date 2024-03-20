#include "AnimMan.h"
#include "Clip.h"

namespace Azul
{
	AnimMan* AnimMan::instance = nullptr;

	AnimMan::AnimMan(int reserveNum, int reserveGrow)
		: ManBase(reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	AnimMan::~AnimMan()
	{
		Iterator* iter = this->baseGetActiveIterator();
		DLink* node = iter->First();
		while (!iter->IsDone())
		{
			Anim* deleteNode = (Anim*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();
		node = iter->First();
		while (!iter->IsDone())
		{
			Anim* deleteNode = (Anim*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}
	}

	AnimMan* AnimMan::GetInstance()
	{
		return instance;
	}

	void AnimMan::Create(int reserveNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new AnimMan(reserveNum, reserveGrow);
	}

	void AnimMan::Destroy()
	{
		AnimMan* man = AnimMan::GetInstance();
		delete man;
		instance = nullptr;
	}

	Anim* AnimMan::Add(Anim::Name name, Clip* clip)
	{
		AnimMan* man = AnimMan::GetInstance();

		Anim* anim = (Anim*)man->baseAddToFront();

		anim->SetName(name);
		anim->SetClip(clip);

		return anim;
	}

	Anim* AnimMan::Find(Anim::Name name)
	{
		AnimMan* man = AnimMan::GetInstance();
		Iterator* iter = man->baseGetActiveIterator();
		for (Anim* anim = (Anim*)iter->First(); !iter->IsDone(); anim = (Anim*)iter->Next())
		{
			if (anim->GetAnimName() == name)
				return anim;
		}

		return nullptr;
	}

	void AnimMan::Remove(Anim* anim)
	{
		AnimMan* man = AnimMan::GetInstance();
		man->baseRemove(anim);
	}

	DLink* AnimMan::derivedCreateNode()
	{
		DLink* node = new Anim();
		return node;
	}
}