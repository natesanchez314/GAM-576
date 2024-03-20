#ifndef IMAGE_DATA_H
#define IMAGE_DATA_H

#include "imageData.pb.h"

namespace Azul
{
	class imageData
	{
	public:
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;

		imageData();
		imageData(const imageData&) = delete;
		imageData& operator=(const imageData&) = delete;
		~imageData();

		void Serialize(imageData_proto& out) const;
		void Deserialize(const imageData_proto& in);
	};
}

#endif // !IMAGE_DATA_H
