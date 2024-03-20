#include "CreateSkel.h"
#include "Skeleton.h"
#include "skelData.h"
#include "skelData.pb.h"
#include "GLTF.h"
#include "File.h"

namespace Azul
{
	void CreateSkeleton(const char* const inName, const char* const outName)
	{
		const char* inFileExt = ".glb";
		const char* outFileExt = ".skel.proto.azul";

		size_t inFileNameSize = strlen(inName) + strlen(inFileExt) + 1;
		size_t outFileNameSize = strlen(outName) + strlen(outFileExt) + 1;

		char* inFileName = new char[inFileNameSize]();
		strcat_s(inFileName, inFileNameSize, inName);
		strcat_s(inFileName, inFileNameSize, inFileExt);

		char* outFileName = new char[outFileNameSize]();
		strcat_s(outFileName, outFileNameSize, outName);
		strcat_s(outFileName, outFileNameSize, outFileExt);

		bool status;
		tinygltf::Model model;

		//meshData mesh;

		GLTF::LoadBinary(model, inFileName);

		skelData* sData = nullptr;
		skelData_proto sDataProto;

		SKEL skel;
		sData = skel.CreateVector(model);// , outName);

		for (int i = 0; i < sData->boneCount; i++)
		{
			sData->bones[i].Print();
		}

		sData->Serialize(sDataProto);

		File::Handle handle;
		File::Error err;

		err = File::Open(handle, outFileName, File::Mode::WRITE);

		std::string strOut;
		sDataProto.SerializeToString(&strOut);

		err = File::Write(handle, strOut.data(), strOut.length());
		err = File::Close(handle);

		delete[] inFileName;
		delete[] outFileName;
		delete sData;
	}

	void CreateSkeletonChickenBot(const char* const inName, const char* const outName)
	{
		const char* inFileExt = ".glb";
		const char* outFileExt = ".skel.proto.azul";

		size_t inFileNameSize = strlen(inName) + strlen(inFileExt) + 1;
		size_t outFileNameSize = strlen(outName) + strlen(outFileExt) + 1;

		char* inFileName = new char[inFileNameSize]();
		strcat_s(inFileName, inFileNameSize, inName);
		strcat_s(inFileName, inFileNameSize, inFileExt);

		char* outFileName = new char[outFileNameSize]();
		strcat_s(outFileName, outFileNameSize, outName);
		strcat_s(outFileName, outFileNameSize, outFileExt);

		bool status;
		tinygltf::Model model;

		//meshData mesh;

		GLTF::LoadBinary(model, inFileName);

		skelData* sData = nullptr;
		skelData_proto sDataProto;

		SKEL skel;
		sData = skel.CreateVectorChickenBot(model);// , outName);

		for (int i = 0; i < sData->boneCount; i++)
		{
			sData->bones[i].Print();
		}

		sData->Serialize(sDataProto);

		File::Handle handle;
		File::Error err;

		err = File::Open(handle, outFileName, File::Mode::WRITE);

		std::string strOut;
		sDataProto.SerializeToString(&strOut);

		err = File::Write(handle, strOut.data(), strOut.length());
		err = File::Close(handle);

		delete[] inFileName;
		delete[] outFileName;
		delete sData;
	}
}