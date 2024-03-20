#include "skelData.h"

namespace Azul
{
	skelData::skelData()
		: boneCount{ 0 }, bones(nullptr), jointTableCount{ 0 }, jointTable(nullptr)
	{ }

	skelData::~skelData()
	{ 
		delete[] this->bones;
		delete[] this->jointTable;
	}

	void skelData::Serialize(skelData_proto& out) const
	{ 
		out.set_bonecount(this->boneCount);
		boneContainer_proto* boneContainer = nullptr;
		for (unsigned int i = 0; i < this->boneCount; i++)
		{
			boneContainer = out.add_bones();
			this->bones[i].Serialize(*boneContainer);
		}
		out.set_jointtablecount(this->jointTableCount);
		for (unsigned int i = 0; i < this->jointTableCount; i++)
			out.add_jointtable(this->jointTable[i]);
	}

	void skelData::Deserialize(const skelData_proto& in)
	{ 
		this->boneCount = in.bonecount();
		this->bones = new boneContainer[boneCount]();
		for (unsigned int i = 0; i < this->boneCount; i++)
			this->bones[i].Deserialize(in.bones()[i]);
		this->jointTableCount = in.jointtablecount();
		this->jointTable = new unsigned int[jointTableCount]();
		for (unsigned int i = 0; i < this->jointTableCount; i++)
			this->jointTable[i] = in.jointtable()[i];
	}
}