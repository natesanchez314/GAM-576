#ifndef ANIM_CONTROLLER_MAN_H
#define ANIM_CONTROLLER_MAN_H

#include "ManBase.h"
#include "AnimController.h"

namespace Azul
{
	class AnimControllerMan : public ManBase
	{
	private:
		static AnimControllerMan* instance;

		AnimControllerMan() = delete;
		AnimControllerMan(int reserveNum, int reserveGrow);
		AnimControllerMan(const AnimControllerMan&) = delete;
		AnimControllerMan& operator=(const AnimControllerMan&) = delete;
		~AnimControllerMan();

		static AnimControllerMan* GetInstance();

	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();
		static AnimController* Add(Anim* anim, AnimTime delta);
		static AnimController* Add(Anim::Name name, AnimTime delta);
		static AnimController* Find(Anim::Name name);
		static void Remove(AnimController* anim);
		static void Update();

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif // !ANIM_MAN_H
