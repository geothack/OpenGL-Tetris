#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer()
{
	::glClearColor(0.0, 0.0, 0.0, 1.0);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
	::glClear(GL_COLOR_BUFFER_BIT);
}
