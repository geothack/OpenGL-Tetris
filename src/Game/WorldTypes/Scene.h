#pragma once

#include "WorldTypes/Transform.h"

class Entity;

class Scene
{
public:
	Scene() = default;

	Entity* CreateEntity(Transform& transform);

	
	inline ::entt::registry& GetRegister() { return mRegistry; }

private:
	::entt::registry mRegistry;

	friend class Entity;
};

