#include "glyphData.h"

namespace Azul
{
	glyphData::glyphData()
		:key{ 0 }, x{ 0 }, y{ 0 }, width{ 0 }, height{ 0 }
	{ }

	glyphData::glyphData(unsigned int key, float x, float y, float width, float height)
		:key(key), x(x), y(y), width(width), height(height)
	{ }

	glyphData::~glyphData()
	{ }

	void glyphData::Serialize(glyphData_proto& out) const
	{
		out.set_key(this->key);
		out.set_x(this->x);
		out.set_y(this->y);
		out.set_width(this->width);
		out.set_height(this->height);
	}

	void glyphData::Deserialize(const glyphData_proto& in)
	{
		this->key = in.key();
		this->x = in.x();
		this->y = in.y();
		this->width = in.width();
		this->height = in.height();
	}
}