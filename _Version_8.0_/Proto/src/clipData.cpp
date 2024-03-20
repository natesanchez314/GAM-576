#include "clipData.h"

clipData::clipData()
	:count(0), frames(nullptr)
{ }

clipData::~clipData()
{
	delete[] frames;
}

void clipData::Serialize(clipData_proto& out) const
{
	out.set_count(this->count);
	for (unsigned int i = 0; i < this->count; i++)
	{
		frameData_proto* frame = out.add_frames();
		this->frames[i].Serialize(*frame);
	}
}

void clipData::Deserialize(const clipData_proto& in)
{
	this->count = in.count();
	this->frames = new frameData[count]();
	for (unsigned int i = 0; i < this->count; i++)
		this->frames[i].Deserialize(in.frames()[i]);
}