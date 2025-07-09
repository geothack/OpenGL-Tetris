#pragma once
class Renderer
{
public:
	Renderer() = default;
	virtual ~Renderer() {};

	virtual void Update() = 0;
};

