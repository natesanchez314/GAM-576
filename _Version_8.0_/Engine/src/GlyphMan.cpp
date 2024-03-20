#include "GlyphMan.h"
#include "File.h"
#include "glyphData.h"
#include "glyphData.pb.h"
#include "fontData.h"
#include "fontData.pb.h"
#include "TextureMan.h"

namespace Azul
{
	GlyphMan* GlyphMan::instance = nullptr;

	void GlyphMan::Create(int reservNum, int reserveGrow)
	{
		if (instance == nullptr)
			instance = new GlyphMan(reservNum, reserveGrow);
	}

	void GlyphMan::Destroy()
	{
		GlyphMan* man = GlyphMan::GetInstance();
		delete man;
		instance = nullptr;
	}
	
	void GlyphMan::AddGlyphs(Glyph::Name name, const char* const fileName, Texture::Name textName)
	{
		AZUL_UNUSED_VAR(name);
		GlyphMan* man = GlyphMan::GetInstance();

		const char* path = "Data\\";
		size_t size = strlen(path) + strlen(fileName) + 1;
		char* fullFileName = new char[size]();
		strcat_s(fullFileName, size, path);
		strcat_s(fullFileName, size, fileName);

		File::Handle handle;
		File::Error err;
		DWORD length;
		
		err = File::Open(handle, fullFileName, File::Mode::READ);
		err = File::Seek(handle, File::Position::END, 0);
		err = File::Tell(handle, length);
		err = File::Seek(handle, File::Position::BEGIN, 0);
		
		char* buff = new char[length];
		
		err = File::Read(handle, buff, length);
		err = File::Close(handle);
		
		std::string strIn(buff, length);

		fontData_proto fontProto;

		fontProto.ParseFromString(strIn);

		fontData fData;
		fData.Deserialize(fontProto);

		delete[] buff;
		delete fullFileName;

		assert(fData.count != 0);

		for (unsigned int i = 0; i < fData.count; i++)
		{
			Glyph* glyph = (Glyph*)man->baseAddToFront();

			glyph->Set(
				name, 
				fData.glyphs[i].key, 
				textName, 
				fData.glyphs[i].x, 
				fData.glyphs[i].y, 
				fData.glyphs[i].width, 
				fData.glyphs[i].height);
		}
	}
	
	Glyph* GlyphMan::Find(Glyph::Name name, unsigned int key)
	{
		GlyphMan* man = GlyphMan::GetInstance();

		Iterator* iter = man->baseGetActiveIterator();

		for (Glyph* glyph = (Glyph*)iter->First(); !iter->IsDone(); glyph = (Glyph*)iter->Next())
		{
			if (glyph->name == name && glyph->key == key)
				return glyph;
		}

		return nullptr;
	}

	void GlyphMan::Remove(Glyph* glyph)
	{
		GlyphMan* man = GlyphMan::GetInstance();

		man->baseRemove(glyph);
	}

	void GlyphMan::Dump()
	{
		GlyphMan* man = GlyphMan::GetInstance();

		man->baseDump();
	}

	GlyphMan* GlyphMan::GetInstance()
	{
		return GlyphMan::instance;
	}

	GlyphMan::GlyphMan(int reserveNum, int reserveGrow)
		: ManBase(reserveGrow)
	{
		this->proFillReservedPool(reserveNum);
	}

	GlyphMan::~GlyphMan()
	{
		Iterator* iter = this->baseGetActiveIterator();

		Glyph* node = (Glyph*)iter->First();

		while (!iter->IsDone())
		{
			Glyph* deleteNode = (Glyph*)iter->Curr();
			node = (Glyph*)iter->Next();
			delete deleteNode;
		}

		iter = this->baseGetReserveIterator();

		node = (Glyph*)iter->First();

		while (!iter->IsDone())
		{
			Glyph* deleteNode = (Glyph*)iter->Curr();
			node = (Glyph*)iter->Next();
			delete deleteNode;
		}
	}

	DLink* GlyphMan::derivedCreateNode()
	{
		DLink* node = new Glyph();

		return node;
	}
}