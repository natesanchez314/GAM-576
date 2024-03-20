//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mixer.h"
#include "MathApp.h"
#include "ShaderObject.h"
#include "ShaderMan.h"
#include "Anim.h"
#include <cmath>

namespace Azul
{
	Mixer::Mixer(Anim* anim)
		:frameA(), frameB(), frameRes(), ts(0.0f), boneCount(anim->numBones), shader(nullptr)
	{ 
		this->frameRes = anim->ssboRes;
		this->shader = ShaderMan::Find(ShaderObject::Name::MIXER);
	}
	
	Mixer::~Mixer()
	{ }

	void Mixer::Update()
	{
		this->shader->SetActive();

		this->frameA.Bind(0);
		this->frameB.Bind(1);
		this->frameRes.Bind(2);

		glUniform1f(this->shader->GetLocation("ts"), ts);
		glUniform1i(this->shader->GetLocation("boneCount"), this->boneCount);

		unsigned int count = (unsigned int)ceil((float)(this->boneCount)/ 8.0f);
		this->shader->Dispatch(count, 1, 1);

		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}

	void Mixer::Blend(
		Bone *pResult,
		const Bone *pA,
		const Bone *pB,
		const float tS,
		int numBones)
	{
		// Interpolate to tS time, for all bones
		for (int i = 0; i < numBones; i++)
		{
			// interpolate ahoy!
			Vec3App::Lerp(pResult->T, pA->T, pB->T, tS);
			QuatApp::Slerp(pResult->Q, pA->Q, pB->Q, tS);
			Vec3App::Lerp(pResult->S, pA->S, pB->S, tS);

			// advance the pointer
			pA++;
			pB++;
			pResult++;
		}
	}
}

// --- End of File ---
