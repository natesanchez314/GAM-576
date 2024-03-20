#ifndef INV_BIND_DATA_H
#define INV_BIND_DATA_H

#include "invBindData.pb.h"

namespace Azul
{
	class invBindData
	{
	public:
		unsigned int count;
		float* data;

		invBindData();
		invBindData(unsigned int count);
		invBindData(const invBindData&) = delete;
		invBindData& operator=(const invBindData&) = delete;
		~invBindData();

		void Serialize(invBindData_proto& out) const;
		void Deserialize(const invBindData_proto& in);
	};
}

#endif // !INV_BIND_H
