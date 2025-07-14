#pragma once


class OpenGLTextRenderer : public Renderer
{
public:
	OpenGLTextRenderer() = default;
	OpenGLTextRenderer(Scene& scene);
	~OpenGLTextRenderer() override;

	void Update() override;

private:
	Scene* mScene;

};

