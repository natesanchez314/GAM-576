//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "sb7.h"
#include "MathEngine.h"
#include "MathApp.h"
#include "Game.h"
#include "GameObject.h"
#include "ShaderObject.h"
#include "ProtoMesh.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "GraphicsObject_FlatTexture.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include "TextureMan.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Camera.h"
#include "Camera3D.h"
#include "Camera2D.h"
#include "GameObjectMan.h"
#include "MeshNodeMan.h"
#include "ShaderMan.h"
#include "CameraMan.h"
#include "CameraMesh.h"
#include "CameraDemoInput.h"
#include "GameObjectBoundingSphere.h"
#include "AnimTimer.h"
#include "Anim.h"
#include "TimerController.h"
#include "AnimController.h"
#include "Clip.h"
#include "ImageMan.h"
#include "GraphicsObject_Sprite.h"
#include "SpriteMesh.h"
#include "GameObject2D.h"
#include "ClipMan.h"
#include "AnimMan.h"
#include "GameObject.h"
#include "GameObjectBasic.h"
#include "FontMan.h"
#include "GlyphMan.h"
#include "SSBO.h"
#include "WorldCompute.h"
#include "GameObjectAnimSkin.h"
#include "GraphicsObject_SkinTexture.h"

using namespace Azul;

namespace Azul
{
	// Todo: clean up
	AnimController* pAnimControllerA;
	AnimController* pAnimControllerB;
	Font* fontA;
	Font* fontB;
	Font* fontC;
	unsigned int count = 0;
	Vec4* lightColor = nullptr;
	Vec3* lightPos = nullptr;

	//-----------------------------------------------------------------------------
	//  Game::Game()
	//		Game Engine Constructor
	//-----------------------------------------------------------------------------
	Game::Game(const char* const pWindowName, const int Width, const int Height)
		:Engine(pWindowName, Width, Height),
		pProtoVersion(nullptr)
	{
		assert(pWindowName);
		this->globalTimer.Tic();
		this->intervalTimer.Tic();
	}

	//-----------------------------------------------------------------------------
	//  Game::~Game()
	//		Game Engine destructor
	//-----------------------------------------------------------------------------
	Game::~Game()
	{ }

	//-----------------------------------------------------------------------------
	// Game::Initialize()
	//		Allows the engine to perform any initialization it needs to before 
	//      starting to run.  This is where it can query for any required services 
	//      and load any non-graphic related content. 
	//-----------------------------------------------------------------------------
	void Game::Initialize()
	{ }

	//-----------------------------------------------------------------------------
	// Game::LoadContent()
	//		Allows you to load all content needed for your engine,
	//	    such as objects, graphics, etc.
	//-----------------------------------------------------------------------------
	void Game::LoadContent()
	{
		// Set the Asset proto version for checking.
		this->SetProtoVersion("1.0.1");

		// Start the managers
		InputMan::Create();
		TextureMan::Create();
		MeshNodeMan::Create();
		ShaderMan::Create();
		CameraMan::Create();
		GameObjectMan::Create();
		ImageMan::Create();
		ClipMan::Create();
		AnimMan::Create();
		FontMan::Create();
		GlyphMan::Create();

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 3D perspective Camera
		//---------------------------------------------------------------------------------------------------------
		Camera3D* pCam0 = new Camera3D();
		pCam0->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam0->setPerspective(35.0f, float(pCam0->getScreenWidth()) / float(pCam0->getScreenHeight()), 1.0f, 10000.0f);
		pCam0->setOrientAndPosition(Vec3(1.0f, 0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(-1.0f, 12.0f, 0.0f));
		pCam0->updateCamera();
		CameraMan::Add(Camera::Name::CAMERA_0, pCam0);
		CameraMan::SetCurrent3D(Camera::Name::CAMERA_0);

		//---------------------------------------------------------------------------------------------------------
		// Setup the current 2D orthographic Camera
		//---------------------------------------------------------------------------------------------------------
		Camera2D* pCam2D = new Camera2D();

		pCam2D->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);
		pCam2D->setOrthographic((float)-pCam2D->getScreenWidth() / 2.0f, (float)pCam2D->getScreenWidth() / 2.0f,
			(float)-pCam2D->getScreenHeight() / 2.0f, (float)pCam2D->getScreenHeight() / 2.0f,
			1.0f, 1000.0f);
		pCam2D->setOrientAndPosition(Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, 2.0f));

