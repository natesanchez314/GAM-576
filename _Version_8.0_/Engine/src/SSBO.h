#ifndef SSBO_H
#define SSBO_H

#include "sb7.h"

class SSBO
{
public:
	enum class Access
	{
		READ = GL_READ_ONLY,
		WRITE = GL_WRITE_ONLY,
		READ_WRITE = GL_READ_WRITE
	};

private:
	GLuint ssbo;
	unsigned int count;
	unsigned int size;
	void* buff;

public:
	SSBO();
	SSBO(const SSBO&) = default;
	SSBO& operator=(const SSBO&) = default;
	~SSBO();

	void Set(unsigned int count, unsigned int size, void* data);

	unsigned int GetLocation() const;
	void Bind(unsigned int location);
	void* Map(SSBO::Access access);
	void Unmap();		
};

#endif // !SSBO_H
