#include "CreateTexture.h"
#include "GLTF.h"
#include "StringThis.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"
#include "ShaderLayout.h"
#include "MathEngine.h"

namespace Azul
{
	void CreateModel(const char* const fileName)
	{
		const char* inFileExt = ".glb";
		const char* outFileExt = ".m.proto.azul";

		size_t inFileNameSize = strlen(fileName) + strlen(inFileExt) + 1;
		size_t outFileNameSize = strlen(fileName) + strlen(outFileExt) + 1;

		char* inFileName = new char[inFileNameSize]();
		strcat_s(inFileName, inFileNameSize, fileName);
		strcat_s(inFileName, inFileNameSize, inFileExt);

		char* outFileName = new char[outFileNameSize]();
		strcat_s(outFileName, outFileNameSize, fileName);
		strcat_s(outFileName, outFileNameSize, outFileExt);

		tinygltf::Model gltfModel;
		meshData runTimeModel;

		bool status;
		status = GLTF::LoadBinary(gltfModel, inFileName);
		assert(status);

		char* buffer = nullptr;
		unsigned int buffSize(0);
		status = GLTF::GetGLBRawBuffer(buffer, buffSize, inFileName);
		assert(status);
		assert(buffer);
		assert(buffSize > 0);

		GLB_header header;
		status = GLTF::GetGLBHeader(header, buffer, buffSize);
		assert(status);

		char* json = nullptr;
		unsigned int jsonSize(0);
		status = GLTF::GetRawJSON(json, jsonSize, buffer, buffSize);
		assert(status);

		char* binBuffer = nullptr;
		unsigned int binBuffsize = 0;
		status = GLTF::GetBinaryBuffPtr(binBuffer, binBuffsize, buffer, buffSize);
		assert(status);

		memcpy_s(runTimeModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.meshes[0].name.c_str(), gltfModel.meshes[0].name.length());

		status = GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_VERT, "POSITION", runTimeModel.vbo_vert, binBuffer);
		assert(status);
		status = GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_NORM, "NORMAL", runTimeModel.vbo_norm, binBuffer);
		assert(status);
		status = GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_TEXT, "TEXCOORD_0", runTimeModel.vbo_uv, binBuffer);
		assert(status);
		status = GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_COLOR, "COLOR_0", runTimeModel.vbo_color, binBuffer);
		//assert(status);
		status = GLTF::SetVBO_index(gltfModel, ATTRIB_LOCATION_INDEX, runTimeModel.vbo_index, binBuffer);
		assert(status);
		//--------------------------------
		// PolyCount
		//--------------------------------
		runTimeModel.triCount = runTimeModel.vbo_index.count / 3;
		runTimeModel.vertCount = runTimeModel.vbo_vert.count;
		runTimeModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);

		meshData_proto runTimeModelProto;
		runTimeModel.Serialize(runTimeModelProto);

		File::Error err = GLTF::WriteMeshToFile(runTimeModelProto, outFileName);
		assert(err == File::Error::SUCCESS);

		delete[] buffer;
		delete[] json;
		delete[] inFileName;
		delete[] outFileName;
	}
}