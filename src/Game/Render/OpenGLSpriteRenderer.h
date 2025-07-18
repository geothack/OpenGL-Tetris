#pragma once

#include "Render/OpenGLFrameBuffer.h"

class OpenGLSpriteRenderer : public Renderer
{
public:
	OpenGLSpriteRenderer() = default;
	OpenGLSpriteRenderer(Scene& scene, OpenGLShader& shakeScreen);
	~OpenGLSpriteRenderer() override;

	void Update() override;

private:
	Scene* mScene;
	OpenGLShader* mShakeScreen;

	OpenGLFrameBuffer mFrameBuffer;
};

