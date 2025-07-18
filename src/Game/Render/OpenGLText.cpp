#include "Utility\PreLibrary.h"
#include "OpenGLText.h"

OpenGLText::OpenGLText(const int height, std::string_view message, TextAttributes attribs, OpenGLShader& shader) :mHeight(height), Message(message.data()),
    TextAttribs(attribs), mTextShader(&shader)
{
}

bool OpenGLText::LoadFont(const std::filesystem::path& path)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::println("ERROR::FREETYPE: Could not init FreeType Library");
        return -1;
    }

    std::string font_name = path.string();
    if (font_name.empty())
    {
        std::println("ERROR::FREETYPE: Failed to load font_name");
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) 
    {
        std::println("ERROR::FREETYPE: Failed to load font");
        return -1;
    }
    else 
    {
        FT_Set_Pixel_Sizes(face, 0, mHeight);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++)
        {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            {
                std::println("ERROR::FREETYTPE: Failed to load Glyph");
                continue;
            }
            uint32_t texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            Character character = 
            {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<uint32_t>(face->glyph->advance.x)
            };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    float vertex_data[] =
    {
        0.0f,1.0f,
        0.0f,0.0f,
        1.0f,1.0f,
        1.0f,0.0f
    };

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

void OpenGLText::RenderFont()
{
    auto copyX = TextAttribs.X;
    mTextShader->Attach();
    mTextShader->SetVec3("textColor", glm::vec3(TextAttribs.Color.x, TextAttribs.Color.y, TextAttribs.Color.z));
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(mVAO);

    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(800), 0.0f, static_cast<float>(600));
    mTextShader->Attach();
    mTextShader->SetMat4("projection", projection);
    //glUniformMatrix4fv(glGetUniformLocation(shader->GetHandle(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    std::string::const_iterator c;
    for (c = Message.begin(); c != Message.end(); c++)
    {
        Character ch = Characters[*c];

        if (*c == '\n')
        {
            TextAttribs.Y -= ((ch.Size.y)) * 1.3 * TextAttribs.Scale;
            TextAttribs.X = copyX;
        }
        else if (*c == ' ')
        {
            TextAttribs.X += ((ch.Advance >> 6)) * TextAttribs.Scale;
        }
        else
        {

            float xpos = TextAttribs.X + ch.Bearing.x * TextAttribs.Scale;
            float ypos = TextAttribs.Y - (ch.Size.y - ch.Bearing.y) * TextAttribs.Scale;

            Transform = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(ch.Size.x * TextAttribs.Scale, ch.Size.y * TextAttribs.Scale, 0));
            mTextShader->SetMat4("transform", Transform);

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, mVBO);

            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, 1);
            TextAttribs.X += (ch.Advance >> 6) * TextAttribs.Scale;
        }
    }
    //TextAttribs.X = copyX;
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
