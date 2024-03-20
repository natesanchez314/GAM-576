//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Game.h"
#include "MathEngine.h"
#include "GameObjectAnim.h"
#include "GraphicsObject.h"

namespace Azul
{

	GameObjectAnim::GameObjectAnim(GraphicsObject *pGraphicsObject)
		: GameObject(pGraphicsObject),
		index(-1)
	{
		
	}

	void GameObjectAnim::Update(AnimTime currentTime)
	{

	}


}

// --- End of File ---
