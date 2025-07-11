#pragma once


class OpenGLUniformBuffer
{
public:
	OpenGLUniformBuffer();

	template<typename T>
	void Init(const T& data)
	{
		glGenBuffers(1, &mOpenGLUniformBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, mOpenGLUniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(data), &data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	template<typename T, typename V>
	void Update(const T& data, const V& value)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, mOpenGLUniformBuffer, 0, sizeof(data));

		glBindBuffer(GL_UNIFORM_BUFFER, mOpenGLUniformBuffer);
		// Location  Size         Value
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(V), glm::value_ptr(value));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

private:
	::uint32_t mOpenGLUniformBuffer;
};

