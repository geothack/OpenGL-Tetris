#pragma once

#include "Render/OpenGLShader.h"
#include "Window/Window.h"

class OpenGLFrameBuffer
{
public:
	OpenGLFrameBuffer() = default;
	OpenGLFrameBuffer(OpenGLShader& shader);
	~OpenGLFrameBuffer();

	uint32_t GetColourTex() { return mTextureColorbuffer; }

	OpenGLShader* GetShader() { return mShader; }

	uint32_t GetVAO() { return mVAO; }

	uint32_t GetHandle() { return mFrameBuffer; }

private:
	uint32_t mVAO;
	uint32_t mVBO;
	uint32_t mFrameBuffer;
	uint32_t mTextureColorbuffer;
	uint32_t mRBO;

	OpenGLShader* mShader;

};

