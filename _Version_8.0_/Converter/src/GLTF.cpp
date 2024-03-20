//#include "tiny_gltf.h"
#include "GLTF.h"
#include "File.h"
#include "textureDataConverter.h"
#include "vboDataConverter.h"

using namespace tinygltf;

namespace Azul
{

	bool GLTF::LoadASCII(Model &model, const char *const pFileName)
	{
		TinyGLTF loader;
		std::string err;
		std::string warn;

		bool status = loader.LoadASCIIFromFile(&model, &err, &warn, pFileName);

		if(!warn.empty())
		{
			Trace::out("Warn: %s\n", warn.c_str());
			assert(false);
		}

		if(!err.empty())
		{
			Trace::out("Err: %s\n", err.c_str());
			assert(false);
		}

		if(!status)
		{
			Trace::out2("Failed to parse glTF\n");
			assert(false);
		}

		return status;
	}

	bool GLTF::LoadBinary(Model &model, const char *const pFileName)
	{
		TinyGLTF loader;
		std::string err;
		std::string warn;

		bool status = loader.LoadBinaryFromFile(&model, &err, &warn, pFileName);

		if(!warn.empty())
		{
			Trace::out("Warn: %s\n", warn.c_str());
			assert(false);
		}

		if(!err.empty())
		{
			Trace::out("Err: %s\n", err.c_str());
			assert(false);
		}

		if(!status)
		{
			Trace::out2("Failed to parse glTF\n");
			assert(false);
		}

		return status;
	}

