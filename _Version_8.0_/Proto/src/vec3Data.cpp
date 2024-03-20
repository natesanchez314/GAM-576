#include "vec3Data.h"

vec3Data::vec3Data()
	:x(0.0f), y(0.0f), z(0.0f)
{ }

vec3Data::~vec3Data()
{ }

void vec3Data::Serialize(vec3Data_proto& out) const
{ 
	out.set_x(this->x);
	out.set_y(this->y);
	out.set_z(this->z);
}

void vec3Data::Deserialize(const vec3Data_proto& in)
{ 
	this->x = in.x();
	this->y = in.y();
	this->z = in.z();
}