//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MESH_H
#define MESH_H

#include "sb7.h"
#include "MathEngine.h"
#include "DLink.h"
#include "BoundingSphere.h"

namespace Azul
{
	struct Vert_xyzuv
	{
		float x;
		float y;
		float z;
		float u;
		float v;
	};

	struct Vert_xyz
	{
		float x;
		float y;
		float z;
	};

	struct Vert_nxnynz
	{
		float nx;
		float ny;
		float nz;
	};

	struct Vert_uv
	{
		float u;
		float v;
	};

	struct Vert_color
	{
		float r;
		float g;
		float b;
		float a;
	};

	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	struct Vert_weight
	{
		float wa;
		float wb;
		float wc;
		float wd;
	};

	struct Vert_joint
	{
		float ja;
		float jb;
		float jc;
		float jd;
	};

	class Mesh
	{
	public:
		enum class Name
		{
			CUBE,
			PYRAMID,
			CRATE,
			BONE_2,
			SPHERE,
			CAMERA,
			SPRITE,
			SPACE_FRIGATE,
			R2D2,
			Bone,
			Bone_001,
			Bone_L,
			Bone_L_001,
			Bone_L_002,
			Bone_R,
			Bone_R_001,
			Bone_R_002,
			CHICKEN_BOT,
			MOUSEY,
			NULL_MESH,
			NOT_INITIALIZED
		};

		static const int POLY_WINDING = GL_CCW;

	public:
		Mesh();
		Mesh(Mesh &copyMesh) = delete;
		Mesh &operator = (Mesh &copyMesh) = delete;
		virtual ~Mesh();

		// Data
		int numVerts;
		int numTris;

		GLuint vao;
		GLuint vbo_verts;  // x,y,z
		GLuint vbo_norms;  // nx,ny,nz
		GLuint vbo_texts;  // u,v
		GLuint vbo_color;  // r,g,b,a
		GLuint vbo_index;  // trilist
		GLuint vbo_weight;
		GLuint vbo_joint;
		Mat4* inverseBind;
		unsigned int inverseBindCount;

		void Wash();
		bool Compare(DLink *pTarget);
		char *GetName();
		void SetName(Mesh::Name _name);

		// Reference sphere... before any transformations are applied
		Sphere *poRefSphere;

	protected:



	public:
		Name name;

	};

}
#endif

// --- End of File ---
