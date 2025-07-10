#include "Utility/PreLibrary.h"
#include "OpenGLSprite.h"

OpenGLSprite::OpenGLSprite(::Material& material) : mSpriteMaterial(&material)
{
	Init();
}

OpenGLSprite::~OpenGLSprite()
{
	//::glDeleteVertexArrays(1, &mVAO);
}

void OpenGLSprite::DrawSprite(glm::vec2 position, glm::vec2 size, float rotate)
{
    mSpriteMaterial->Attach();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); 

    model = glm::scale(model, glm::vec3(size, 1.0f)); 

    mSpriteMaterial->SetMat4("model", model);

    //glActiveTexture(GL_TEXTURE0);
    //texture.Bind();

    glBindVertexArray(mVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void OpenGLSprite::Init()
{
    uint32_t VBO;
    float vertices[] = 
    {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(mVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), static_cast<float>(600), 0.0f, -1.0f, 1.0f);

    mSpriteMaterial->SetMat4("projection", projection);
}
