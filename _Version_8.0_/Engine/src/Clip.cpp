// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"
#include "File.h"

namespace Azul
{
	Clip::Clip()
	: numBones(0),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{ }

	Clip::~Clip()
	{
		FrameBucket *pTmp = poHead;

		while (pTmp != nullptr)
		{
			FrameBucket *pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	void Clip::AnimateBones(AnimTime tCurr, Bone* bone)
	{
		Trace::out2("BoneCount: %d", this->numBones);
		// First one 
		FrameBucket *pTmp = this->poHead;
		
		// Find which key frames
		while(tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}
		
		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket *pA = pTmp->prevBucket;
		FrameBucket *pB = pTmp;
		
		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(bone, pA->poBone, pB->poBone, tS, this->numBones);
	}

	void Clip::AnimateBones(AnimTime tCurr, Mixer* mixer)
	{
		assert(mixer);
		//Trace::out2("BoneCount: %d", this->numBones);
		// First one 
		FrameBucket* pTmp = this->poHead;

		// Find which key frames
		while (tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket* pA = pTmp->prevBucket;
		FrameBucket* pB = pTmp;

		mixer->frameA = pA->ssbo;
		mixer->frameB = pB->ssbo;

		// find the "S" of the time
		mixer->ts = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		mixer->Update();
	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket *pTmp = this->poHead;

		while (pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	void Clip::SetName(Name _name)
	{
		this->name = _name;
	}

	Clip::Name Clip::GetClipName() const
	{
		return this->name;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}

	float scale = 1.0f;

	void Clip::SetAnimationDataFromFile(const char* const pFileName)
	{
		File::Handle handle;
		File::Error err;
		DWORD fileLen;

		err = File::Open(handle, pFileName, File::Mode::READ);
		err = File::Seek(handle, File::Position::END, 0);
		err = File::Tell(handle, fileLen);
		err = File::Seek(handle, File::Position::BEGIN, 0);

		char* buff = new char[fileLen]();

		err = File::Read(handle, buff, fileLen);
		err = File::Close(handle);

		std::string strIn(buff, fileLen);
		delete[] buff;

		clipData_proto clipProto;
		clipProto.ParseFromString(strIn);

		clipData clip;
		clip.Deserialize(clipProto);

		this->SetAnimationData(clip);
		//this->privSetAnimationData();
		this->TotalTime = this->privFindMaxTime();
		this->numFrames = this->privFindNumFrames();
	}

	void Clip::SetAnimationData(clipData& clip)
	{
		FrameBucket* tmpFramePrev = nullptr;
		FrameBucket* tmpFrame = nullptr;

		for (unsigned int i = 0; i < clip.count; i++)
		{
			tmpFrame = new FrameBucket();
			tmpFrame->prevBucket = tmpFramePrev;
			tmpFrame->nextBucket = nullptr;
			tmpFrame->KeyTime = (int)i * AnimTime(AnimTime::Duration::FILM_24_FRAME);


			unsigned int boneCount = clip.frames[i].count;
			this->numBones = (int)boneCount;
			tmpFrame->poBone = new Bone[boneCount]();

			for (unsigned int j = 0; j < boneCount; j++)
			{
				tmpFrame->poBone[j].T = Vec3(
					clip.frames[i].bones[j].t.x,
					clip.frames[i].bones[j].t.y,
					clip.frames[i].bones[j].t.z);
				tmpFrame->poBone[j].Q = Quat(
					clip.frames[i].bones[j].q.v.x,
					clip.frames[i].bones[j].q.v.y,
					clip.frames[i].bones[j].q.v.z,
					clip.frames[i].bones[j].q.real);
				tmpFrame->poBone[j].S = Vec3(
					clip.frames[i].bones[j].s.x,
					clip.frames[i].bones[j].s.y,
					clip.frames[i].bones[j].s.z);
			}
			tmpFrame->ssbo.Set(boneCount, sizeof(Bone), tmpFrame->poBone);

			if (tmpFramePrev != nullptr)
				tmpFramePrev->nextBucket = tmpFrame;
			if (this->poHead == nullptr)
				this->poHead = tmpFrame;

			tmpFramePrev = tmpFrame;
		}

		assert(this->poHead != nullptr);
	}
}

// --- End of File ---
