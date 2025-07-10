#pragma once

#include "Render/Material.h"

class OpenGLSprite
{
public:
    OpenGLSprite() = default;
    OpenGLSprite(::Material& material);
    ~OpenGLSprite();
    void DrawSprite(glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f);

private:
    ::Material* mSpriteMaterial;
    ::uint32_t mVAO;
    void Init();
};

