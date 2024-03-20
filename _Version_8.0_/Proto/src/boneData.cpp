#include "boneData.h"

boneData::boneData()
	:t(), q(), s()
{ }

boneData::~boneData()
{ }

void boneData::Serialize(boneData_proto& out) const
{
	this->t.Serialize(*out.mutable_t());
	this->q.Serialize(*out.mutable_q());
	this->s.Serialize(*out.mutable_s());
}

void boneData::Deserialize(const boneData_proto& in)
{
	this->t.Deserialize(in.t());
	this->q.Deserialize(in.q());
	this->s.Deserialize(in.s());
}