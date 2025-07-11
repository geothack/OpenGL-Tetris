#pragma once

#include "WorldTypes/Scene.h"
#include "Utility/Verify.h"

class Entity
{
public:
	Entity() = default;

	Entity(const Entity& other) = default;

	Entity(::entt::entity entity, Scene& scene);

	virtual ~Entity() {};

	virtual void BeginPlay() {};

	virtual void Update() {};

	template<typename T>
	bool HasComponent()
	{
		return mScene->GetRegister().any_of<T>(mHandle);
	}

	template<typename T, typename ... Args>
	T* AddComponent(Args&& ... args)
	{
		if (HasComponent<T>())
		{
			Verify::Update("Entity already has component", 0);
		}
		return &mScene->GetRegister().emplace<T>(mHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T* GetComponent()
	{
		if (!HasComponent<T>())
		{
			Verify::Update("Entity does not have component", 0);
		}

		return &mScene->GetRegister().get<T>(mHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		if (!HasComponent<T>())
		{
			Verify::Update("Entity does not have component", 0);
		}

		mScene->GetRegister().erase<T>(mHandle);
	}

	Transform* GetWorldTransform() 
	{ 
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		return GetComponent<Transform>(); 
	}

	inline const ::entt::handle GetHandle() { return mHandle; }

private:
	::entt::handle mHandle;
	Scene* mScene;
};

