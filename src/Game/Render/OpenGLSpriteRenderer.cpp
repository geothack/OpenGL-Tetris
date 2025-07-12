#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"
#include "Render/Material.h"
#include "WorldTypes/Transform.h"
#include "Render/OpenGLSprite.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer(Entity& player) : mPlayer(&player)
{
	::glClearColor(0.5, 0.0, 0.0, 1.0);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
	::glClear(GL_COLOR_BUFFER_BIT);

    mPlayer->GetComponent<Material>()->Attach();

    mPlayer->GetComponent<Material>()->SetMat4("model", *mPlayer->GetComponent<Transform>()->GetWorldLocation());


    glBindVertexArray(mPlayer->GetComponent<OpenGLSprite>()->GetVertexArray());
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
