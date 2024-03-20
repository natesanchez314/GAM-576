#ifndef SPRITE_DATA_H
#define SPRITE_DATA_H

#include "spriteData.pb.h"
#include "vboData.h"

namespace Azul
{
	class spriteData
	{
	public:
		unsigned int triCount;
		unsigned int vertCount;
		vboData vbo_vert;
		vboData vbo_uv;
		vboData vbo_index;

		spriteData();
		spriteData(const spriteData&) = delete;
		spriteData& operator=(const spriteData&) = delete;
		~spriteData();

		void Serialize(spriteData_proto& out) const;
		void Deserialize(const spriteData_proto& in);
	};
}

#endif // !SPRITE_DATA_H
