#pragma once


class EntityRuntimeCache
{
public:
	static EntityRuntimeCache* Get();

	template<class T>
	void Add(T& object)
	{
		Entity* entityBase = &object;
		mEntityCache.emplace_back(entityBase);
	}

	void AddEntity(Entity& entity)
	{
		mEntityCache.emplace_back(&entity);
	}

	void Update();

	void Free(const int handle);

	void Free();

private:
	inline static EntityRuntimeCache* mEntityRuntimeCache = nullptr;

	std::vector<Entity*> mEntityCache;

};

