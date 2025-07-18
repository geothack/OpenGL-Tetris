#include "Utility/PreLibrary.h"
#include "OpenGLTextRenderer.h"
#include "Render/OpenGLText.h"


OpenGLTextRenderer::OpenGLTextRenderer(Scene& scene) : mScene(&scene)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

OpenGLTextRenderer::~OpenGLTextRenderer()
{
}

void OpenGLTextRenderer::Update()
{

      auto view = mScene->GetRegister()->view<OpenGLText, OpenGLShader>();

      for (auto [entity, text, shader] : view.each())
      {
          auto copyX = text.TextAttribs.X;
          shader.Attach();
          shader.SetVec3("textColor", glm::vec3(text.TextAttribs.Color.x, text.TextAttribs.Color.y, text.TextAttribs.Color.z));
          glActiveTexture(GL_TEXTURE0);
          glBindVertexArray(text.GetVertexArray());

          glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
          shader.Attach();
          shader.SetMat4("projection", projection);

          std::string::const_iterator c;
          for (c = text.Message.begin(); c != text.Message.end(); c++)
          {
              Character ch = text.Characters[*c];

              if (*c == '\n')
              {
                  text.TextAttribs.Y -= ((ch.Size.y)) * 1.3 * text.TextAttribs.Scale;
                  text.TextAttribs.X = copyX;
              }
              else if (*c == ' ')
              {
                  text.TextAttribs.X += ((ch.Advance >> 6)) * text.TextAttribs.Scale;
              }
              else
              {

                  float xpos = text.TextAttribs.X + ch.Bearing.x * text.TextAttribs.Scale;
                  float ypos = text.TextAttribs.Y - (ch.Size.y - ch.Bearing.y) * text.TextAttribs.Scale;

                  text.Transform = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.Size.x * text.TextAttribs.Scale, ch.Size.y * text.TextAttribs.Scale, 0));
                  shader.SetMat4("transform", text.Transform);

                  glBindTexture(GL_TEXTURE_2D, ch.TextureID);
                  glBindBuffer(GL_ARRAY_BUFFER, text.GetVertexBuffer());

                  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
                  text.TextAttribs.X += (ch.Advance >> 6) * text.TextAttribs.Scale;
              }
          }
          text.TextAttribs.X = copyX;
          glBindVertexArray(0);
          glBindBuffer(GL_ARRAY_BUFFER, 0);
          glBindTexture(GL_TEXTURE_2D, 0);
      }
    
}
