#include "InvBind.h"
#include "GLTF.h"
#include "File.h"
#include "meshDataConverter.h"
#include "invBindData.h"

using namespace tinygltf;

namespace Azul
{
	void CreateInvBind(const char* const inName, const char* const outName)
	{
		const char* inFileExt = ".glb";
		const char* outFileExt = ".inv.proto.azul";

		size_t inFileNameSize = strlen(inName) + strlen(inFileExt) + 1;
		size_t outFileNameSize = strlen(outName) + strlen(outFileExt) + 1;

		char* inFileName = new char[inFileNameSize]();
		strcat_s(inFileName, inFileNameSize, inName);
		strcat_s(inFileName, inFileNameSize, inFileExt);

		char* outFileName = new char[outFileNameSize]();
		strcat_s(outFileName, outFileNameSize, outName);
		strcat_s(outFileName, outFileNameSize, outFileExt);

		bool status;
		tinygltf::Model gltfModel;

		meshData runtimeModel;
		char* buff = nullptr;
		unsigned int buffSize(0);
		GLB_header header;
		char* json = nullptr;
		unsigned int jsonSize(0);
		char* binBuff = nullptr;
		unsigned int binBuffSize = 0;

		status = GLTF::LoadBinary(gltfModel, inFileName);

		status = GLTF::GetGLBRawBuffer(buff, buffSize, inFileName);

		status = GLTF::GetGLBHeader(header, buff, buffSize);
		
		status = GLTF::GetRawJSON(json, jsonSize, buff, buffSize);

		status = GLTF::GetBinaryBuffPtr(binBuff, binBuffSize, buff, buffSize);

		SkinMesh skinMesh;

		size_t invMatAccessorIndex = (size_t)gltfModel.skins[0].inverseBindMatrices;
		
		unsigned char* buffData = (unsigned char*)&gltfModel.buffers[0].data[0];

		auto inverseAccesor = gltfModel.accessors[invMatAccessorIndex];
		auto inverseBuffView = gltfModel.bufferViews[(size_t)inverseAccesor.bufferView];

		unsigned char* inverseMatBuff = buffData + inverseBuffView.byteOffset;

		Mat4* mat = (Mat4*)inverseMatBuff;
		for (size_t i = 0; i < inverseAccesor.count; i++)
			skinMesh.invBone.push_back(mat[i]);

		
		invBindData bind(inverseAccesor.count);
		
		Mat4* matOut = (Mat4*)&bind.data[0];
		for (size_t i = 0; i < inverseAccesor.count; i++)
			matOut[i] = mat[i];

		invBindData_proto bindProto;
		bind.Serialize(bindProto);

		File::Handle handle;
		File::Error err;

		err = File::Open(handle, outFileName, File::Mode::WRITE);

		std::string strOut;
		bindProto.SerializeToString(&strOut);

		err = File::Write(handle, strOut.data(), strOut.length());
		err = File::Close(handle);

		delete[] inFileName;
		delete[] outFileName;
		delete[] json;
		delete[] buff;
	}
}