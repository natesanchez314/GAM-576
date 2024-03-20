#include "spriteData.h"

namespace Azul
{
	spriteData::spriteData()
		: triCount{0}, vertCount{0}, vbo_vert(), vbo_uv(), vbo_index()
	{ }

	spriteData::~spriteData()
	{ }

	void spriteData::Serialize(spriteData_proto& out) const
	{ 
		out.set_tricount(this->triCount);
		out.set_vertcount(this->vertCount);
		this->vbo_vert.Serialize(*out.mutable_vbo_vert());
		this->vbo_uv.Serialize(*out.mutable_vbo_uv());
		this->vbo_index.Serialize(*out.mutable_vbo_index());
	}

	void spriteData::Deserialize(const spriteData_proto & in)
	{ 
		this->triCount = in.tricount();
		this->vertCount = in.vertcount();
		this->vbo_vert.Deserialize(in.vbo_vert());
		this->vbo_uv.Deserialize(in.vbo_uv());
		this->vbo_index.Deserialize(in.vbo_index());
	}
}