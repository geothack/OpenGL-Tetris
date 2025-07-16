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
		return mScene->GetRegister()->any_of<T>(mHandle);
	}

	template<typename T, typename ... Args>
	T* AddComponent(Args&& ... args)
	{
		if (HasComponent<T>())
		{
			Verify::Update("Entity already has component", 0);
		}
		return &mScene->GetRegister()->emplace<T>(mHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T* GetComponent()
	{
		if (!HasComponent<T>())
		{
			Verify::Update("Entity does not have component", 0);
		}

		return &mScene->GetRegister()->get<T>(mHandle);
	}

	template<typename T>
	void RemoveComponent()
	{
		if (!HasComponent<T>())
		{
			Verify::Update("Entity does not have component", 0);
		}

		mScene->GetRegister()->erase<T>(mHandle);
	}

	Transform* GetEntityTransform() 
	{ 
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		return GetComponent<Transform>(); 
	}

	glm::vec2* GetEntityPosition()
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		return GetComponent<Transform>()->GetPosition();
	}

	void SetEntityPosition(const glm::vec2& position)
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		GetComponent<Transform>()->UpdatePosition(position);
	}

	float GetEntityRotation()
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		return GetComponent<Transform>()->GetRotation();
	}

	void SetEntityRotation(const float rotation)
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		GetComponent<Transform>()->UpdateRotation(rotation);
	}

	glm::vec2* GetEntitySize()
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		return GetComponent<Transform>()->GetSize();
	}

	void SetEntitySize(const glm::vec2& size)
	{
		if (!HasComponent<Transform>())
		{
			Verify::Update("Entity does not have transform component", 0);
		}

		GetComponent<Transform>()->UpdateSize(size);
	}

	//inline const ::entt::entity GetHandle() { return mHandle; }

	inline const int GetEntityCacheHandle() { return mEntityCacheHandle; }

	bool HasRunBeginPlay = false;

private:
	::entt::entity mHandle;
	Scene* mScene;

	inline static int mCacheHandle = 0;
	int mEntityCacheHandle;

};

