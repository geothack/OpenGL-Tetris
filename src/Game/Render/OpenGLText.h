#pragma once

#include "Render/OpenGLShader.h"
#include "Window/Window.h"

struct Character
{
	uint32_t TextureID; 
	glm::ivec2   Size;      
	glm::ivec2   Bearing;   
	uint32_t Advance;   
};

struct TextAttributes
{
	float X = 0.0f;
	float Y = 0.0f;
	float Scale = 0.0f;
	glm::vec3 Color = glm::vec3(1.0f);
};

class OpenGLText
{
public:
	OpenGLText() = default;
	OpenGLText(const int height, std::string_view message, TextAttributes attribs, OpenGLShader& shader);
	~OpenGLText() = default;

	bool LoadFont(const std::filesystem::path& path);
	void RenderFont();

	std::string Message = "";

	TextAttributes TextAttribs;

	glm::mat4 Transform;

	std::map<GLchar, Character> Characters;

	inline const uint32_t const GetVertexArray() const { return mVAO; }
	inline const uint32_t const GetVertexBuffer() const { return mVBO; }

private:
	OpenGLShader* mTextShader;

	uint32_t mVAO;
	uint32_t mVBO;

	int mHeight;

};

