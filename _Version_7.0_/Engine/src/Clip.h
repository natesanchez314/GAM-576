//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CLIP_H
#define CLIP_H

#include "AnimTime.h"
#include "Bone.h"
#include "clipData.h"
#include "DLink.h"
#include "SSBO.h"
#include "Mixer.h"

namespace Azul
{
	class Clip : public DLink
	{
	public:

		struct FrameBucket
		{
			~FrameBucket()
			{
				delete[] poBone;
				//delete ssbo;
			}

			FrameBucket *nextBucket;
			FrameBucket *prevBucket;
			AnimTime      KeyTime;
			Bone         *poBone;
			SSBO ssbo;
			char          pad[4];
		};

		enum class Name
		{
			BOT_HIT_FRONT,
			BOT_RUN,
			BOT_SIDESTEP_LEFT,
			BOT_WALK,
			BOT_SHOT_FRONT,
			BOT_TURN_LEFT,
			MOUSEY_JOYFUL_JUMP,
			MOUSEY_WALK,
			MOUSEY_RUN,
			UNITIALIZED,
			NULL_CLIP
		};

	public:
		Clip();
		Clip(const Clip &) = delete;
		Clip &operator = (const Clip &) = delete;
		~Clip();

		void SetName(Name name);
		Name GetClipName() const;

		AnimTime GetTotalTime(); 
		void SetAnimationDataFromFile(const char* const pFileName);
		void SetAnimationData(clipData& data);
		void AnimateBones(AnimTime tCurr, Bone* bone);
		void AnimateBones(AnimTime tCurr, Mixer* mixer);

	private:
		AnimTime privFindMaxTime();
		int  privFindNumFrames();

	public:
		int          numBones;
		int          numFrames;
		AnimTime     TotalTime;
		FrameBucket *poHead;
		Name name;
	};
}

#endif

//--- End of File ---
