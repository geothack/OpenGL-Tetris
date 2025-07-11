#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer(OpenGLSprite& sprite, Transform& transform, Material& material) : mSprite(&sprite), mTransform(&transform), mMaterial(&material)
{
	::glClearColor(0.5, 0.0, 0.0, 1.0);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
	::glClear(GL_COLOR_BUFFER_BIT);

    mMaterial->Attach();

    mMaterial->SetMat4("model", *mTransform->GetWorldLocation());


    glBindVertexArray(mSprite->GetVertexArray());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
