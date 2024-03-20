//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GameMan.h"
#include "google\protobuf\message_lite.h"

using namespace Azul;

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Game is inside a singleton
	GameMan::Create("w1(4) 2D Shader ", 1600, 1200);

	Game *pGame = GameMan::GetGame();
	pGame->Run();

	GameMan::Destroy();

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

// ---  End of File ---


