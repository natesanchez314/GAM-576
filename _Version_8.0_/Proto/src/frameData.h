#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "frameData.pb.h"
#include "boneData.h"

class frameData
{
public:
	int frameIndex;
	float time;
	unsigned int count;
	boneData* bones;

	frameData();
	frameData(const frameData&) = delete;
	frameData& operator=(const frameData&) = delete;
	~frameData();

	void Serialize(frameData_proto& out) const;
	void Deserialize(const frameData_proto& in);
};

#endif // !FRAME_DATA_H
