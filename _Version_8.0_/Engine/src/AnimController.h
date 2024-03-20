//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_CONTROLLER_H
#define ANIM_CONTROLLER_H

#include "TimerController.h"
#include "GameObjectAnim.h"
#include "Anim.h"
#include "DLink.h"
#include "Mixer.h"
#include "Texture.h"

namespace Azul
{
	class AnimController
	{
	public:
		AnimController();
		AnimController(AnimTime delta, Anim* anim);
		AnimController(const AnimController &) = delete;
		AnimController &operator = (const AnimController &) = delete;
		~AnimController();

		void SetAnim(Clip::Name name);
		void TransitionAnim(Clip::Name name, float transitionTime);
		void SetAnim(Clip::Name name, AnimTime delta);
		void SetAnimSpeed(AnimTime delta);

		Anim* GetAnim() const;

		void Update();

		Mixer* mixer;

	private:
		TimerController *poTimerControl;
		Anim *poAnim;
		Clip* transitionClip;
		bool transitioning;
		float transitionTime;
		float transitionCurrTime;

	};
}

#endif

// --- End of File ---