	bool GLTF::GetGLBRawBuffer(char *&pBuff, unsigned int &BuffSize, const char *const pFileName)
	{
		File::Handle fh;
		File::Error err;

		err = File::Open(fh, pFileName, File::Mode::READ);
		assert(err == File::Error::SUCCESS);

		err = File::Seek(fh, File::Position::END, 0);
		assert(err == File::Error::SUCCESS);

		DWORD FileSize(0);
		err = File::Tell(fh, FileSize);
		assert(err == File::Error::SUCCESS);

		// Cast it down to 32-bit size (limit 4GB)
		BuffSize = (unsigned int)FileSize;
		pBuff = new char[BuffSize]();
		assert(pBuff);

		err = File::Seek(fh, File::Position::BEGIN, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Read(fh, pBuff, BuffSize);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		assert(pBuff);
		assert(BuffSize > 0);

		return true;
	}

	bool GLTF::GetGLBHeader(GLB_header &header, const char *const pBuff, unsigned int BuffSize)
	{
		GLB_header *pGlbHeader;

		pGlbHeader = (GLB_header *)&pBuff[0];
		assert(pGlbHeader);

		// boundary check
		assert((char *)(pGlbHeader + 1) < (pBuff + BuffSize));

		assert(pGlbHeader->version == 2);
		assert(pGlbHeader->magic == 0x46546C67);

		header = *pGlbHeader;

		return true;
	}

	bool GLTF::GetRawJSON(char *&pJSON, unsigned int &JsonSize, const char *const pBuff, unsigned int BuffSize)
	{
		// BEGINNING...
		GLB_header *pGlbHeader;

		pGlbHeader = (GLB_header *)&pBuff[0];
		assert(pGlbHeader);

		// boundary check
		assert((char *)(pGlbHeader + 1) < (pBuff + BuffSize));

		// Now this next is CHUNK header
		CHUNK_header *pChunkHdr;
		pChunkHdr = (CHUNK_header *)(pGlbHeader + 1);

		assert(pChunkHdr->chunkType == 0x4E4F534A);
		JsonSize = pChunkHdr->chunkLength;
		pJSON = new char[JsonSize + 1]();
		memset(pJSON, 0, JsonSize + 1);
		memcpy(pJSON, (char *)pChunkHdr->chunkData, JsonSize);

		// boundary check - bottom of header
		assert((char *)(pChunkHdr + 1) < (pBuff + BuffSize));

		// boundary check - bottom of data
		//char *pA = (char *)(pChunkHdr + 1) + pChunkHdr->chunkLength;
		//char *pB = (char *)(pBuff + BuffSize);
		assert(((char *)(pChunkHdr + 1) + pChunkHdr->chunkLength) <= (pBuff + BuffSize));

		assert(pJSON);
		assert(JsonSize > 0);

		return true;
	}


	bool GLTF::GetBinaryBuffPtr(char *&pBinaryBuff, unsigned int &BinaryBuffSize, const char *const pBuff, unsigned int BuffSize)
	{
		// BEGINNING...
		GLB_header *pGlbHeader;

		pGlbHeader = (GLB_header *)&pBuff[0];
		assert(pGlbHeader);

		// Now this next is CHUNK header - JSON
		CHUNK_header *pChunkHdr;
		pChunkHdr = (CHUNK_header *)(pGlbHeader + 1);

		assert(pChunkHdr);
		assert(pChunkHdr->chunkType == 0x4E4F534A);

		//Trace::out("CHUNK Header:\n");
		//Trace::out("\tType: 0x%08x \n", pChunkHdr->chunkType);
		//Trace::out("\tLength: 0x%x %d\n", pChunkHdr->chunkLength, pChunkHdr->chunkLength);

		// Now this next is CHUNK header - Binary
		pChunkHdr = (CHUNK_header *)((uint32_t)(pChunkHdr + 1) + pChunkHdr->chunkLength);

		assert(pChunkHdr->chunkType == 0x004E4942);

		//Trace::out("CHUNK Header:\n");
		//Trace::out("\tType: 0x%08x \n", pChunkHdr->chunkType);
		//Trace::out("\tLength: 0x%x %d\n", pChunkHdr->chunkLength, pChunkHdr->chunkLength);

		BinaryBuffSize = pChunkHdr->chunkLength;
		pBinaryBuff = (char *)pChunkHdr->chunkData;

		assert(((char *)(pChunkHdr + 1) + BinaryBuffSize) <= (pBuff + BuffSize));

		assert(pBinaryBuff);
		assert(BinaryBuffSize > 0);

		return true;

	}

	bool GLTF::GetAzulProtoType(const char *&pProtoFileType, meshData &_meshData)
	{
		bool status = false;

		if(_meshData.vbo_vert.enabled && _meshData.text_color.enabled)
		{
			pProtoFileType = ".mt";
			status = true;
		}
		else if(_meshData.vbo_vert.enabled && !_meshData.text_color.enabled)
		{
			pProtoFileType = ".m";
			status = true;
		}
		else if(!_meshData.vbo_vert.enabled && _meshData.text_color.enabled)
		{
			pProtoFileType = ".t";
			status = true;
		}
		else
		{
			assert(false);
			status = false;
		}

		return status;
	}



	bool GLTF::SetCustomVBO(
		unsigned int AttribIndex,
		const char *pKey,
		vboData &vbo,
		void *pData,
		unsigned int sizeInBytes,
		unsigned int count,
		vboData::VBO_COMPONENT componentType,
		vboData::VBO_TYPE type,
		vboData::VBO_TARGET target)
	{
		AZUL_UNUSED_VAR(pKey);

		vbo.enabled = true;

		vbo.targetType = target;
		vbo.componentType = componentType;
		vbo.vboType = type;

		assert(AttribIndex >= 0);
		vbo.attribIndex = (unsigned int)AttribIndex;
		vbo.count = count;
		vbo.dataSize = sizeInBytes;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

		//GLTF::PrintData((char *)pData, 0, vbo.count, vbo.componentType, vbo.vboType);

		return true;
	}

	bool GLTF::SetCustomVBO_index(
		unsigned int AttribIndex,
		const char *pKey,
		vboData &vbo,
		void *pData,
		unsigned int sizeInBytes,
		unsigned int count,
		vboData::VBO_COMPONENT componentType,
		vboData::VBO_TYPE type,
		vboData::VBO_TARGET target)
	{
		AZUL_UNUSED_VAR(pKey);

		vbo.enabled = true;

		vbo.targetType = target;
		vbo.componentType = componentType;
		vbo.vboType = type;

		assert(AttribIndex >= 0);
		vbo.attribIndex = (unsigned int)AttribIndex;  // not used in index buffers
		vbo.count = count * 3;
		vbo.dataSize = sizeInBytes;

		vbo.poData = new unsigned char[vbo.dataSize]();
		assert(vbo.poData);
		memcpy_s(vbo.poData, vbo.dataSize, pData, vbo.dataSize);

		//	GLTF::PrintData((char *)vbo.poData, 0, vbo.count, vbo.componentType, vbo.vboType);

		return true;
	}

	bool GLTF::SetVBO(Model &gltfModel, unsigned int _AttribIndex, const char *pKey, vboData &vbo, char *pBinaryBuff)
	{
		// Get the accessor, buffer view
		vbo.enabled = false;

		assert(pKey);
		auto map = gltfModel.meshes[0].primitives[0].attributes;
		auto it = map.find(pKey);

		if(it != map.end())
		{
			// Get the accessor, buffer view
			vbo.enabled = true;

			auto index = it->second;

			auto accessor = gltfModel.accessors[(size_t)index];
			size_t buffIndex = (size_t)accessor.bufferView;
			auto bufferView = gltfModel.bufferViews[buffIndex];

			vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
			vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
			vbo.vboType = vboDataConverter::GetType(accessor.type);

			vbo.attribIndex = _AttribIndex;
			vbo.count = accessor.count;
			vbo.dataSize = bufferView.byteLength;

			// poData
			assert(pBinaryBuff);
			char *pBuffStart(nullptr);

			// Start address
			pBuffStart = pBinaryBuff + bufferView.byteOffset;

			// in case there's data
			delete[] vbo.poData;

			vbo.poData = new unsigned char[vbo.dataSize]();
			assert(vbo.poData);
			memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);

			//		GLTF::PrintData(pBinaryBuff, bufferView.byteOffset, vbo.count, vbo.componentType, vbo.vboType);

		}

		return vbo.enabled;
	}


