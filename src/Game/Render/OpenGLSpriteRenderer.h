#pragma once

#include "Render/Renderer.h"

class OpenGLSpriteRenderer : public Renderer
{
public:
	OpenGLSpriteRenderer();
	~OpenGLSpriteRenderer() override;

	void Update() override;
};