		// Holder for the current 2D  cameras
		CameraMan::Add(Camera::Name::CAMERA_1, pCam2D);
		CameraMan::SetCurrent2D(Camera::Name::CAMERA_1);

		// -----------------------------------
		// Load the Mesh from Data file
		// -----------------------------------
		Mesh* pPyramidMesh = new ProtoMesh("PyramidMesh.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::PYRAMID, pPyramidMesh);
		Mesh* spaceFrigateMesh = new ProtoMesh("space_frigate.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::SPACE_FRIGATE, spaceFrigateMesh);
		Mesh* r2d2Mesh = new ProtoMesh("R2-D2.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::R2D2, r2d2Mesh);
		Mesh* crateMesh = new ProtoMesh("wooden crate.m.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CRATE, crateMesh);
		Mesh* chickenBotMesh = new ProtoMesh("chickenbot.skin.proto.azul");
		MeshNodeMan::Add(Mesh::Name::CHICKEN_BOT, chickenBotMesh);
		Mesh* mouseyMesh = new ProtoMesh("mousey.skin.proto.azul");
		MeshNodeMan::Add(Mesh::Name::MOUSEY, mouseyMesh);

		// Load the Sprite Mesh
		SpriteMesh* pSpriteMesh = new SpriteMesh("SpriteModel.azul");
		assert(pSpriteMesh);
		MeshNodeMan::Add(Mesh::Name::SPRITE, pSpriteMesh);

		// ----------------------------------
		// Create/Load Shader 
		// ----------------------------------
		ShaderObject* pShaderObject_sprite;
		pShaderObject_sprite = ShaderMan::Add(ShaderObject::Name::SPRITE, "spriteRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_sprite);

		ShaderObject* pShaderObject_constcolor;
		pShaderObject_constcolor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constColorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_constcolor);

		ShaderObject* pShaderObject_color;
		pShaderObject_color = ShaderMan::Add(ShaderObject::Name::COLOR_POSITION, "colorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_color);

		ShaderObject* pShaderObject_texture;
		pShaderObject_texture = ShaderMan::Add(ShaderObject::Name::TEXTURE_SIMPLE, "textureRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_texture);

		ShaderObject* pShaderObject_textureLight;
		pShaderObject_textureLight = ShaderMan::Add(ShaderObject::Name::TEXTURE_POINT_LIGHT, "texturePointLightDiff", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_textureLight);

		ShaderObject* pShaderObject_constColor;
		pShaderObject_constColor = ShaderMan::Add(ShaderObject::Name::CONST_COLOR, "constcolorRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_constColor);

		ShaderObject* pShaderObject_colorSingle;
		pShaderObject_colorSingle = ShaderMan::Add(ShaderObject::Name::COLOR_SINGLE, "colorSingleRender", ShaderObject::Type::GRAPHICS);
		assert(pShaderObject_colorSingle);

		ShaderObject* shaderObject_skin;
		shaderObject_skin = ShaderMan::Add(ShaderObject::Name::SKIN, "skinTextureRender", ShaderObject::Type::GRAPHICS);
		assert(shaderObject_skin);

		ShaderObject* shaderObject_computeTest;
		shaderObject_computeTest = ShaderMan::Add(ShaderObject::Name::COMPUTE_TEST, "computeTest", ShaderObject::Type::COMPUTE);

		ShaderObject* shaderObject_mixer;
		shaderObject_mixer = ShaderMan::Add(ShaderObject::Name::MIXER, "computeMixer", ShaderObject::Type::COMPUTE);
		assert(shaderObject_mixer);

		ShaderObject* shaderObject_world;
		shaderObject_world = ShaderMan::Add(ShaderObject::Name::WORLD, "computeWorldMat", ShaderObject::Type::COMPUTE);
		assert(shaderObject_world);

		// ------------------------------------------
		// Load Textures from Data File
		// ------------------------------------------
		TextureMan::Add("HotPink.t.proto.azul", Texture::Name::HOT_PINK);
		TextureMan::Add("Aliens.t.proto.azul", Texture::Name::INVADERS);
		TextureMan::Add("Duckweed.t.proto.azul", Texture::Name::DUCKWEED);
		TextureMan::Add("Rocks.t.proto.azul", Texture::Name::ROCKS);
		TextureMan::Add("Stone.t.proto.azul", Texture::Name::STONES);
		TextureMan::Add("RedBrick.t.proto.azul", Texture::Name::RED_BRICK);
		TextureMan::Add("space_frigate.t.proto.azul", Texture::Name::SPACE_FRIGATE);
		TextureMan::Add("R2D2_BaseColor.t.proto.azul", Texture::Name::R2D2);
		TextureMan::Add("ChickenbotDiffuse.t.proto.azul", Texture::Name::CHICKEN_BOT);
		TextureMan::Add("FontTexture.t.proto.azul", Texture::Name::FONT);
		TextureMan::Add("crate_BaseColor.t.proto.azul", Texture::Name::CRATE);
		TextureMan::Add("Ch14_1001_Diffuse.t.proto.azul", Texture::Name::MOUSEY);

		// -------------------------------------------
		// Images
		// -------------------------------------------
		Image* greenAlienImage = new Image(Image::Name::Alien_Green, Texture::Name::INVADERS, Rect(136.0f, 64.0f, 85.0f, 63.0f));
		Image* redAlienImage = new Image(Image::Name::Alien_Red, Texture::Name::INVADERS, Rect(554.0f, 63.0f, 98.0f, 64.0f));

		static_assert(sizeof(Image) == 36, "wrong size");

		ImageMan::Add(greenAlienImage);
		ImageMan::Add(redAlienImage);

		// --------------------------------------------
		// Sprite
		// --------------------------------------------
		GraphicsObject_Sprite* pGraphics_Sprite = new GraphicsObject_Sprite(pSpriteMesh, pShaderObject_sprite, greenAlienImage, Rect(600, 200, 200, 200));
		GameObject2D* greenAlien = new GameObject2D(pGraphics_Sprite);
		GameObjectMan::Add(greenAlien, GameObjectMan::GetRoot());

		greenAlien->SetName("GREEN ALIEN");

		pGraphics_Sprite = new GraphicsObject_Sprite(pSpriteMesh, pShaderObject_sprite, redAlienImage, Rect(1000, 200, 200, 200));
		GameObject2D* redAlien = new GameObject2D(pGraphics_Sprite);
		GameObjectMan::Add(redAlien, GameObjectMan::GetRoot());

		greenAlien->SetName("RED ALIEN");

		// --------------------------------------------
		// Text
		// --------------------------------------------
		GlyphMan::AddGlyphs(Glyph::Name::DEFAULT, "FontTexture.font.proto.azul", Texture::Name::FONT);
		fontA = FontMan::Add(Font::Name::ANIM_A, Mesh::Name::SPRITE, ShaderObject::Name::SPRITE, "Walk", Glyph::Name::DEFAULT, 600, 400);
		fontB = FontMan::Add(Font::Name::ANIM_B, Mesh::Name::SPRITE, ShaderObject::Name::SPRITE, "Joyful Jump", Glyph::Name::DEFAULT, 900, 400);
		fontC = FontMan::Add(Font::Name::COUNT, Mesh::Name::SPRITE, ShaderObject::Name::SPRITE, "Count: 0", Glyph::Name::DEFAULT, 800, 1000);

		// -------------------------------------------
		// Mesh Game Objects
		// -------------------------------------------
		GraphicsObject_FlatTexture* pSpaceFrigateTexture = new GraphicsObject_FlatTexture(spaceFrigateMesh, pShaderObject_texture, Texture::Name::SPACE_FRIGATE);
		GameObjectBasic* spaceFrigate = new GameObjectBasic(pSpaceFrigateTexture);
		spaceFrigate->SetScale(0.05f, 0.05f, 0.05f);
		spaceFrigate->SetTrans(-3.0f, 0.0f, 3.0f);
		spaceFrigate->delta_x = 0.005f;
		spaceFrigate->delta_y = -0.005f;
		GameObjectMan::Add(spaceFrigate, GameObjectMan::GetRoot());

		GraphicsObject_FlatTexture* r2d2Texture = new GraphicsObject_FlatTexture(r2d2Mesh, pShaderObject_texture, Texture::Name::R2D2);
		GameObjectBasic* r2d2_a = new GameObjectBasic(r2d2Texture);
		r2d2_a->SetScale(75.0f, 75.0f, 75.0f);
		r2d2_a->SetTrans(1.0f, 0.0f, -3.0f);
		Quat q1(Quat::Rot1::Y, -MATH_PI2);
		Quat q2(Quat::Rot1::Z, MATH_PI);
		Quat q = q1 * q2;
		r2d2_a->SetQuat(q); 
		r2d2_a->delta_x = 0.01f;
		GameObjectMan::Add(r2d2_a, GameObjectMan::GetRoot());

		GraphicsObject_Wireframe* r2d2Wireframe = new GraphicsObject_Wireframe(r2d2Mesh, pShaderObject_color);
		GameObjectBasic* r2d2_b = new GameObjectBasic(r2d2Wireframe);
		r2d2_b->SetScale(75.0f, 75.0f, 75.0f);
		r2d2_b->SetTrans(1.0f, 0.0f, 3.0f);
		r2d2_b->SetQuat(q);
		r2d2_b->delta_x = 0.01f;
		GameObjectMan::Add(r2d2_b, GameObjectMan::GetRoot());

		GraphicsObject_FlatTexture* crateTexture = new GraphicsObject_FlatTexture(crateMesh, pShaderObject_texture, Texture::Name::CRATE);
		GameObjectBasic* crate = new GameObjectBasic(crateTexture);
		crate->SetScale(0.9f, 0.9f, 0.9f);
		crate->SetTrans(-3.0f, 0.0f, -3.0f);
		crate->delta_y = 0.05f;
		crate->delta_z = -0.05f;
		GameObjectMan::Add(crate, GameObjectMan::GetRoot());

		// ---------------------------------
		// Create Animation
		// ---------------------------------
		Vec3* scale = new Vec3(100, 100, 100);
		Vec3* pos = new Vec3(-3, 0, 0);
		lightColor = new Vec4(1.0f, 1.0f, 1.0f, 1.0f);
		lightPos = new Vec3(1.0f, 3.0f, 5.0f);

		Clip* chickenBotClip = ClipMan::Add(Clip::Name::BOT_WALK, "walk_mesh.anim.proto.azul");
		ClipMan::Add(Clip::Name::BOT_TURN_LEFT, "turn_left+mesh.anim.proto.azul");
		ClipMan::Add(Clip::Name::BOT_HIT_FRONT, "hit_front+mesh.anim.proto.azul");
		ClipMan::Add(Clip::Name::BOT_SHOT_FRONT, "shot_front+mesh.anim.proto.azul");
		ClipMan::Add(Clip::Name::MOUSEY_WALK, "Mousey_Happy_walk.anim.proto.azul");
		ClipMan::Add(Clip::Name::MOUSEY_RUN, "Mousey_Run_Forward.anim.proto.azul");
		Clip* mouseyClip = ClipMan::Add(Clip::Name::MOUSEY_JOYFUL_JUMP, "Joyful Jump.anim.proto.azul");
		
		// Chickenbot
		GraphicsObject_SkinTexture* chickenBotSkin = new GraphicsObject_SkinTexture(chickenBotMesh, shaderObject_skin, Texture::Name::CHICKEN_BOT, *lightColor, *lightPos);
		GameObjectAnimSkin* chickenBot = new GameObjectAnimSkin(chickenBotSkin);

		chickenBot->delta_y = 0.00f;
		chickenBot->SetScale(75.0f, 75.0f, 75.0f);
		chickenBot->SetTrans(-2.0f, 0.0f, -1.0f);

		GameObjectMan::Add(chickenBot, GameObjectMan::GetRoot());
		chickenBot->SetName("chicken bot");

		Anim* animA = new Anim(chickenBotClip);

		AnimTime deltaA = 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pAnimControllerA = new AnimController(deltaA, animA);

		Mixer* mixerA = new Mixer(animA);
		pAnimControllerA->mixer = mixerA;
		chickenBot->SetMixer(mixerA);

		WorldCompute* worldComputeA = new WorldCompute(mixerA, "chickenbot.hierarchy.proto.azul", "chickenbot.inv.proto.azul", ShaderObject::Name::WORLD);

		chickenBotSkin->worldCompute = worldComputeA;
		chickenBot->SetWorldCompute(worldComputeA);

		// Mousey
		GraphicsObject_SkinTexture* mouseySkin = new GraphicsObject_SkinTexture(mouseyMesh, shaderObject_skin, Texture::Name::MOUSEY, *lightColor, *lightPos);
		GameObjectAnimSkin* mousey = new GameObjectAnimSkin(mouseySkin);

		mousey->delta_y = 0.00f;
		mousey->SetScale(2.0f, 2.0f, 2.0f);
		mousey->SetTrans(-2.0f, 0.0f, 1.0f);

		GameObjectMan::Add(mousey, GameObjectMan::GetRoot());
		mousey->SetName("mousey");

		Anim* animB = new Anim(mouseyClip);

		AnimTime deltaB = 0.2f * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pAnimControllerB = new AnimController(deltaB, animB);

		Mixer* mixerB = new Mixer(animB);
		pAnimControllerB->mixer = mixerB;
		mousey->SetMixer(mixerB);

		WorldCompute* worldComputeB = new WorldCompute(mixerB, "mousey.hierarchy.proto.azul", "mousey.inv.proto.azul", ShaderObject::Name::WORLD);

		mouseySkin->worldCompute = worldComputeB;
		mousey->SetWorldCompute(worldComputeB);
		mousey->SetWorldCompute(worldComputeB);

		delete scale;
		delete pos;
	}

	//-----------------------------------------------------------------------------
	// Game::Update()
	//      Called once per frame, update data, tranformations, etc
	//      Use this function to control process order
	//      Input, AI, Physics, Animation, and Graphics
	//-----------------------------------------------------------------------------
	void Game::Update(float)
	{
		// ------------------------------------
		// Camera update
		// ------------------------------------
		if (InputMan::GetKeyboard()->GetKeyState(Keyboard::KEY_1))
		{
			fontA->UpdateMessage("Walk");
			pAnimControllerA->SetAnim(Clip::Name::BOT_WALK);
		}
		else if (InputMan::GetKeyboard()->GetKeyState(Keyboard::KEY_2))
		{
			fontA->UpdateMessage("Shot front");
			pAnimControllerA->SetAnim(Clip::Name::BOT_SHOT_FRONT);
		}
		else if (InputMan::GetKeyboard()->GetKeyState(Keyboard::KEY_3))
		{
			fontA->UpdateMessage("Hit Front");
			pAnimControllerA->SetAnim(Clip::Name::BOT_HIT_FRONT);
		}

		char a[64];
		snprintf(a, 64, "Count: %d", count++);
		fontC->UpdateMessage(a);

		Camera3D* pCam3D = CameraMan::GetCurrent3D();
		pCam3D->updateCamera();

		Camera2D* pCam2D = CameraMan::GetCurrent2D();
		pCam2D->updateCamera();

		// ------------------------------------------------
		// Timer update
		// ------------------------------------------------
		this->intervalTimer.Toc();
		this->intervalTimer.Tic();

		// ------------------------------------
		// Animate Me
		// ------------------------------------
		pAnimControllerA->Update();
		pAnimControllerB->Update();

		// ------------------------------------
		// Update GameObjects
		// ------------------------------------
		GameObjectMan::Update(this->globalTimer.Toc());
	}


	//-----------------------------------------------------------------------------
	// Game::Draw()
	//		This function is called once per frame
	//	    Use this for draw graphics to the screen.
	//      Only do rendering here
	//-----------------------------------------------------------------------------
	void Game::Draw()
	{
		GameObjectMan::Draw();
	}


	//-----------------------------------------------------------------------------
	// Game::UnLoadContent()
	//       unload content (resources loaded above)
	//       unload all content that was loaded before the Engine Loop started
	//-----------------------------------------------------------------------------
	void Game::UnLoadContent()
	{
		// Todo fix this - verify OpenGL removal

		//  glDeleteVertexArrays(1, &vao);
		//  glDeleteProgram(pShaderObject->programObject);
		//  glDeleteBuffers(1, &buffer);

		FontMan::Destroy();
		GlyphMan::Destroy();
		AnimMan::Destroy();
		ClipMan::Destroy();
		TextureMan::Destroy();
		InputMan::Destroy();
		GameObjectMan::Destroy();
		MeshNodeMan::Destroy();
		ShaderMan::Destroy();
		CameraMan::Destroy();
		ImageMan::Destroy();

		delete pAnimControllerA;
		delete pAnimControllerB;
		delete lightColor;
		delete lightPos;
	}

	//------------------------------------------------------------------
	// Game::ClearBufferFunc()
	// Allows user to change the way the clear buffer function works
	//------------------------------------------------------------------
	void Game::ClearBufferFunc()
	{
#ifdef _DEBUG
		const GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
#else
		const GLfloat color[] = { 0.85f, 0.7f, 0.7f, 1.0f };
#endif
		const GLfloat one = 1.0f;

		glViewport(0, 0, info.windowWidth, info.windowHeight);
		glClearBufferfv(GL_COLOR, 0, color);
		glClearBufferfv(GL_DEPTH, 0, &one);
	}


	void Game::SetProtoVersion(char* const pVersion)
	{
		assert(pVersion);

		this->pProtoVersion = pVersion;
	}

	const char* const Game::GetProtoVersion()
	{
		return this->pProtoVersion;
	}

}  // namespace 

// --- End of File ---
