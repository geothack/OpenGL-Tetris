#pragma once

#include "Render/OpenGLUniformBuffer.h"

class OpenGLSprite
{
public:
    OpenGLSprite();
    ~OpenGLSprite();

    uint32_t GetVertexArray();

    void Free();

private:
    void Init();

private:
    ::uint32_t mVAO;

    struct Camera
    {
        alignas(16) glm::mat4 Projection;
    };

    Camera mCameraData;

    OpenGLUniformBuffer mOpenGLUniformBuffer;
};