	void GLTF::PrintData(char *pBinaryBuff, size_t byteOffset, size_t count, vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE vboType)
	{
		Trace::out("\n");
		if(componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT && vboType == vboData::VBO_TYPE::SCALAR) // unsigned short
		{
			unsigned short *p = (unsigned short *)((uint32_t)pBinaryBuff + byteOffset);
			void *pstart = p;
			Trace::out("start: %p \n", p);
			for(size_t j = 0; j < count / 3; j++)
			{
				Trace::out("\t[%d]:  %3d %3d %3d \n", j, p[0], p[1], p[2]);
				p += 3;
			}
			void *pend = p;
			Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
			Trace::out("\n");
		}

		if(componentType == vboData::VBO_COMPONENT::UNSIGNED_INT && vboType == vboData::VBO_TYPE::SCALAR) // unsigned int
		{
			unsigned int *p = (unsigned int *)((uint32_t)pBinaryBuff + byteOffset);
			void *pstart = p;
			Trace::out("start: %p \n", p);
			for(size_t j = 0; j < count / 3; j++)
			{
				Trace::out("\t[%d]:  %3d %3d %3d \n", j, p[0], p[1], p[2]);
				p += 3;
			}
			void *pend = p;
			Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
			Trace::out("\n");
		}

		if(componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC4)
		{
			float *p = (float *)((uint32_t)pBinaryBuff + byteOffset);
			void *pstart = p;
			Trace::out("start: %p \n", p);
			for(size_t j = 0; j < count; j++)
			{
				Trace::out("\t[%d]:  %5.4f %5.4f %5.4f %5.4f\n", j, p[0], p[1], p[2], p[3]);
				p += 4;
			}
			void *pend = p;
			Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
			Trace::out("\n");
		}

		if(componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC3)
		{
			float *p = (float *)((uint32_t)pBinaryBuff + byteOffset);
			void *pstart = p;
			Trace::out("start: %p \n", p);
			for(size_t j = 0; j < count; j++)
			{
				Trace::out("\t[%d]:  %5.4f %5.4f %5.4f \n", j, p[0], p[1], p[2]);
				p += 3;
			}
			void *pend = p;
			Trace::out("end: %p diff: %d\n", p, (size_t)pend - (size_t)pstart);
			Trace::out("\n");
		}

		if(componentType == vboData::VBO_COMPONENT::FLOAT && vboType == vboData::VBO_TYPE::VEC2)
		{
			float *p = (float *)((uint32_t)pBinaryBuff + byteOffset);

			for(size_t j = 0; j < count; j++)
			{
				Trace::out("\t[%d]:  %5.4f %5.4f \n", j, p[0], p[1]);
				p += 2;
			}

			Trace::out("\n");
		}

	}


