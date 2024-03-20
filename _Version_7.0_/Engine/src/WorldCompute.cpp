#include "WorldCompute.h"
#include "File.h"
#include "hierarchyData.h"
#include "ShaderMan.h"
#include "invBindData.h"
#include <cmath>

namespace Azul
{
	WorldCompute::WorldCompute(Mixer* mixer, const char* const hierarchyFileName, const char* const invBindFileName, ShaderObject::Name name)
		: localBone(mixer->frameRes), hierarchy(), worldMat(), invBind(), boneCount(mixer->boneCount), hierarchyDepth(0), shader(nullptr)
	{
		File::Handle handle;
		File::Error err;
		DWORD len;

		const char* pPath = "Data\\";
		size_t size = strlen(pPath) + strlen(hierarchyFileName) + 1;
		char* pFileName = new char[size]();
		memset(pFileName, 0, size);
		strcat_s(pFileName, size, pPath);
		strcat_s(pFileName, size, hierarchyFileName);

		err = File::Open(handle, pFileName, File::Mode::READ);

		err = File::Seek(handle, File::Position::END, 0);

		err = File::Tell(handle, len);

		char* buff = new char[len]();

		err = File::Seek(handle, File::Position::BEGIN, 0);

		err = File::Read(handle, buff, len);

		err = File::Close(handle);

		std::string strIn(buff, len);
		hierarchyData_proto hDataProto;

		hDataProto.ParseFromString(strIn);

		hierarchyData hData;
		hData.Deserialize(hDataProto);

		this->hierarchyDepth = (int)hData.maxDepth;
		this->hierarchy.Set((hData.maxDepth * hData.count), sizeof(int), hData.data);

		Mat4* worldArr = new Mat4[(unsigned int)this->boneCount]();

		this->worldMat.Set((unsigned int)this->boneCount, sizeof(Mat4), worldArr);

		size = strlen(pPath) + strlen(invBindFileName) + 1;
		char* pFileNameB = new char[size]();
		memset(pFileNameB, 0, size);
		strcat_s(pFileNameB, size, pPath);
		strcat_s(pFileNameB, size, invBindFileName);

		err = File::Open(handle, pFileNameB, File::Mode::READ);

		err = File::Seek(handle, File::Position::END, 0);

		err = File::Tell(handle, len);

		char* buffB = new char[len]();

		err = File::Seek(handle, File::Position::BEGIN, 0);

		err = File::Read(handle, buffB, len);

		err = File::Close(handle);

		std::string strInB(buffB, len);
		invBindData_proto ibDataProto;

		ibDataProto.ParseFromString(strInB);

		invBindData ibData;
		ibData.Deserialize(ibDataProto);

		this->invBind.Set(ibData.count, sizeof(Mat4), ibData.data);

		delete[] buff;
		delete[] buffB;
		delete[] worldArr;
		delete[] pFileName;
		delete[] pFileNameB;

		this->shader = ShaderMan::Find(name);
	}

	void WorldCompute::Update()
	{
		this->shader->SetActive();

		this->localBone.Bind(0);
		this->hierarchy.Bind(1);
		this->worldMat.Bind(2);
		this->invBind.Bind(3);

		glUniform1i(this->shader->GetLocation("hierarchyDepth"), this->hierarchyDepth);
		glUniform1i(this->shader->GetLocation("boneCount"), this->boneCount);

		unsigned int count = (unsigned int)ceil((float)this->boneCount / 10.0f);

		this->shader->Dispatch(count, 1, 1);

		glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
	}
}