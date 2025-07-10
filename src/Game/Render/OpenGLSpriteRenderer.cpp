#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer()
{
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
	::glClearColor(0.5, 0.0, 0.0, 1.0);
	::glClear(GL_COLOR_BUFFER_BIT);
}
