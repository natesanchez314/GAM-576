//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GAME_OBJECT_ANIM_SKIN_H
#define GAME_OBJECT_ANIM_SKIN_H

#include "GameObjectAnim.h"
#include "MathEngine.h"
#include "ShaderObject.h"
#include "Mesh.h"
#include "GraphicsObject.h"
#include "PCSNode.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"
#include "WorldCompute.h"

namespace Azul
{
	class GameObjectAnimSkin : public GameObjectAnim
	{
	public:
		GameObjectAnimSkin(GraphicsObject* graphicsObject);

		// Big four
		GameObjectAnimSkin() = delete;
		GameObjectAnimSkin(const GameObjectAnimSkin &) = delete;
		GameObjectAnimSkin &operator=(GameObjectAnimSkin &) = delete;
		virtual ~GameObjectAnimSkin();

		void SetScale(float sx, float sy, float sz);
		void SetQuat(float qx, float qy, float qz, float qw);
		void SetTrans(float x, float y, float z);
		
		void SetScale(Vec3& r);
		void SetQuat(Quat& r);
		void SetTrans(Vec3& r);

		void SetWorldCompute(WorldCompute* wc);
		void SetMixer(Mixer* mixer);

		virtual void Update(AnimTime currTime);

		virtual void SetIndex(int i) override;

	private:
		void UpdateWorld(AnimTime currTime);
		void Compute();

	public:   
		Mat4* boneWorld;
		WorldCompute* worldCompute;
		ShaderObject* shaderWorld;
		ShaderObject* shaderMixer;
		Mixer* mixer;

		Vec3* poScale;
		Quat* poQuat;
		Vec3* poTrans;

		float delta_x;
		float delta_y;
		float delta_z;

		float cur_rot_x;
		float cur_rot_y;
		float cur_rot_z;
	};
}

#endif

// --- End of File ---
