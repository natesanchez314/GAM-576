#ifndef QUAT_DATA_H
#define QUAT_DATA_H

#include "vec3Data.h"
#include "quatData.pb.h"

class quatData
{
public:
	vec3Data v;
	float real;

	quatData();
	quatData(const quatData&) = delete;
	quatData& operator=(const quatData&) = delete;
	~quatData();

	void Serialize(quatData_proto& out) const;
	void Deserialize(const quatData_proto& in);
};

#endif // !QUAT_DATA_H
