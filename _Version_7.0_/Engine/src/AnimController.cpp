//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AnimController.h"
#include "Anim.h"
#include "ClipMan.h"
#include "AnimMan.h"

namespace Azul
{
	AnimController::AnimController()
		: mixer(nullptr), poTimerControl(nullptr), poAnim(nullptr)
	{
		// Animation object
		this->poAnim = new Anim();
		assert(this->poAnim);
	}

	AnimController::AnimController(AnimTime delta, Anim* anim)
		: mixer(nullptr), poTimerControl(nullptr), poAnim(anim)
	{
		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);
		this->poTimerControl = new TimerController(delta, minTime, maxTime);
	}

	AnimController::~AnimController()
	{
		delete poAnim;
		delete mixer;
		delete poTimerControl;
	}

	void AnimController::Update()
	{
		this->poTimerControl->Update();
		this->poAnim->Animate(this->poTimerControl->GetCurrTime(), this->mixer);

	}

	void AnimController::SetAnim(Clip::Name name)
	{
		// Swap out clip
		if (this->poAnim->GetClipName() != name)
		{
			Clip* clip = ClipMan::Find(name);
			this->poAnim->SetClip(clip);

			AnimTime maxTime = poAnim->FindMaxTime();
			AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

		}
	}

	void AnimController::SetAnim(Clip::Name name, AnimTime delta)
	{
		Clip* clip = ClipMan::Find(name);
		this->poAnim->SetClip(clip);

		AnimTime maxTime = poAnim->FindMaxTime();
		AnimTime minTime = AnimTime(AnimTime::Duration::ZERO);

		this->poTimerControl = new TimerController(delta, minTime, maxTime);
	}

	void AnimController::SetAnimSpeed(AnimTime delta)
	{
		this->poTimerControl->SetDeltaTime(delta);
	}

	Anim* AnimController::GetAnim() const
	{
		return this->poAnim;
	}
}

// --- End of File ---
