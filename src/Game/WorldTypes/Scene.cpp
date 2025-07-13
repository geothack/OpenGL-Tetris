#include "Utility/PreLibrary.h"
#include "Scene.h"
#include "WorldTypes/Entity.h"

Entity Scene::CreateEntity(Transform& transform)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	return entity;
}

Entity Scene::CreateSpriteEntity(Transform& transform, OpenGLSprite& sprite, Material& material)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	entity.AddComponent<OpenGLSprite>(sprite);
	entity.AddComponent<Material>(material);
	return entity;
}

Entity Scene::CreateShaderSpriteEntity(Transform& transform, OpenGLSprite& sprite, OpenGLShader& shader)
{
	auto entity = Entity(mRegistry.create(), *this);
	entity.AddComponent<Transform>(transform);
	entity.AddComponent<OpenGLSprite>(sprite);
	entity.AddComponent<OpenGLShader>(shader);
	return entity;
}
