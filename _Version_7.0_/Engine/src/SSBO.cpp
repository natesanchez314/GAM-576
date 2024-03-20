   #include "SSBO.h"

SSBO::SSBO()
	: ssbo(), count(0), size(0), buff(nullptr)
{ 
	glGenBuffers(1, &ssbo);
}

SSBO::~SSBO()
{ 
	this->buff = nullptr;
	glDeleteBuffers(1, &ssbo);
}

void SSBO::Set(unsigned int _count, unsigned int _size, void* data)
{
	this->count = _count;
	this->size = _size;
	this->buff = data;

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, this->ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)(this->count * this->size), this->buff, GL_STATIC_DRAW);
}

unsigned int SSBO::GetLocation() const
{ 
	return this->ssbo;
}

void SSBO::Bind(unsigned int location)
{ 
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, location, this->ssbo);
}

void* SSBO::Map(SSBO::Access access)
{ 
	void* res = glMapNamedBuffer(this->ssbo, GLenum(access));
	return res;
}

void SSBO::Unmap()
{ 
	glUnmapNamedBuffer(this->ssbo);
}