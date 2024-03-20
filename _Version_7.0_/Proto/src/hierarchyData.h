#ifndef HIERARCHY_DATA_H
#define HIERARCHY_DATA_H

#include "hierarchyData.pb.h"

namespace Azul
{
	class hierarchyData
	{
	public:
		unsigned int count;
		unsigned int maxDepth;
		unsigned int* data;

		hierarchyData();
		hierarchyData(unsigned int count, unsigned int maxDepth);
		hierarchyData(const hierarchyData&) = delete;
		hierarchyData& operator=(const hierarchyData&) = delete;
		~hierarchyData();

		void Serialize(hierarchyData_proto& out) const;
		void Deserialize(const hierarchyData_proto& in);
	};
}

#endif // !HIERARCHY_DATA_H
