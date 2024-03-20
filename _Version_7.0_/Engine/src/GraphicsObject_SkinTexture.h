#ifndef GRAPHICS_OBJECT_SKIN_TEXTURE_H
#define GRAPHICS_OBJECT_SKIN_TEXTURE_H

#include "GraphicsObject.h"
#include "TextureMan.h"
#include "WorldCompute.h"

namespace Azul
{
	class GraphicsObject_SkinTexture : public GraphicsObject
	{
	public:
		Mat4* boneWorld;
		Texture::Name tName;
		int boneCount;
		WorldCompute* worldCompute;
		Vec4& lightColor;
		Vec3& lightPos;

		GraphicsObject_SkinTexture() = delete;
		GraphicsObject_SkinTexture(const Mesh* const mesh, const ShaderObject* const shaderObj, Texture::Name tName, Vec4& lightColor, Vec3& lightPos);
		GraphicsObject_SkinTexture(const GraphicsObject_SkinTexture&) = delete;
		GraphicsObject_SkinTexture& operator=(const GraphicsObject_SkinTexture&) = delete;
		virtual ~GraphicsObject_SkinTexture() = default;

		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		void SetBoneWorld(Mat4* boneWorld);
	};
}

#endif // !GRAPHICS_OBJECT_SKIN_TEXTURE_H
