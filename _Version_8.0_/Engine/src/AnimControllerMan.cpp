#include "AnimControllerMan.h"

namespace Azul
{
	AnimControllerMan* AnimControllerMan::instance = nullptr;

	AnimControllerMan::AnimControllerMan(int reserveNum, int reserveGrow)
		: ManBase(reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	AnimControllerMan::~AnimControllerMan()
	{
		Iterator* iter = this->baseGetActiveIterator();
		DLink* node = iter->First();
		while (!iter->IsDone())
		{
			AnimController* deleteNode = (AnimController*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();
		node = iter->First();
		while (!iter->IsDone())
		{
			AnimController* deleteNode = (AnimController*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}
	}

	AnimControllerMan* AnimControllerMan::GetInstance()
	{
		return instance;
	}

	void AnimControllerMan::Create(int reserveNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new AnimControllerMan(reserveNum, reserveGrow);
	}

	void AnimControllerMan::Destroy()
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();
		delete man;
		man = nullptr;
	}

	/*AnimController* AnimControllerMan::Add(Anim* anim, AnimTime delta)
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();

		AnimController* animController = (AnimController*)man->baseAddToFront();

		animController->Set(anim, delta);

		return animController;
	}

	AnimController* AnimControllerMan::Add(Anim::Name name, AnimTime delta)
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();

		AnimController* anim = (AnimController*)man->baseAddToFront();

		anim->Set(name, delta);

		return anim;
	}

	AnimController* AnimControllerMan::Find(Anim::Name name)
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();
		Iterator* iter = man->baseGetActiveIterator();
		for (AnimController* anim = (AnimController*)iter->First(); !iter->IsDone(); anim = (AnimController*)iter->Next())
		{
			if (anim->GetAnimName() == name)
				return anim;
		}

		return nullptr;
	}

	void AnimControllerMan::Remove(AnimController* anim)
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();
		man->baseRemove(anim);
	}

	void AnimControllerMan::Update()
	{
		AnimControllerMan* man = AnimControllerMan::GetInstance();

		Iterator* iter = man->baseGetActiveIterator();
		for (AnimController* anim = (AnimController*)iter->First(); !iter->IsDone(); anim = (AnimController*)iter->Next())
			anim->Update();
	}
	*/
	DLink* AnimControllerMan::derivedCreateNode()
	{
		//DLink* node = new AnimController();
		//return node;
		return nullptr;
	}
}