#include "Font.h"
#include "fontData.pb.h"
#include "GraphicsObject_Sprite.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "TextureMan.h"
#include "GameObjectMan.h"
#include "ImageMan.h"

namespace Azul
{
	Font::Font()
		: name(Name::UNINITIALIZED), sprite(nullptr)
	{ }

	Font::~Font()
	{ 
		//delete this->sprite;
		//sprite = nullptr;
	}

	void Font::Set(Font::Name _name, Mesh::Name mName, ShaderObject::Name sName, const char* const message, Glyph::Name gName, float xStart, float yStart)
	{
		Image* image = new Image(Image::Name::FONT, Texture::Name::FONT, Rect(45.0f, 160.0f, 21.0f, 30.0f));
		ImageMan::Add(image);
		this->name = _name;
		GraphicsObject_Sprite* gos = new GraphicsObject_Sprite(
			MeshNodeMan::Find(mName),
			ShaderMan::Find(sName),
			image, 
			Rect(xStart, yStart, 1, 1));
		this->sprite = new GameObjectFont(gos);
		GameObjectMan::Add(this->sprite, GameObjectMan::GetRoot());
		this->sprite->Set(message, gName, xStart, yStart);
		this->sprite->scaleX = 20;
		this->sprite->scaleY = 20;
	}

	void Font::UpdateMessage(const char* const newMsg)
	{
		this->sprite->UpdateMessage(newMsg);
	}
}