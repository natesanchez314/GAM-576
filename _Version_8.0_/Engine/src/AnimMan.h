#ifndef ANIM_MAN_H
#define ANIM_MAN_H

#include "ManBase.h"
#include "Anim.h"
#include "Bone.h"
#include "Clip.h"

namespace Azul
{
	class AnimMan : public ManBase
	{
	private:
		static AnimMan* instance;

		AnimMan() = delete;
		AnimMan(int reserveNum, int reserveGrow);
		AnimMan(const AnimMan&) = delete;
		AnimMan& operator=(const AnimMan&) = delete;
		~AnimMan();

		static AnimMan* GetInstance();

	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();
		static Anim* Add(Anim::Name name, Clip* clip);
		static Anim* Find(Anim::Name name);
		static void Remove(Anim* anim);

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif // !ANIM_MAN_H
