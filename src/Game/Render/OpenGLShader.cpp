#include "OpenGLShader.h"
#include "Utility/Verify.h"

OpenGLShader::OpenGLShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		MakeShader(vertexShaderPath, fragShaderPath);
	}
	else
	{
		MakeShader(vertexShaderPath, fragShaderPath, geoShaderPath);
	}
}

void OpenGLShader::MakeShader(const std::filesystem::path& vertexShaderPath, const std::filesystem::path& fragShaderPath, const std::filesystem::path& geoShaderPath)
{
	if (geoShaderPath.empty())
	{
		Create(mVertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(mFragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		LinkShader();
	}
	else
	{
		Create(mVertex, vertexShaderPath.string().c_str(), GL_VERTEX_SHADER);
		Create(mFragment, fragShaderPath.string().c_str(), GL_FRAGMENT_SHADER);
		Create(mGeometry, fragShaderPath.string().c_str(), GL_GEOMETRY_SHADER);
		LinkShader();
	}
}

void OpenGLShader::Attach() const
{
	glUseProgram(mProgram);
}

void OpenGLShader::Create(uint32_t& shader, const char* path, uint32_t type)
{
	std::ifstream file;

	std::stringstream ssfile;

	std::string code;

	file.open(path);
	std::stringstream vShaderStream;
	ssfile << file.rdbuf();

	file.close();
	code = ssfile.str();
	const char* glShader = code.c_str();

	shader = glCreateShader(type);
	glShaderSource(shader, 1, &glShader, NULL);
	glCompileShader(shader);
	// check for shader compile errors

	glGetShaderiv(shader, GL_COMPILE_STATUS, &mSuccess);

	glGetShaderInfoLog(shader, 512, NULL, mInfoLog);
	std::string error = std::format("Failed to compile shader {}", mInfoLog);

	Verify::Update(error, mSuccess);

}

void OpenGLShader::LinkShader()
{
	mProgram = glCreateProgram();
	glAttachShader(mProgram, mVertex);
	glAttachShader(mProgram, mFragment);
	glLinkProgram(mProgram);
	// check for linking errors
	glGetProgramiv(mProgram, GL_LINK_STATUS, &mSuccess);

	glGetProgramInfoLog(mProgram, 512, NULL, mInfoLog);
	std::string error = std::format("Failed to link program {}", mInfoLog);

	Verify::Update(error, mSuccess);
	
	glDeleteShader(mVertex);
	glDeleteShader(mFragment);
}