	bool GLTF::SetVBO_index(Model &gltfModel, unsigned int _AttribIndex, vboData &vbo, char *pBinaryBuff)
	{
		// Get the accessor, buffer view
		vbo.enabled = true;

		auto index = gltfModel.meshes[0].primitives[0].indices;
		//assert(index > 0);

		auto accessor = gltfModel.accessors[(size_t)index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
		vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
		vbo.vboType = vboDataConverter::GetType(accessor.type);

		vbo.attribIndex = _AttribIndex;  // not used in index buffers
		vbo.count = accessor.count;
		vbo.dataSize = bufferView.byteLength;

		// poData
		assert(pBinaryBuff);
		char *pBuffStart(nullptr);

		// Start address
		pBuffStart = pBinaryBuff + bufferView.byteOffset;

		// in case there's data
		delete[] vbo.poData;

		if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT)
		{
			// Convert the unsigned short into unsigned int buffer
			// Engine will now be all unsigned int for index buffer
			unsigned int *pIndexData = new unsigned int[vbo.count]();
			unsigned int *pTmp = pIndexData;
			unsigned short *pShort = (unsigned short *)pBuffStart;

			for(unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = *pShort++;
			}

			// this is the output buffer
			vbo.poData = (unsigned char *)pIndexData;
			// update the data
			vbo.dataSize = vbo.count * sizeof(unsigned int);
			// update the component
			vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
		}
		else if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
		{
			vbo.poData = new unsigned char[vbo.dataSize]();
			assert(vbo.poData);
			memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
		}
		else
		{
			assert(false);
		}

		//GLTF::PrintData((char *)vbo.poData, 0, vbo.count, vbo.componentType, vbo.vboType);

		return true;
	}



	bool GLTF::SetTexture(Model &gltfModel, unsigned int index, textureData &text, char *pBinaryBuff)
	{
		AZUL_UNUSED_VAR(gltfModel);
		AZUL_UNUSED_VAR(index);
		AZUL_UNUSED_VAR(text);
		AZUL_UNUSED_VAR(pBinaryBuff);

		text.enabled = true;

		if(strcmp(gltfModel.images[index].mimeType.c_str(), "image/png") == 0)
		{
			text.textType = textureData::TEXTURE_TYPE::PNG;
		}

		text.magFilter = textureData::TEXTURE_MAG_FILTER::DEFAULT;
		text.minFilter = textureData::TEXTURE_MIN_FILTER::DEFAULT;
		text.wrapS = textureData::TEXTURE_WRAP::DEFAULT;
		text.wrapT = textureData::TEXTURE_WRAP::DEFAULT;
		text.width = (unsigned int)gltfModel.images[index].width;
		text.height = (unsigned int)gltfModel.images[index].height;
		text.component = (unsigned int)gltfModel.images[index].component;
		text.bits = (unsigned int)gltfModel.images[index].bits;
		text.as_is = gltfModel.images[index].as_is;
		text.pixel_type = textureDataConverter::GetComponent(gltfModel.images[index].pixel_type);

		// pFileName
		unsigned int len = gltfModel.images[index].name.length();
		assert(len < text.FILE_NAME_SIZE);
		memcpy_s(text.pFileName,
			text.FILE_NAME_SIZE,
			gltfModel.images[index].name.c_str(),
			len);



		if(gltfModel.images[index].as_is == false)
		{
			// at this point the data is decompressed into a raw buffer gltfModel
			text.dataSize = gltfModel.images[index].image.size();

			Trace::out("byteLength: %d \n", text.dataSize);

			// in case there's data
			delete[] text.poData;

			text.poData = new unsigned char[text.dataSize]();
			assert(text.poData);
			auto pStart = &gltfModel.images[index].image[0];
			memcpy_s(text.poData, text.dataSize, pStart, text.dataSize);
		}
		else
		{
			// export the texture file in compressed mode 
			unsigned int buffViewIndex = (unsigned int)gltfModel.images[index].bufferView;
			auto buffView = gltfModel.bufferViews[buffViewIndex];
			text.dataSize = buffView.byteLength;

			char *pBuffStart = pBinaryBuff + buffView.byteOffset;

			//	Trace::out("byteLength: %d \n", text.dataSize);
			//	Trace::out("byteOffset: %d \n", buffView.byteOffset);

				// in case there's data
			delete[] text.poData;

			text.poData = new unsigned char[text.dataSize]();
			assert(text.poData);
			memcpy_s(text.poData, text.dataSize, pBuffStart, text.dataSize);
		}
		return true;
	}


