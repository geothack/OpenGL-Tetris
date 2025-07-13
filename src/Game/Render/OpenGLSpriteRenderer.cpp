#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"
#include "Render/Material.h"
#include "WorldTypes/Transform.h"
#include "Render/OpenGLSprite.h"
#include "Render/OpenGLTexture.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer(Scene& scene) : mScene(&scene)
{
	::glClearColor(0.0, 0.0, 0.0, 1.0);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
	::glClear(GL_COLOR_BUFFER_BIT);

    auto view = mScene->GetRegister()->view<Transform, OpenGLSprite, Material>();

    for (auto [entity,transform,sprite,material] : view.each())
    { 
        material.Attach();

        material.SetMat4("model", *transform.GetWorldLocation());

        glBindVertexArray(sprite.GetVertexArray());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    auto shaderView = mScene->GetRegister()->view<Transform, OpenGLSprite, OpenGLShader,OpenGLTexture>();

    for (auto [entity, transform, sprite, shader,texture] : shaderView.each())
    {
        shader.Attach();
        glBindTextureUnit(0, texture.GetHandle());

        shader.SetMat4("model", *transform.GetWorldLocation());
        auto Projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);
        shader.SetMat4("projection", Projection);

        glBindVertexArray(sprite.GetVertexArray());
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

}
