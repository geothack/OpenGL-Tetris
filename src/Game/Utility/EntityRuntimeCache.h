#pragma once


class EntityRuntimeCache
{
public:
	static EntityRuntimeCache* Get();

	void Add(Entity& entity)
	{
		mEntityCache.emplace_back(&entity);
	}

	void BeginPlay()
	{
		for (auto* entityBase : mEntityCache)
		{
			if (entityBase)
			{
				entityBase->BeginPlay();
			}
		}
	}

	void Update()
	{
		for (auto* entityBase : mEntityCache)
		{
			if (entityBase)
			{
				entityBase->Update();
			}
		}
	}

	void Free();

private:
	inline static EntityRuntimeCache* mEntityRuntimeCache = nullptr;

	std::vector<Entity*> mEntityCache;

};

