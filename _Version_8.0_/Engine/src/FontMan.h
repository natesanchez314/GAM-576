#ifndef FONT_MAN_H
#define FONT_MAN_H

#include "ManBase.h"
#include "Font.h"

namespace Azul
{
	class FontMan : public ManBase
	{
	private:
		//FontMan* nodeCompare;
		static FontMan* instance;

	public:
		static void Create(int reservNum = 0, int reserveGrow = 1);
		static void Destroy();
		static Font* Add(Font::Name name, Mesh::Name mName, ShaderObject::Name sName, const char* const message, Glyph::Name gName, float xStart, float yStart);
		static Font* Find(Font::Name name);
		static void Remove(Font* font);
		static void Dump();

	private:
		static FontMan* GetInstance();

		FontMan() = delete;
		FontMan(int reserveNum, int reserveGrow);
		FontMan(const FontMan&) = delete;
		FontMan& operator=(const FontMan&) = delete;
		~FontMan();

	protected:
		DLink* derivedCreateNode() override;
	};
}

#endif // !FONT_MAN_H
