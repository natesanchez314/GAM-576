#ifndef SKEL_DATA_H
#define SKEL_DATA_H

#include "boneContainer.h"
#include "skelData.pb.h"

namespace Azul
{
	class skelData
	{
	public:
		unsigned int boneCount;
		boneContainer* bones;
		unsigned int jointTableCount;
		unsigned int* jointTable;

		skelData();
		skelData(const skelData&) = delete;
		skelData& operator=(const skelData&) = delete;
		~skelData();

		void Serialize(skelData_proto& out) const;
		void Deserialize(const skelData_proto& in);
	};
}

#endif // !SKEL_DATA_H
