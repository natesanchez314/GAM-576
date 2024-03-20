#ifndef SKEL_MAN_H
#define SKEL_MAN_H

#include "ManBase.h"
#include "Skeleton.h"

namespace Azul
{
	class SkelMan : public ManBase
	{
	private:
		static SkelMan* instance;

		SkelMan() = delete;
		~SkelMan();
		SkelMan(int reserveNum, int reserveGrow);
		SkelMan(const SkelMan&) = delete;
		SkelMan& operator=(const SkelMan&) = delete;

		static SkelMan* GetInstance();

	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();
		static Skeleton* Add();
		static Skeleton* Find();
		static void Remove(Skeleton* skel);

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif
