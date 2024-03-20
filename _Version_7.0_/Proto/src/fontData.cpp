#include "fontData.h"

namespace Azul
{
	fontData::fontData()
		: count(0), glyphs(nullptr)
	{ }

	fontData::~fontData()
	{ 
		delete[] glyphs;
	}

	void fontData::Serialize(fontData_proto& out) const
	{ 
		out.set_count(this->count);
		for (unsigned int i = 0; i < this->count; i++)
		{
			glyphData_proto* glyph = out.add_glyphs();
			this->glyphs[i].Serialize(*glyph);
		}
	}

	void fontData::Deserialize(const fontData_proto& in)
	{
		this->count = in.count();
		this->glyphs = new glyphData[count]();
		for (unsigned int i = 0; i < this->count; i++)
			this->glyphs[i].Deserialize(in.glyphs()[i]);
	}
}