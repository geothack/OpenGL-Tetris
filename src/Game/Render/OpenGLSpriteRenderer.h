#pragma once

#include "WorldTypes/Entity.h"

class OpenGLSpriteRenderer : public Renderer
{
public:
	OpenGLSpriteRenderer() = default;
	OpenGLSpriteRenderer(Scene& scene);
	~OpenGLSpriteRenderer() override;

	void Update() override;

private:
	Scene* mScene;
};

