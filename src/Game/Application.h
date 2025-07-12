#pragma once

#include "Window/Window.h"
#include "Render/Material.h"
#include "Render/OpenGLSpriteRenderer.h"
#include "Render/OpenGLSprite.h"
#include "WorldTypes/Transform.h"

#include "Gameplay/Player.h"
#include "Gameplay/Piece.h"

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

	// Pieces
	Piece mLine;

	// Entities
	std::array<Entity, 200> mTetrisBoard;
};

