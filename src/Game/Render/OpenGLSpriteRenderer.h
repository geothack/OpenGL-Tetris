#pragma once

#include "WorldTypes/Entity.h"

class OpenGLSpriteRenderer : public Renderer
{
public:
	OpenGLSpriteRenderer() = default;
	OpenGLSpriteRenderer(Entity& player);
	~OpenGLSpriteRenderer() override;

	void Update() override;

private:
	Entity* mPlayer;
};

