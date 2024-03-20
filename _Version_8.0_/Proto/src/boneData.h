#ifndef BONE_DATA_H
#define BONE_DATA_H

#include "boneData.pb.h"
#include "vec3Data.h"
#include "quatData.h"

class boneData
{
public:
	vec3Data t;
	quatData q;
	vec3Data s;

	boneData();
	boneData(const boneData&) = delete;
	boneData& operator=(const boneData&) = delete;
	~boneData();

	void Serialize(boneData_proto& out) const;
	void Deserialize(const boneData_proto& in);
};

#endif // !BONE_DATA_H
