#include "Material.h"

Material::Material(Color color) : mColor(color)
{
	mOpenGLShader = OpenGLShader("res/Shaders/Basic.vert", "res/Shaders/Basic.frag");
}

Material::~Material()
{
}

void Material::Attach() const
{
	mOpenGLShader.Attach();
	mOpenGLShader.SetFloat("Red", mColor.Red);
	mOpenGLShader.SetFloat("Green", mColor.Green);
	mOpenGLShader.SetFloat("Blue", mColor.Blue);
}
