#ifndef WORLD_COMPUTE_H
#define WORLD_COMPUTE_H

#include "Mixer.h"
#include "SSBO.h"
#include "ShaderObject.h"

namespace Azul
{
	class WorldCompute
	{
	public:
		SSBO localBone;
		SSBO hierarchy;
		SSBO worldMat;
		SSBO invBind;
		int boneCount;
		int hierarchyDepth;
		ShaderObject* shader;

		WorldCompute() = delete;
		WorldCompute(Mixer* mixer, const char* const hierarchyFileName, const char* const invBindFileName, ShaderObject::Name name);
		WorldCompute(const WorldCompute&) = delete;
		WorldCompute& operator=(const WorldCompute&) = delete;
		~WorldCompute() = default;

		void Update();
	};
}

#endif // !WORLD_COMPUTE_H
