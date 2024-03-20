#ifndef GAME_OBJECT_FONT_H
#define GAME_OBJECt_FONT_H

#include "GameObject2D.h"
#include "Rect.h"
#include "Glyph.h"

namespace Azul
{
	class GameObjectFont : public GameObject2D
	{
	private:
		static const unsigned int MESSAGE_SIZE = 64;

		char* message;

	public:
		Glyph::Name name;
		float xStart;
		float yStart;

		GameObjectFont() = delete;
		GameObjectFont(GraphicsObject_Sprite* graphicsObject);
		GameObjectFont(const GameObjectFont&) = delete;
		GameObjectFont& operator=(const GameObject&) = delete;
		virtual ~GameObjectFont() override;

		void Set(const char* const message, Glyph::Name name, float xStart, float yStart);
		virtual void Draw() override;

		void UpdateMessage(const char* const newMsg);

	private:
		void privUpdate();
	};
}

#endif // !GAME_OBJECT_FONT_H
