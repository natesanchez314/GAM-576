#ifndef CLIP_DATA_H
#define CLIP_DATA_H

#include "clipData.pb.h"
#include "frameData.h"

class clipData
{
public:
	unsigned int count;
	frameData* frames;

	clipData();
	clipData(const clipData&) = delete;
	clipData& operator=(const clipData&) = delete;
	~clipData();

	void Serialize(clipData_proto& out) const;
	void Deserialize(const clipData_proto& in);
};

#endif // !CLIP_DATA_H
