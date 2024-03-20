#include "ClipMan.h"
#include "Clip.h"

namespace Azul
{
	ClipMan* ClipMan::instance = nullptr;

	ClipMan::ClipMan(int reserveNum, int reserveGrow)
		: ManBase(reserveNum, reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	ClipMan::~ClipMan()
	{
		Iterator* iter = this->baseGetActiveIterator();
		DLink* node = iter->First();
		while (!iter->IsDone())
		{
			Clip* deleteNode = (Clip*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();
		node = iter->First();
		while (!iter->IsDone())
		{
			Clip* deleteNode = (Clip*)iter->Curr();
			node = iter->Next();
			delete deleteNode;
		}
	}

	ClipMan* ClipMan::GetInstance()
	{
		return instance;
	}

	void ClipMan::Create(int reserveNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new ClipMan(reserveNum, reserveGrow);
	}

	void ClipMan::Destroy()
	{
		ClipMan* man = ClipMan::GetInstance();
		delete man;
		man = nullptr;
	}

	Clip* ClipMan::Add(Clip::Name name, const char* const pInFileName)
	{
		ClipMan* man = ClipMan::GetInstance();

		Clip* clip = (Clip*)man->baseAddToFront();

		const char* pPath = "Data\\";
		size_t size = strlen(pPath) + strlen(pInFileName) + 1;
		char* pFileName = new char[size]();
		memset(pFileName, 0, size);
		strcat_s(pFileName, size, pPath);
		strcat_s(pFileName, size, pInFileName);

		clip->SetAnimationDataFromFile(pFileName);

		clip->SetName(name);

		delete pFileName;

		return clip;
	}

	Clip* ClipMan::Find(Clip::Name name)
	{
		ClipMan* man = ClipMan::GetInstance();
		Iterator* iter = man->baseGetActiveIterator();
		for (Clip* clip = (Clip*)iter->First(); !iter->IsDone(); clip = (Clip*)iter->Next())
		{
			if (clip->GetClipName() == name)
				return clip;
		}

		return nullptr;
	}

	void ClipMan::Remove(Clip* clip)
	{
		ClipMan* man = ClipMan::GetInstance();
		man->baseRemove(clip);
	}

	DLink* ClipMan::derivedCreateNode()
	{
		DLink* node = new Clip();
		return node;
	}
}