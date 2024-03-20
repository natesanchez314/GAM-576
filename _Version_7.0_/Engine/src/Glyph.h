#ifndef GLYPH_H
#define GLYPH_H

#include "DLink.h"
#include "Texture.h"
#include "Rect.h"

namespace Azul
{
	class Glyph : public DLink
	{
	public:

		enum class Name
		{
			DEFAULT,
			UNITIALIZED
		};

		Name name;
		unsigned int key;

	private:
		Rect rect;
		Texture* texture;
	
	public:
		Glyph();
		Glyph(unsigned int key, float x, float y, float width, float height);
		Glyph(const Glyph& other) = delete;
		Glyph& operator=(const Glyph& other) = delete;
		~Glyph();

		void Set(Name name, unsigned int key, Texture::Name textName, float x, float y, float width, float height);
		
		Rect GetRect() const;
		Texture* GetTexture() const;
	};
}

#endif // !GLYPH_H
