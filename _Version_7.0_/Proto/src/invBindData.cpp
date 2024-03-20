#include "invBindData.h"

namespace Azul
{
	invBindData::invBindData()
		: count(0), data(nullptr)
	{ }

	invBindData::invBindData(unsigned int count)
		: count(count), data(nullptr)
	{
		this->data = new float[count * 16]();
	}

	invBindData::~invBindData()
	{ 
		delete[] data;
	}

	void invBindData::Serialize(invBindData_proto& out) const
	{ 
		out.set_count(this->count);
		for (unsigned int i = 0; i < count * 16; i++)
			out.add_data(this->data[i]);
	}

	void invBindData::Deserialize(const invBindData_proto& in)
	{ 
		this->count = in.count();
		this->data = new float[this->count * 16]();
		for (unsigned int i = 0; i < count * 16; i++)
			this->data[i] = in.data(i);
	}
}
