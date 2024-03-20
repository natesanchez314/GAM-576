#ifndef FONT_DATA_H
#define FONT_DATA_H

#include "fontData.pb.h"
#include "glyphData.h"

namespace Azul
{
	class fontData
	{
	public:
		unsigned int count;
		glyphData* glyphs;

		fontData();
		fontData(const fontData&) = delete;
		fontData& operator=(const fontData&) = delete;
		~fontData();

		void Serialize(fontData_proto& out) const;
		void Deserialize(const fontData_proto& in);
	};
}

#endif // !FONT_DATA_H
