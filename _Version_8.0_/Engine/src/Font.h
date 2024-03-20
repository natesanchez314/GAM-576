#ifndef FONT_H
#define FONT_H

#include "Glyph.h"
#include "fontData.h"
#include "DLink.h"
#include "Texture.h"
#include "Rect.h"
#include "GameObjectFont.h"
#include "Mesh.h"
#include "ShaderObject.h"

namespace Azul
{
	class Font : public DLink
	{
	public:
		enum class Name
		{
			DEFAULT,
			ANIM_A,
			ANIM_B,
			COUNT,
			UNINITIALIZED
		};

		Name name;
		GameObjectFont* sprite;

	public:
		Font();
		Font(const Font& other) = delete;
		Font& operator=(const Font& other) = delete;
		~Font();

		void UpdateMessage(const char* const newMsg);

		void Set(Name name, Mesh::Name mName, ShaderObject::Name sName, const char* const message, Glyph::Name gName, float xStart, float yStart);
	};
}

#endif // !FONT_H