	bool GLTF::SetVBO_BONE_index(Model &gltfModel,
		unsigned int _AttribIndex,
		vboData &vbo,
		char *pBuffStart,
		unsigned int byteLength,
		unsigned int count)
	{
		// Get the accessor, buffer view
		vbo.enabled = true;

		auto index = gltfModel.meshes[0].primitives[0].indices;
		assert(index > 0);

		auto accessor = gltfModel.accessors[(size_t)index];
		size_t buffIndex = (size_t)accessor.bufferView;
		auto bufferView = gltfModel.bufferViews[buffIndex];

		vbo.targetType = vboDataConverter::GetTarget(bufferView.target);

		// it was converted to unsigned int earlier...
		assert(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT);
		vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;

		vbo.vboType = vboDataConverter::GetType(accessor.type);

		vbo.attribIndex = _AttribIndex;  // not used in index buffers
		vbo.count = count;
		vbo.dataSize = byteLength;

		assert(pBuffStart);

		// in case there's data
		delete[] vbo.poData;

		if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_SHORT)
		{
			// Convert the unsigned short into unsigned int buffer
			// Engine will now be all unsigned int for index buffer
			unsigned int *pIndexData = new unsigned int[vbo.count]();
			unsigned int *pTmp = pIndexData;
			unsigned short *pShort = (unsigned short *)pBuffStart;

			for(unsigned int i = 0; i < vbo.count; i++)
			{
				// convert it
				*pTmp++ = *pShort++;
			}

			// this is the output buffer
			vbo.poData = (unsigned char *)pIndexData;
			// update the data
			vbo.dataSize = vbo.count * sizeof(unsigned int);
			// update the component
			vbo.componentType = vboData::VBO_COMPONENT::UNSIGNED_INT;
		}
		else if(vbo.componentType == vboData::VBO_COMPONENT::UNSIGNED_INT)
		{
			vbo.poData = new unsigned char[vbo.dataSize]();
			assert(vbo.poData);
			memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);
		}
		else
		{
			assert(false);
		}


		return true;
	}

	bool GLTF::SetVBO_BONE(Model &gltfModel,
		unsigned int _AttribIndex,
		const char *pKey,
		vboData &vbo,
		char *pBuffStart,
		unsigned int byteLength,
		unsigned int count)
	{
		// Get the accessor, buffer view
		vbo.enabled = false;

		assert(pKey);
		auto map = gltfModel.meshes[0].primitives[0].attributes;
		auto it = map.find(pKey);

		if(it != map.end())
		{
			// Get the accessor, buffer view
			vbo.enabled = true;

			auto index = it->second;

			auto accessor = gltfModel.accessors[(size_t)index];
			size_t buffIndex = (size_t)accessor.bufferView;
			auto bufferView = gltfModel.bufferViews[buffIndex];

			vbo.targetType = vboDataConverter::GetTarget(bufferView.target);
			vbo.componentType = vboDataConverter::GetComponent(accessor.componentType);
			vbo.vboType = vboDataConverter::GetType(accessor.type);

			vbo.attribIndex = _AttribIndex;
			vbo.count = count;
			vbo.dataSize = byteLength;

			assert(pBuffStart);

			// in case there's data
			delete[] vbo.poData;

			vbo.poData = new unsigned char[vbo.dataSize]();
			assert(vbo.poData);
			memcpy_s(vbo.poData, vbo.dataSize, pBuffStart, vbo.dataSize);

		}

		return vbo.enabled;
	}

	File::Error GLTF::WriteMeshToFile(meshData_proto& mesh, const char* fileName)
	{
		File::Handle handle;
		File::Error err;

		err = File::Open(handle, fileName, File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string out;
		mesh.SerializeToString(&out);

		File::Write(handle, out.data(), out.length());
		assert(err == File::Error::SUCCESS);

		err = File::Close(handle);
		assert(err == File::Error::SUCCESS);

		return err;
	}

}

// --- End of File ---
