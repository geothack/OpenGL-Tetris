#pragma once

class OpenGLSprite
{
public:
    OpenGLSprite();
    ~OpenGLSprite();

    uint32_t GetVertexArray();

    void Free();

private:
    ::uint32_t mVAO;
    void Init();
};

