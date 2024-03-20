#ifndef BONE_CONTAINER_H
#define BONE_CONTAINER_H

#include "boneContainer.pb.h"

namespace Azul
{
	class boneContainer
	{
	public:
		static const unsigned int SKELETON_NAME_SIZE = 64;

		int index;
		int parentIndex;
		char nodeName[SKELETON_NAME_SIZE];

		boneContainer();
		boneContainer(const boneContainer&) = delete;
		boneContainer& operator=(const boneContainer&) = delete;
		~boneContainer();

		void Serialize(boneContainer_proto& out) const;
		void Deserialize(const boneContainer_proto& in);

		void Print() const;
	};
}

#endif // !BONE_CONTAINER_H
