//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MIXER_H
#define MIXER_H

#include "AnimTimer.h"
#include "Bone.h"
#include "SSBO.h"
#include "ShaderObject.h"

namespace Azul
{
	class Anim;

	class Mixer
	{
	public:
		SSBO frameA;
		SSBO frameB;
		SSBO frameRes;
		float ts;
		int boneCount;
		ShaderObject* shader;

		Mixer() = delete;
		Mixer(Anim* anim);
		Mixer(const Mixer&) = delete;
		Mixer& operator=(const Mixer&) = delete;
		~Mixer();

		void Update();

		static void Blend(	Bone *pResult,
							const Bone *pA,
							const Bone *pB,
							const float tS,
							const int numBones);
	};
}

#endif

// --- End of File ---
