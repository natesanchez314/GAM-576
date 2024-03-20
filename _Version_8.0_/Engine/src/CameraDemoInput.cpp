//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CameraDemoInput.h"
#include "InputMan.h"
#include "Keyboard.h"
#include "CameraMan.h"

namespace Azul
{
	void CameraDemoInput()
	{
		Keyboard *key = InputMan::GetKeyboard();

		if(key->GetKeyState(Keyboard::KEY_SPACE))
		{
			Camera3D *pCamera = CameraMan::GetCurrent3D();

			if(pCamera->getName() == Camera::Name::CAMERA_0)
			{
				CameraMan::SetCurrent3D(Camera::Name::CAMERA_1);
			}
			else
			{
				CameraMan::SetCurrent3D(Camera::Name::CAMERA_0);
			}
		}

		if(key->GetKeyState(Keyboard::KEY_0))
		{
			CameraMan::SetCurrent3D(Camera::Name::CAMERA_0);
		}

		if(key->GetKeyState(Keyboard::KEY_1))
		{
			CameraMan::SetCurrent3D(Camera::Name::CAMERA_1);
		}

		if(key->GetKeyState(Keyboard::KEY_2))
		{
			CameraMan::SetCurrent3D(Camera::Name::CAMERA_2);
		}

		if(key->GetKeyState(Keyboard::KEY_3))
		{
			CameraMan::SetCurrent3D(Camera::Name::CAMERA_3);
		}
	}

}

// --- End of File ---
