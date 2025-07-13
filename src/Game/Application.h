#pragma once

#include "Window/Window.h"
#include "Render/Material.h"
#include "Render/OpenGLSpriteRenderer.h"
#include "Render/OpenGLSprite.h"
#include "Render/OpenGLTexture.h"
#include "WorldTypes/Transform.h"

#include "Gameplay/Player.h"
#include "Gameplay/Block.h"
#include "Gameplay/Ball.h"

class Application
{
public:
	Application();
	~Application();

	void Update();

private:
	void Init();


private:
	::Window mGameWindow;

	::OpenGLSpriteRenderer mSpriteRenderer;

	// Scenes
	::Scene mMainScene;

	// Player
	Player mPlayer;

	// Ball
	Ball mBall;

	// Blocks
	std::array<Block, 30> mBlockArray;

	enum class BlockColor
	{
		None = -1,
		Green,
		Red,
		Blue,
		Yellow,
		Orange,
		Purple
	};


};

