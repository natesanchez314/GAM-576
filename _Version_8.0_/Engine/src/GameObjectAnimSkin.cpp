//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectAnimSkin.h"
#include "GraphicsObject.h"
#include "Mesh.h"
#include "Anim.h"
#include "ShaderMan.h"

namespace Azul
{
	GameObjectAnimSkin::GameObjectAnimSkin(GraphicsObject* pGraphicsObject)
		: GameObjectAnim(pGraphicsObject), worldCompute(nullptr)
	{
		this->poTrans = new Vec3(0.0f, 0.0f, 0.0f);
		this->poScale = new Vec3(1.0f, 1.0f, 1.0f);
		this->poQuat = new Quat(0.0f, 0.0f, 0.0f, 1.0f);

		this->delta_x = 0.0f;
		this->delta_y = 0.0f;
		this->delta_z = 0.0f;

		this->cur_rot_x = 0.0f;
		this->cur_rot_y = 0.0f;
		this->cur_rot_z = 0.0f;

		this->shaderWorld = ShaderMan::Find(ShaderObject::Name::WORLD);
		this->shaderMixer = ShaderMan::Find(ShaderObject::Name::MIXER);
	}

	GameObjectAnimSkin::~GameObjectAnimSkin()
	{
		delete this->poTrans;
		delete this->poQuat;
		delete this->poScale;
		delete this->worldCompute;
	}

	void GameObjectAnimSkin::Update(AnimTime currentTime)
	{
		// Goal: update the world matrix
		AZUL_UNUSED_VAR(currentTime);
		//this->privUpdateBoneWorld();
		this->UpdateWorld(currentTime);
		this->poGraphicsObject->SetWorld(*this->poWorld);
		this->Compute();
	}

	void GameObjectAnimSkin::UpdateWorld(AnimTime currTime)
	{
		AZUL_UNUSED_VAR(currTime);

		Quat Qy(Quat::Rot1::Y, MATH_PI2);
		Quat Qx(Quat::Rot1::X, MATH_PI2);
		Quat Qy2(Quat::Rot1::Y, MATH_PI);

		Quat Q = Qy2 * Qx * Qy;

		Mat4 T(Mat4::Trans::XYZ, *this->poTrans);
		Mat4 S(Mat4::Scale::XYZ, *this->poScale);

		cur_rot_x += delta_x;
		cur_rot_y += delta_y;
		cur_rot_z += delta_z;

		Mat4 Rx(Mat4::Rot1::X, cur_rot_x);
		Mat4 Ry(Mat4::Rot1::Y, cur_rot_y);
		Mat4 Rz(Mat4::Rot1::Z, cur_rot_z);

		// world matrix
		*this->poWorld = S * Rx * Ry * Rz * Q * T;

	}

	void GameObjectAnimSkin::Compute()
	{
		//this->mixer->Update();
		this->worldCompute->Update();
	}

	void GameObjectAnimSkin::SetIndex(int i)
	{
		this->index = i;
	}

	void GameObjectAnimSkin::SetWorldCompute(WorldCompute* wc)
	{
		this->worldCompute = wc;
	}
	/*
	void GameObjectAnimSkin::SetMixer(Mixer* _mixer)
	{
		this->mixer = _mixer;
	}*/

	void GameObjectAnimSkin::SetScale(float sx, float sy, float sz)
	{
		this->poScale->set(sx, sy, sz);
	}

	void GameObjectAnimSkin::SetQuat(float qx, float qy, float qz, float qw)
	{
		this->poQuat->set(qx, qy, qz, qw);
	}

	void GameObjectAnimSkin::SetTrans(float x, float y, float z)
	{
		this->poTrans->set(x, y, z);
	}

	void GameObjectAnimSkin::SetScale(Vec3& r)
	{
		this->poScale->set(r);
	}

	void GameObjectAnimSkin::SetQuat(Quat& r)
	{
		this->poQuat->set(r);
	}

	void GameObjectAnimSkin::SetTrans(Vec3& r)
	{
		this->poTrans->set(r);
	}
}

// --- End of File ---
