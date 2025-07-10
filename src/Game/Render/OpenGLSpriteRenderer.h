#pragma once

#include "WorldTypes/Transform.h"
#include "Render/Material.h"
#include "Render/OpenGLSprite.h"

class OpenGLSpriteRenderer : public Renderer
{
public:
	OpenGLSpriteRenderer() = default;
	OpenGLSpriteRenderer(OpenGLSprite& sprite, Transform& transform, Material& material);
	~OpenGLSpriteRenderer() override;

	void Update() override;

private:
	OpenGLSprite* mSprite;
	Transform* mTransform;
	Material* mMaterial;
};

