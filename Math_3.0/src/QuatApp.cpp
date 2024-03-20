//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MathEngine.h"
#include "MathApp.h"

//----------------------------------------------------------------------------- 
// Mutates result to be a slerp between the source and target by the
// specified factor.
// For a factor of 0.0, result == source.
// For a factor of 1.0, result == target.
//----------------------------------------------------------------------------- 

namespace Azul
{  
	void QuatApp::Slerp(Quat& result, const Quat& source, const Quat& target, const float slerpFactor)
	{
		Quat tar = Quat(target);
		float tmpCos = source.dot(target);
		if (tmpCos < 0.0f)
		{
			tmpCos = -tmpCos;
			tar = -tar;
		}
		if (slerpFactor == 0.0f)
			result = source;
		else if (slerpFactor == 1.0f)
			result = tar;
		else
		{
			float angle = Trig::acos(tmpCos);
			float s = Trig::sin(angle);
			if (s != 0.0f)
				result = source * (Trig::sin((1 - slerpFactor) * angle) / s) + tar * (Trig::sin(slerpFactor * angle) / s);
		}
	}

	void QuatApp::SlerpArray(Quat* result, const Quat* source, const Quat* target, const float slerpFactor, const int numQuats)
	{
		for (int i = 0; i < numQuats; i++)
		{
			Slerp(result[i], source[i], target[i], slerpFactor);
		}
	}

}

// ---  End of File ---------------
