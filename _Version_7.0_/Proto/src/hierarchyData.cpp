#include "hierarchyData.h"

namespace Azul
{
	hierarchyData::hierarchyData()
		: count(0), maxDepth(0), data(nullptr)
	{ }

	hierarchyData::hierarchyData(unsigned int count, unsigned int maxDepth)
		: count(count), maxDepth(maxDepth), data(nullptr)
	{ 
		this->data = new unsigned int[count * maxDepth]();
	}

	hierarchyData::~hierarchyData()
	{ 
		delete[] this->data;
	}

	void hierarchyData::Serialize(hierarchyData_proto& out) const
	{ 
		out.set_count(this->count);
		out.set_maxdepth(this->maxDepth);
		for (unsigned int i = 0; i < (count * maxDepth); i++)
			out.add_data(this->data[i]);
	}

	void hierarchyData::Deserialize(const hierarchyData_proto& in)
	{ 
		delete[] this->data;
		this->count = in.count();
		this->maxDepth = in.maxdepth();
		this->data = new unsigned int[(count * maxDepth)]();
		for (unsigned int i = 0; i < (count * maxDepth); i++)
			data[i] = in.data(i);
	}
}