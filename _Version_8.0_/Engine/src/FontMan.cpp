#include "FontMan.h"
#include "File.h"
#include "fontData.h"
#include "fontData.pb.h"
#include "TextureMan.h"
#include "GameObjectMan.h"

namespace Azul
{
	FontMan* FontMan::instance = nullptr;

	void FontMan::Create(int reservNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new FontMan(reservNum, reserveGrow);
	}

	void FontMan::Destroy()
	{
		FontMan* man = FontMan::GetInstance();
		delete man;
		instance = nullptr;
	}

	Font* FontMan::Add(Font::Name name, Mesh::Name mName, ShaderObject::Name sName, const char* const message, Glyph::Name gName, float xStart, float yStart)
	{
		FontMan* man = FontMan::GetInstance();
		Font* font = (Font*)man->baseAddToFront();

		font->Set(name, mName, sName, message, gName, xStart, yStart);

		//GameObjectMan::Add(font->sprite, GameObjectMan::GetRoot());
		font->sprite->DrawEnable();

		return font;
	}

	Font* FontMan::Find(Font::Name name)
	{
		FontMan* man = FontMan::GetInstance();

		Iterator* iter = man->baseGetActiveIterator();

		for (Font* font = (Font*)iter->First(); !iter->IsDone(); font = (Font*)iter->Next())
		{
			if (font->name == name)
				return font;
		}

		return nullptr;
	}

	void FontMan::Remove(Font* font)
	{
		FontMan* man = FontMan::GetInstance();

		man->baseRemove(font);
	}

	void FontMan::Dump()
	{
		FontMan* man = FontMan::GetInstance();

		man->baseDump();
	}

	FontMan* FontMan::GetInstance()
	{
		return FontMan::instance;
	}

	FontMan::FontMan(int reserveNum, int reserveGrow)
		: ManBase(reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	FontMan::~FontMan()
	{
		Iterator* iter = this->baseGetActiveIterator();

		Font* node = (Font*)iter->First();

		while (!iter->IsDone())
		{
			Font* deleteNode = (Font*)iter->Curr();
			node = (Font*)iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();

		node = (Font*)iter->First();

		while (!iter->IsDone())
		{
			Font* deleteNode = (Font*)iter->Curr();
			node = (Font*)iter->Next();
			delete deleteNode;
		}
	}

	DLink* FontMan::derivedCreateNode()
	{
		DLink* node = new Font();

		return node;
	}
}