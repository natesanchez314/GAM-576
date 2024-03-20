#ifndef CLIP_MAN_H
#define CLIP_MAN_H

#include "ManBase.h"
#include "Clip.h"
#include "Bone.h"

namespace Azul
{
	class ClipMan : public ManBase
	{
	private:
		static ClipMan* instance;

		ClipMan() = delete;
		ClipMan(int reserveNum, int reserveGrow);
		ClipMan(const ClipMan&) = delete;
		ClipMan& operator=(const ClipMan&) = delete;
		~ClipMan();

		static ClipMan* GetInstance();

	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();
		static Clip* Add(Clip::Name name, const char* const pFileName);
		static Clip* Find(Clip::Name name);
		static void Remove(Clip* Clip);

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif // !Clip_MAN_H
