#include "glyph.h"
#include "TextureMan.h"

namespace Azul
{
	Glyph::Glyph()
		: name(Name::UNITIALIZED), key{ 0 }, rect(), texture(nullptr)
	{ }

	Glyph::Glyph(unsigned int key, float x, float y, float width, float height)
		: key(key), rect(x, y, width, height), texture(nullptr)
	{ }

	Glyph::~Glyph()
	{ 
		// Let texture man handle deleting of the texture
		this->texture = nullptr;
	}

	void Glyph::Set(Name _name, unsigned int _key, Texture::Name textName, float x, float y, float width, float height)
	{
		this->name = _name;
		this->key = _key;
		this->texture = TextureMan::Find(textName);
		this->rect.x = x;
		this->rect.y = y;
		this->rect.width = width;
		this->rect.height = height;
	}

	Rect Glyph::GetRect() const
	{
		return this->rect;
	}

	Texture* Glyph::GetTexture() const
	{
		return this->texture;
	}
}