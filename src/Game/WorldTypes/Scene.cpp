#include "Utility/PreLibrary.h"
#include "Scene.h"
#include "WorldTypes/Entity.h"

Entity Scene::CreateEntity(Transform& transform)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	return entity;
}
