//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Anim.h"
#include "Constants.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Mixer.h"
#include "Clip.h"


namespace Azul
{

	Anim::Anim()
		: ssboRes(),
		numBones(0),
		pClip(nullptr),
		poBoneResult(nullptr)
	{ }

	Anim::Anim(Clip* clip)
		: ssboRes(),
		numBones(0),
		pClip(clip),
		poBoneResult(nullptr)
	{
		this->numBones = clip->numBones;
		this->poBoneResult = new Bone[(unsigned int)clip->numBones]();
		this->ssboRes.Set((unsigned int)clip->numBones, sizeof(Bone), this->poBoneResult);
	}

	Anim::~Anim()
	{
		delete[] this->poBoneResult;
	}

	void Anim::Clear()
	{
		this->pClip = nullptr;
	}

	void Anim::SetName(Name _name)
	{
		this->name = _name;
	}

	void Anim::SetClip(Clip* clip)
	{
		this->pClip = clip;
	}

	bool Anim::Transition(AnimTime tCurr, float& transitionCurrTime, float transitionTime, Clip* newClip, Mixer* mixerRes)
	{
		bool returnVal = true;

		// Old clip
		Clip::FrameBucket* pTmpA = this->pClip->poHead;
		while (tCurr >= pTmpA->KeyTime && pTmpA->nextBucket != nullptr)
			pTmpA = pTmpA->nextBucket;
		Clip::FrameBucket* pAB = pTmpA;
		
		// New clip
		Clip::FrameBucket* pTmpB = newClip->poHead;
		while (tCurr >= pTmpB->KeyTime && pTmpB->nextBucket != nullptr)
			pTmpB = pTmpB->nextBucket;
		Clip::FrameBucket* pBB = pTmpB;

		// Res
		float A = 0.0f;
		float B = 1.0f;
		float resCurr = A + transitionCurrTime * (B - A);

		if (resCurr > 1.0f)
		{
			resCurr = 1.0f;
			returnVal = false;
		}

		mixerRes->frameA = pAB->ssbo;
		mixerRes->frameB = pBB->ssbo;

		mixerRes->ts = resCurr;

		mixerRes->Update();

		transitionCurrTime += transitionTime;

		return returnVal;
	}

	Anim::Name Anim::GetAnimName() const
	{
		return this->name;
	}

	Clip::Name Anim::GetClipName() const
	{
		if (this->pClip == nullptr)
			return Clip::Name::NULL_CLIP;
		return this->pClip->GetClipName();
	}

	AnimTime Anim::FindMaxTime()
	{
		assert(pClip);
		return this->pClip->GetTotalTime();
	}

	void Anim::Animate(AnimTime tCurr)
	{
		this->pClip->AnimateBones(tCurr, this->poBoneResult);
	}

	void Anim::Animate(AnimTime tCurr, Mixer* mixer)
	{
		this->pClip->AnimateBones(tCurr, mixer);
	}
}

//--- End of File ----