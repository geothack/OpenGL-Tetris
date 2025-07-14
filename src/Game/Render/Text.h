#pragma once

#include "Render/Material.h"
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

class ZText
{
public:
	ZText() = default;
	ZText(const int height, const std::string& message);
	~ZText() = default;

	bool LoadFont(const std::filesystem::path& path);
	void RenderFont(Window* window, TextAttributes attribs, Material* shader);

	std::string Message = "";

private:
	std::map<GLchar, Character> mCharacters;

	uint32_t mVAO;
	uint32_t mVBO;

	int mHeight;

	glm::mat4 mTransform;

};

