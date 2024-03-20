#include "GraphicsObject_SkinTexture.h"
#include "CameraMan.h"
#include "TextureMan.h"
#include "Mesh.h"
#include "Anim.h"

namespace Azul
{
	GraphicsObject_SkinTexture::GraphicsObject_SkinTexture(const Mesh* const mesh, const ShaderObject* const shaderObj, Texture::Name tName, Vec4& lightColor, Vec3& lightPos)
		: GraphicsObject(mesh, shaderObj), boneWorld(nullptr), tName(tName), boneCount(0), lightColor(lightColor), lightPos(lightPos)
	{ }
	/*
	GraphicsObject_SkinTexture::~GraphicsObject_SkinTexture()
	{ 
		//delete this->worldCompute;
		delete this->lightColor;
		delete this->lightPos;
	}
	*/
	void GraphicsObject_SkinTexture::SetState()
	{ 
		glActiveTexture(GL_TEXTURE0);
		GLuint textID = TextureMan::FindID(this->tName);
		glBindTexture(GL_TEXTURE_2D, textID);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

	void GraphicsObject_SkinTexture::SetDataGPU()
	{ 
		this->pShaderObj->SetActive();
		glBindVertexArray(this->GetMesh()->vao);
		Camera* cam = CameraMan::GetCurrent3D();
		Mat4 view = cam->getViewMatrix();
		Mat4 proj = cam->getProjMatrix();

		this->worldCompute->worldMat.Bind(0);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("pivotWorld"), 1, GL_FALSE, (float*)this->poWorld);

		glUniformMatrix4fv(this->pShaderObj->GetLocation("proj_matrix"), 1, GL_FALSE, (float*)&proj);
		glUniformMatrix4fv(this->pShaderObj->GetLocation("view_matrix"), 1, GL_FALSE, (float*)&view);

		Vec3 light = this->lightPos;
		Vec4 color = this->lightColor;
		glUniform3fv(this->pShaderObj->GetLocation("vLightPos"), 1, (float*)&light);
		glUniform4fv(this->pShaderObj->GetLocation("vColor"), 1, (float*)&color);
	}

	void GraphicsObject_SkinTexture::Draw()
	{ 
		glDrawElements(GL_TRIANGLES, 3 * this->GetMesh()->numTris, GL_UNSIGNED_INT, 0);
	}

	void GraphicsObject_SkinTexture::RestoreState()
	{ 
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
	}

	void GraphicsObject_SkinTexture::SetBoneWorld(Mat4* _boneWorld)
	{ 
		this->boneWorld = _boneWorld;
	}
}