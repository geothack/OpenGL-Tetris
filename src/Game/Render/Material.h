#pragma once


#include "Render/OpenGLShader.h"

struct Color
{
	float Red;
	float Green;
	float Blue;
};


class Material
{
public:
	Material() = default;
	Material(Color color);
	~Material();

	void Attach();

	void SetVec3(std::string_view name, const glm::vec3& value);

	void SetMat4(std::string_view name, const glm::mat4& value);

private:
	OpenGLShader mOpenGLShader;

	Color mColor;
};

