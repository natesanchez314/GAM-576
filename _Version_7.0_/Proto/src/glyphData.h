#ifndef GLYPH_DATA_H
#define GLYPH_DATA_H

#include "glyphData.pb.h"

namespace Azul
{
	class glyphData
	{
	public:
		unsigned int key;
		float x;
		float y;
		float width;
		float height;

		glyphData();
		glyphData(unsigned int key, float x, float y, float width, float height);
		glyphData(const glyphData&) = delete;
		glyphData& operator=(const glyphData&) = delete;
		~glyphData();

		void Serialize(glyphData_proto& out) const;
		void Deserialize(const glyphData_proto& in);
	};
}

#endif // !GLYPH_DATA_H
