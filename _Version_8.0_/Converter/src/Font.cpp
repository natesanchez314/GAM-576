#include "Font.h"
#include "File.h"
#include "textureData.h"
#include "GLTF.h"
#include "CreateTexture.h"
#include "pugixml.hpp"
#include "glyphData.h"
#include "fontData.h"
#include "fontData.pb.h"
#include <vector>

using namespace tinygltf;

namespace Azul
{
    void CreateFontAndTexture(const char* const textureFileName, const char* const xmlFileName)
    {
        const char* inFileExt = ".png";
        const char* outFileExt = ".font.proto.azul";

        size_t inFileNameSize = strlen(textureFileName) + strlen(inFileExt) + 1;
        size_t outFileNameSize = strlen(textureFileName) + strlen(outFileExt) + 1;

        char* inFileName = new char[inFileNameSize]();
        strcat_s(inFileName, inFileNameSize, textureFileName);
        strcat_s(inFileName, inFileNameSize, inFileExt);

        char* outFileName = new char[outFileNameSize]();
        strcat_s(outFileName, outFileNameSize, textureFileName);
        strcat_s(outFileName, outFileNameSize, outFileExt);

        CreateTexturePNG(inFileName);

        pugi::xml_document doc;
        pugi::xml_parse_result res = doc.load_file(xmlFileName);
        assert(res);
        unsigned int nodeCount = 0;

        pugi::xml_node node;
        
        //std::vector<glyphData*> tmpGlyphs;
        for (node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
        {
            //glyphData* glyph = new glyphData();
            //glyph->key = node.attribute("key").as_uint();
            //glyph->x = node.child("x").text().as_float();
            //glyph->y = node.child("y").text().as_float();
            //glyph->width = node.child("width").text().as_float();
            //glyph->height = node.child("height").text().as_float();
            //tmpGlyphs.push_back(glyph);
            nodeCount++;
        }

        fontData font;
        font.count = nodeCount;
        font.glyphs = new glyphData[nodeCount]();

        int i = 0;
        for (node = doc.child("fontMetrics").child("character"); node; node = node.next_sibling("character"))
        {
            font.glyphs[i].key = node.attribute("key").as_uint();
            font.glyphs[i].x = node.child("x").text().as_float();
            font.glyphs[i].y = node.child("y").text().as_float();
            font.glyphs[i].width = node.child("width").text().as_float();
            font.glyphs[i].height = node.child("height").text().as_float();
            glyphData* glyph = &font.glyphs[i];
            i++;
        }

        fontData_proto protoFont;
        font.Serialize(protoFont);

        File::Handle handle;
        File::Error err;
        
        err = File::Open(handle, outFileName, File::Mode::WRITE);

        std::string strOut;
        protoFont.SerializeToString(&strOut);

        err = File::Write(handle, strOut.data(), strOut.length());

        err = File::Close(handle);

        delete[] inFileName;
        delete[] outFileName;
    }
}