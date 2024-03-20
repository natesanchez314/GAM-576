//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#version 430 core

// #includes doesn't work GLSL 
// Insert at compile time "ShaderLayout.h" manually
#include "ShaderLayout.h"

layout (location = ATTRIB_LOCATION_VERT) in vec4 vert;    
layout (location = ATTRIB_LOCATION_NORM) in vec3 norms;
layout (location = ATTRIB_LOCATION_TEXT) in vec2 uv;

layout (location = ATTRIB_LOCATION_WEIGHT) in vec4  weight;
layout (location = ATTRIB_LOCATION_JOINT) in ivec4 joint;

// Uniforms

layout (std430, binding = 0) buffer boneWorld_label
{
	mat4 boneWorld[];
};

	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform mat4 pivotWorld;
	uniform vec3 vLightPos;
	uniform vec4 vColor;

// Varying
	out VS_OUT
	{
		vec2 textCoordinate;
		vec4 vFragColor;
	} vs_out;


void main(void)
{
// Get vNorm
		//mat4 mvMatrix = view_matrix * world_matrix;
		//mat3 mNormalMatrix;
		//mNormalMatrix[0] = normalize(mvMatrix[0].xyz);
		//mNormalMatrix[1] = normalize(mvMatrix[1].xyz);
		//mNormalMatrix[2] = normalize(mvMatrix[2].xyz);
		//vec3 vNorm = normalize(mNormalMatrix * norms);

	// Get vLightDir
		

    vs_out.textCoordinate = uv;

	// Remember: We use ROW major, but OpenGL GLSL multiplies in reverse order!

	 mat4 skin_matrix = weight.x * boneWorld[joint.x]   +
					    weight.y * boneWorld[joint.y]   +
					    weight.z * boneWorld[joint.z]   +
					    weight.w * boneWorld[joint.w]  ;

						
		mat3 mNormalMatrix;
		mNormalMatrix[0] = normalize(skin_matrix[0].xyz);
		mNormalMatrix[1] = normalize(skin_matrix[1].xyz);
		mNormalMatrix[2] = normalize(skin_matrix[2].xyz);
		vec3 vNorm = normalize(mNormalMatrix * norms);

		vec4 ecPosition;
		vec3 ecPosition3;
		ecPosition = skin_matrix * vert;
		ecPosition3 = ecPosition.xyz /ecPosition.w;
		vec3 vLightDir = normalize(vLightPos - ecPosition3);

	// Get vFragColor
		float fDot = max(0.0, dot(vNorm, vLightDir)); 
		vs_out.vFragColor.rgb = vColor.rgb * fDot;
		vs_out.vFragColor.a = vColor.a;
	
    gl_Position = proj_matrix * view_matrix * pivotWorld * skin_matrix * vert;    
}

// --- End of File ---
