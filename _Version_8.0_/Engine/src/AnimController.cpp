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
		: mixer(nullptr),
		poTimerControl(nullptr),
		poAnim(nullptr),
		transitionClip(nullptr),
		transitioning(false),
		transitionTime(0)
	{
		// Animation object
		this->poAnim = new Anim();
		assert(this->poAnim);
	}

	AnimController::AnimController(AnimTime delta, Anim* anim)
		: mixer(nullptr),
		poTimerControl(nullptr),
		poAnim(anim),
		transitionClip(nullptr),
		transitioning(false),
		transitionTime(0)
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
		if (this->transitioning)
		{
			bool doneTransitioning = this->poAnim->Transition(this->poTimerControl->GetCurrTime(), this->transitionCurrTime, this->transitionTime, this->transitionClip, this->mixer);
			
			if (!doneTransitioning)
			{
				this->poAnim->SetClip(this->transitionClip);
				this->poTimerControl->SetMaxTime(poAnim->FindMaxTime());
				this->transitioning = doneTransitioning;
			}
		}
		else
			this->poAnim->Animate(this->poTimerControl->GetCurrTime(), this->mixer);

	}

	void AnimController::SetAnim(Clip::Name name)
	{
		Clip* clip = ClipMan::Find(name);
		this->poAnim->SetClip(clip);
	}

	void AnimController::TransitionAnim(Clip::Name name, float _transitionTime)
	{
		this->transitionTime = _transitionTime;
		this->transitionCurrTime = 0.0f;
		this->transitioning = true;
		this->transitionClip = ClipMan::Find(name);
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
