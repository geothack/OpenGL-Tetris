#pragma once

#include "WorldTypes/Transform.h"
#include "Render/OpenGLSprite.h"
#include "Render/Material.h"

class Entity;

class Scene
{
public:
	Scene() = default;

	Entity CreateEntity(Transform& transform);
	Entity CreateSpriteEntity(Transform& transform, OpenGLSprite& sprite, Material& material);
	Entity CreateShaderSpriteEntity(Transform& transform, OpenGLSprite& sprite, OpenGLShader& shader);

	
	inline ::entt::registry* GetRegister() { return &mRegistry; }

private:
	::entt::registry mRegistry;

	friend class Entity;
};

