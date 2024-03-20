//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ANIM_H
#define ANIM_H

#include "AnimTimer.h"
#include "MathEngine.h"
#include "Clip.h"
#include "SSBO.h"

namespace Azul
{
	class Anim : public DLink
	{
	public:
		enum class Name
		{
			ANIM_A,
			ANIM_B,
			BOT_HIT_FRONT,
			RUN,
			SIDESTEP_LEFT,
			WALK,
			UNITIALIZED
		};

		Anim();
		Anim(Clip* clip);
		Anim(const Anim &) = delete;
		Anim &operator = (const Anim &) = delete;
		virtual ~Anim();

		virtual void Clear();

		void SetName(Name name);
		void SetClip(Clip* clip);

		Name GetAnimName() const;
		Clip::Name GetClipName() const;

		void Animate(AnimTime tCurr);
		void Animate(AnimTime tCurr, Mixer* mixer);
		AnimTime FindMaxTime();

		SSBO ssboRes;
		int numBones;

	private:
		Name name;
		Clip            *pClip;
		Bone            *poBoneResult;
	};

}
#endif

// --- End of File ---