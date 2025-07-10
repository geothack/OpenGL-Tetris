#include "Utility/PreLibrary.h"
#include "Material.h"

Material::Material(Color color) : mColor(color)
{
	mOpenGLShader = OpenGLShader("res/Shaders/Sprite.vert", "res/Shaders/Sprite.frag");
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

void Material::SetVec3(std::string_view name, const glm::vec3& value) const
{
	mOpenGLShader.SetVec3(name, value);
}

void Material::SetMat4(std::string_view name, const glm::mat4& value) const
{
	mOpenGLShader.SetMat4(name, value);
}
