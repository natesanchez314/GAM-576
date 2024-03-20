#include "Hierarchy.h"
#include "File.h"
#include "GLTF.h"
#include "meshData.h"
#include "Skeleton.h"

using namespace tinygltf;

namespace Azul
{
	void CreateHierarchy(const char* const inName, const char* const outName)
	{
		const char* inFileExt = ".glb";
		const char* outFileExt = ".hierarchy.proto.azul";

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

		status = GLTF::LoadBinary(gltfModel, inFileName);

		SKEL skel;
		hierarchyData* hData;
		hierarchyData_proto hDataProto;

		hData = skel.Hierarchy(gltfModel);

		hData->Serialize(hDataProto);

		File::Handle handle;
		File::Error err;

		err = File::Open(handle, outFileName, File::Mode::WRITE);

		std::string strOut;
		hDataProto.SerializeToString(&strOut);

		err = File::Write(handle, strOut.data(), strOut.length());
		err = File::Close(handle);

		delete[] inFileName;
		delete[] outFileName;
		delete hData;

	}
}