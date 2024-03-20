//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SHADER_OBJECT_H
#define SHADER_OBJECT_H

#include "sb7.h"
#include "DLink.h"

namespace Azul
{
	class ShaderObject : public DLink
	{
	public:
		enum class Name
		{
			NULL_SHADER,
			COLOR_POSITION,
			COLOR_SINGLE,
			TEXTURE_SIMPLE,
			SPRITE,
			TEXTURE_POINT_LIGHT,
			CONST_COLOR,
			SKIN,
			COMPUTE_TEST,
			MIXER,
			WORLD,
			UNINITIALIZED
		};

		enum class Type
		{
			GRAPHICS,
			COMPUTE,
			UNINITIALIZED
		};

	public:
		ShaderObject();
		ShaderObject(const ShaderObject &) = delete;
		ShaderObject &operator = (ShaderObject &) = delete;
		virtual ~ShaderObject();


		void Set(ShaderObject::Name name, const char *const pName, ShaderObject::Type type);
		void SetActive() const;
		GLint GetLocation(const char *const pUniformName) const;

		virtual void Wash() override;
		virtual char *GetName() override;
		virtual bool Compare(DLink *pTargetNode) override;
		virtual void Dump() override;

		void Dispatch(unsigned int x, unsigned int y, unsigned int z);

	private:
		void privClear();
		bool privCreateShader(GLuint &programObject, const char *const pShaderBaseFileName);
		bool privLoadNCompile(GLuint &shaderObject, const char *const pShaderFileName, GLenum shader_type);
		void privLoadFile(const char *const pFileName, char *&pBuff, int &BuffSize);
		void privRemoveVersionLine(char *pBuff, const char *pTok);


	public:
		Name  name;
		Type type;
		GLuint		programObject;
		GLuint fs;
		GLuint vs;
		GLuint cs;

	};

}

#endif

// --- End of File ---
