#ifndef VEC3_DATA_H
#define VEC3_DATA_H

#include "vec3Data.pb.h"

class vec3Data
{
public:
	float x;
	float y;
	float z;

	vec3Data();
	vec3Data(const vec3Data&) = delete;
	vec3Data& operator=(const vec3Data&) = delete;
	~vec3Data();

	void Serialize(vec3Data_proto& out) const;
	void Deserialize(const vec3Data_proto& in);
};

#endif // !VEC3_DATA_H
