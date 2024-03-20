#include "GameObjectFont.h"
#include "GlyphMan.h"

namespace Azul
{
	GameObjectFont::GameObjectFont(GraphicsObject_Sprite* pGraphicsObject)
		: GameObject2D(pGraphicsObject), name(Glyph::Name::UNITIALIZED), xStart{ 0 }, yStart{ 0 }
	{ }

	GameObjectFont::~GameObjectFont()
	{
		delete[] message;
	}

	void GameObjectFont::Set(const char* const _message, Glyph::Name _name, float _xStart, float _yStart)
	{
		size_t msgSize = strlen(_message) + 1;
		this->message = new char[GameObjectFont::MESSAGE_SIZE]();
		strcat_s(this->message, msgSize, _message);
		//this->message = _message;
		this->name = _name;
		this->xStart = _xStart;
		this->yStart = _yStart;
	}

	void GameObjectFont::Draw()
	{
		if (this->mDrawEnable)
		{
			float tmpX = this->xStart;
			float tmpY = this->yStart;
			float tmpWidth = this->scaleY;

			float endX = this->xStart;

			size_t msgSize = strlen(this->message);
			for (int i = 0; i < (int)msgSize; i++)
			{
				unsigned int key = (unsigned int)this->message[i];

				Glyph* glyph = GlyphMan::Find(this->name, key);

				tmpX = endX + glyph->GetRect().width / 2;
				this->posX = tmpX;
				this->posY = tmpY;
				this->scaleX = glyph->GetRect().width;

				GraphicsObject_Sprite* pGraphicsObj = (GraphicsObject_Sprite*)this->GetGraphicsObject();
				this->privUpdate();
				pGraphicsObj->UpdateImage(glyph->GetRect());
				pGraphicsObj->Render();

				endX = glyph->GetRect().width / 2 + tmpX;
				this->scaleX = tmpWidth;
			}
		}
	}

	void GameObjectFont::UpdateMessage(const char* const newMsg)
	{
		size_t msgSize = strlen(newMsg) + 1;
		memset(this->message, 0, strlen(this->message));
		strcat_s(this->message, msgSize, newMsg);
	}

	void GameObjectFont::privUpdate()
	{
		// Goal: update the world matrix
		Mat4 Scale(Mat4::Scale::XYZ, this->scaleX, this->scaleY, 1.0f);
		Mat4 Rot(Mat4::Rot1::Z, this->angle);
		Mat4 Trans(Mat4::Trans::XYZ, this->posX, this->posY, 0.0f);

		*this->poWorld = Scale * Rot * Trans;

		// push to graphics object
		this->poGraphicsObject->SetWorld(*this->poWorld);
	}
}