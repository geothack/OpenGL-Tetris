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

	void Free(const int handle)
	{
		for (auto it = mEntityCache.begin(); it != mEntityCache.end(); )
		{
			if ((*it)->GetEntityCacheHandle() == handle)
			{	             
				it = mEntityCache.erase(it); 
				//delete* it;
			}
			else
			{
				it++; 
			}
		}
	}

	void Free();

private:
	inline static EntityRuntimeCache* mEntityRuntimeCache = nullptr;

	std::vector<Entity*> mEntityCache;

};

