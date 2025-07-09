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

private:
	OpenGLShader mOpenGLShader;

	Color mColor;
};

