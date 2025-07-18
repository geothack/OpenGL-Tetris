#include "Utility/PreLibrary.h"
#include "OpenGLSpriteRenderer.h"
#include "Render/Material.h"
#include "WorldTypes/Transform.h"
#include "Render/OpenGLSprite.h"
#include "Render/OpenGLTexture.h"

OpenGLSpriteRenderer::OpenGLSpriteRenderer(Scene& scene, OpenGLShader& shakeScreen) : mScene(&scene), mShakeScreen(&shakeScreen)
{
	::glClearColor(0.0, 0.0, 0.0, 1.0);
    mFrameBuffer = OpenGLFrameBuffer(*mShakeScreen);
}

OpenGLSpriteRenderer::~OpenGLSpriteRenderer()
{
}

void OpenGLSpriteRenderer::Update()
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer.GetHandle());
    //glEnable(GL_DEPTH_TEST);

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

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDisable(GL_DEPTH_TEST);
    //glClearColor(0.25f, 0.25f, 0.25f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);

    mShakeScreen->Attach();
    glBindVertexArray(mFrameBuffer.GetVAO());
    //glBindTexture(GL_TEXTURE_2D, mFrameBuffer.GetColourTex());	
    glBindTextureUnit(0, mFrameBuffer.GetColourTex());
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
