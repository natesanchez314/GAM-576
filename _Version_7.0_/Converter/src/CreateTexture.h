//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CREATE_TEXTURE_H
#define CREATE_TEXTURE_H

#include "textureData.h"

namespace Azul
{
	void CreateTextureTGA(const char *const pName);
	void CreateTexturePNG(const char *const pName);
	textureData CreateAndReturnTextureTGA(const char* const pName);
}

#endif

// --- End of File ---
