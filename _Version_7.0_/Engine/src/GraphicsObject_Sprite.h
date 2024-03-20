//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_SPRITE_H
#define GRAPHICS_OBJECT_SPRITE_H

#include "Texture.h"
#include "Image.h"
#include "GraphicsObject.h"
#include "ShaderObject.h"

namespace Azul
{
	class GraphicsObject_Sprite : public GraphicsObject
	{
	public:
		GraphicsObject_Sprite(Mesh *pMesh, ShaderObject *pShaderObj, Image *image, Rect rect);
		virtual ~GraphicsObject_Sprite();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

		void UpdateImage(const Rect& rect);

		//GLuint textureID;
		Image *pImage;
		Mat4 *poMatrix_uv;
		Mat4 *poMatrix_orig;

		float origWidth;
		float origHeight;

		float origPosX;
		float origPosY;
	};
}

#endif

//--- End of File ---

