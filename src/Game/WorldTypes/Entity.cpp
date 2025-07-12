#include "Utility/PreLibrary.h"
#include "Entity.h"

Entity::Entity(::entt::entity entity, Scene& scene) : mScene(&scene), mHandle(entity)
{
}
