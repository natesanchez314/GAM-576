#include "imageData.h"

namespace Azul
{
	imageData::imageData()
		:x{0}, y{0}, width{0}, height{0}
	{ }

	imageData::~imageData()
	{ }

	void imageData::Serialize(imageData_proto& out) const
	{
		out.set_x(this->x);
		out.set_y(this->y);
		out.set_width(this->width);
		out.set_height(this->height);
	}

	void imageData::Deserialize(const imageData_proto& in)
	{
		this->x = in.x();
		this->y = in.y();
		this->width = in.width();
		this->height = in.height();
	}
}