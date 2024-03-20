#include "boneContainer.h"

namespace Azul
{
	boneContainer::boneContainer()
		: index{0}, parentIndex{0}, nodeName{0}
	{ }

	boneContainer::~boneContainer()
	{ }

	void boneContainer::Serialize(boneContainer_proto& out) const
	{ 
		out.set_index(this->index);
		out.set_parentindex(this->parentIndex);
		std::string name((const char*)this->nodeName, boneContainer::SKELETON_NAME_SIZE);
		out.set_nodename(name);
	}

	void boneContainer::Deserialize(const boneContainer_proto& in)
	{ 
		this->index = in.index();
		this->parentIndex = in.parentindex();
		memcpy_s(this->nodeName, 
			boneContainer::SKELETON_NAME_SIZE,
			in.nodename().data(), 
			boneContainer::SKELETON_NAME_SIZE);
	}

	void boneContainer::Print() const
	{
		Trace::out("{%2d, %2d, \"%s\" },\n",
			this->index,
			this->parentIndex,
			this->nodeName);
	}
}
