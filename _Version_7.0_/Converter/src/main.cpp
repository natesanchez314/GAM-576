//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


// -------------------------
// Anim Converter 3
// -------------------------


#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"
#include "ChickenBot.h"
#include "CreateTexture.h"
#include "GLTF.h"
#include "StringThis.h"
#include "meshData.h"
#include "meshDataConverter.h"
#include "json.hpp"
#include "File.h"
#include "ShaderLayout.h"
#include "MathEngine.h"
#include "Skeleton.h"
#include "Anim.h"
#include "CreateModel.h"
#include "Font.h"
#include "CreateSkel.h"
#include "Skin.h"
#include "Hierarchy.h"
#include "InvBind.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;


int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Create custom models/texture into proto format
	// Need to be converted each time the format changes
	CreateCubeMesh();
	CreatePyramidMesh();
	CreateSphereMesh();
	CreateTextureTGA("Aliens.tga");
	CreateTextureTGA("HotPink.tga");
	CreateTextureTGA("Rocks.tga");
	CreateTextureTGA("Duckweed.tga");
	CreateTextureTGA("RedBrick.tga");
	CreateTextureTGA("Stone.tga");
	CreateTextureTGA("space_frigate.tga");
	CreateTexturePNG("R2D2_BaseColor.png");
	CreateTexturePNG("crate_BaseColor.png");
	CreateTexturePNG("ChickenbotDiffuse.png");  //<--- use this for the model
	CreateTexturePNG("Ch14_1001_Diffuse.png");
	CreateChickenBotModels();
	CreateModel("space_frigate");
	CreateModel("R2-D2");
	CreateModel("wooden crate");
	CreateFontAndTexture("FontTexture", "Metrics.xml");
	CreateSkeleton("walk_mesh", "chickenbot");
	CreateSkeleton("Joyful Jump", "mousey");

	// Animations for chicken bot
	ANIM::CreateAnimFromFile("walk_mesh");
	ANIM::CreateAnimFromFile("turn_left+mesh");
	ANIM::CreateAnimFromFile("hit_front+mesh");
	ANIM::CreateAnimFromFile("shot_front+mesh");

	// Animations for mousey
	ANIM::CreateAnimFromFile("Joyful Jump");
	ANIM::CreateAnimFromFile("Mousey_Happy_walk");
	ANIM::CreateAnimFromFile("Mousey_Run_Forward");

	CreateSkin("walk_mesh", "chickenbot");
	CreateSkin("Joyful Jump", "mousey");

	CreateHierarchy("walk_mesh", "chickenbot");
	CreateHierarchy("Joyful Jump", "mousey");

	CreateInvBind("walk_mesh", "chickenbot");
	CreateInvBind("Joyful Jump", "mousey");

	google::protobuf::ShutdownProtobufLibrary();

	// -----------------------------------------------
	// Getting this directory name programmatically 
	// trying to get: _Version_1.0_
	// HACK city below... need to do cleanly
	// -----------------------------------------------
	
	size_t len = strlen(SOLUTION_DIR) +1;
	char *pDir = new char[len]();
	memcpy(pDir, SOLUTION_DIR, len);
	
	char *pEnd = nullptr;
	char *pStart = nullptr;
	int count = 0;
	// find the start and end ptr of desired string
	for(size_t i = len; i != 0; i--)
	{
		char data = pDir[i];
		if( data == 92 && count==0)
		{
			count++;
			pEnd = &pDir[i];
			continue;
		}
		if(data == 92 && count == 1)
		{
			count++;
			pEnd = &pDir[i];
			continue;
		}
		if(data == 92 && count == 2)
		{
			count++;
			pStart = &pDir[i];
			pStart += 1;
			break;
		}
	}

	char *pVerName = new char[256]();
	memset(pVerName, 0, 256);
	memcpy_s(pVerName, 256, pStart, (size_t)(pEnd - pStart));

	char *pCopyCmd = new char[256]();
	memset(pCopyCmd, 0, 256);
	sprintf_s(pCopyCmd, 256, "copy *.azul .\\..\\%s\\Data", pVerName);

	system(pCopyCmd);
	system("del *.azul");

	delete pCopyCmd;
	delete pVerName;
	delete pDir;

	//google::protobuf::ShutdownProtobufLibrary();

	return 0;

}

// ---  End of File ---------------
