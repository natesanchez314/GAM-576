#include "frameData.h"

frameData::frameData()
	:frameIndex(0), time(0.0f), count(0), bones(nullptr)
{ }

frameData::~frameData()
{
	delete[] bones;
}

void frameData::Serialize(frameData_proto& out) const
{
	out.set_frame_index(this->frameIndex);
	out.set_time(this->time);
	out.set_count(this->count);
	for (unsigned int i = 0; i < this->count; i++)
	{
		boneData_proto* bone = out.add_bones();
		this->bones[i].Serialize(*bone);
	}
}

void frameData::Deserialize(const frameData_proto& in)
{
	this->frameIndex = in.frame_index();
	this->time = in.time();
	this->count = in.count();
	this->bones = new boneData[this->count]();
	for (unsigned int i = 0; i < this->count; i++)
		this->bones[i].Deserialize(in.bones()[i]);
}