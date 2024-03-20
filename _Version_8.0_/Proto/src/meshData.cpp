//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "meshData.h"

namespace Azul
{
	meshData::~meshData()
	{

	}

	meshData::meshData()
		:
		pVersion{0},
		pMeshName{0},
		mode{meshData::RENDER_MODE::DEFAULT},
		triCount{0},
		vertCount{0},
		vbo_vert(),
		vbo_norm(),
		vbo_uv(),
		vbo_color(),
		vbo_index(),
		text_color(),
		vbo_weights(),
		vbo_joints(),
		vbo_invbind()
	{
		strcpy_s(this->pVersion, meshData::VERSION_NUM_BYTES, meshData::PROTO_VERSION);
		// Make sure version is within the bytes for serialization
		assert(strlen(this->pVersion) < meshData::VERSION_NUM_BYTES);
	}

	void meshData::Serialize(meshData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		std::string sVersion((const char *)this->pVersion, meshData::VERSION_NUM_BYTES);
		out.set_pversion(sVersion);

		std::string sName((const char *)this->pMeshName, meshData::FILE_NAME_SIZE);
		out.set_pmeshname(sName);

		out.set_mode((meshData_proto_RENDER_MODE)this->mode);
		out.set_tricount(this->triCount);
		out.set_vertcount(this->vertCount);

		vboData_proto *pVBO_proto;

		pVBO_proto = new vboData_proto();
		this->vbo_vert.Serialize(*pVBO_proto);
		out.set_allocated_vbo_vert(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_norm.Serialize(*pVBO_proto);
		out.set_allocated_vbo_norm(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_uv.Serialize(*pVBO_proto);
		out.set_allocated_vbo_uv(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_color.Serialize(*pVBO_proto);
		out.set_allocated_vbo_color(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_index.Serialize(*pVBO_proto);
		out.set_allocated_vbo_index(pVBO_proto);

		textureData_proto *pText_proto;

		pText_proto = new textureData_proto();
		this->text_color.Serialize(*pText_proto);
		out.set_allocated_text_color(pText_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_weights.Serialize(*pVBO_proto);
		out.set_allocated_vbo_weights(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_joints.Serialize(*pVBO_proto);
		out.set_allocated_vbo_joints(pVBO_proto);

		pVBO_proto = new vboData_proto();
		this->vbo_invbind.Serialize(*pVBO_proto);
		out.set_allocated_vbo_invbind(pVBO_proto);
	}

	void meshData::Deserialize(const meshData_proto &in)
	{
		// CHECK the Version
		memcpy_s(this->pVersion, meshData::VERSION_NUM_BYTES, in.pversion().data(), meshData::VERSION_NUM_BYTES);
		assert(strcmp(this->pVersion, meshData::PROTO_VERSION) == 0);

		// Load the rest
		memcpy_s(this->pMeshName, meshData::FILE_NAME_SIZE, in.pmeshname().data(), meshData::FILE_NAME_SIZE);
		this->mode = (RENDER_MODE)in.mode();
		this->triCount = in.tricount();
		this->vertCount = in.vertcount();

		this->vbo_vert.Deserialize(in.vbo_vert());
		this->vbo_norm.Deserialize(in.vbo_norm());
		this->vbo_uv.Deserialize(in.vbo_uv());
		this->vbo_color.Deserialize(in.vbo_color());
		this->vbo_index.Deserialize(in.vbo_index());

		this->text_color.Deserialize(in.text_color());
		this->vbo_weights.Deserialize(in.vbo_weights());
		this->vbo_joints.Deserialize(in.vbo_joints());
		this->vbo_invbind.Deserialize(in.vbo_invbind());
	}

	void meshData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		//Trace::out("%s: \n", pName);
		//Trace::out("\n");

		//Trace::out("version: %s \n", this->pVersion);
		//Trace::out("\n");
		//this->vbo_vert.Print("vbo_vert");
		//Trace::out("\n");
		//this->vbo_norm.Print("vbo_norm");
		//Trace::out("\n");
		//this->vbo_uv.Print("vbo_uv");
		//Trace::out("\n");
		//this->vbo_color.Print("vbo_color");
		//Trace::out("\n");
		//this->vbo_index.Print("vbo_index");
		//Trace::out("\n");
		//this->text_color.Print("text_color");
		//Trace::out("\n");
	}
}

// --- End of File ---


