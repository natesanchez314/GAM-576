#ifndef GLYPH_MAN_H
#define GLYPH_MAN_H

#include "ManBase.h"
#include "Glyph.h"

namespace Azul
{
	class GlyphMan : public ManBase
	{
	private:
		static GlyphMan* instance;

	public:
		static void Create(int reservNum = 0, int reserveGrow = 1);
		static void Destroy();
		static void AddGlyphs(Glyph::Name name, const char* const fileName, Texture::Name textName);
		static Glyph* Find(Glyph::Name name, unsigned int key);
		static void Remove(Glyph* glyph);
		static void Dump();

	private:
		static GlyphMan* GetInstance();

		GlyphMan() = delete;
		GlyphMan(int reserveNum, int reserveGrow);
		GlyphMan(const GlyphMan&) = delete;
		GlyphMan& operator=(const GlyphMan&) = delete;
		~GlyphMan();

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif // !GLYPH_MAN_H
