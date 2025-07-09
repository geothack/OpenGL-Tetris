#pragma once
#include "Utility/PreLibrary.h"

class Renderer
{
public:
	Renderer() = default;
	virtual ~Renderer() {};

	virtual void Update() = 0;
};

