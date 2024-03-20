#include "quatData.h"

quatData::quatData()
	:v(), real(1.0f)
{ }

quatData::~quatData()
{ }

void quatData::Serialize(quatData_proto& out) const
{
	this->v.Serialize(*out.mutable_v());
	out.set_real(this->real);
}

void quatData::Deserialize(const quatData_proto& in)
{
	this->v.Deserialize(in.v());
	this->real = in.real();
}