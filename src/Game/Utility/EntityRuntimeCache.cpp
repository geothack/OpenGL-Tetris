#include "Utility/PreLibrary.h"
#include "EntityRuntimeCache.h"

EntityRuntimeCache* EntityRuntimeCache::Get()
{
	if (!mEntityRuntimeCache)
	{
		mEntityRuntimeCache = new EntityRuntimeCache();
	}

	return mEntityRuntimeCache;
}

void EntityRuntimeCache::Update()
{
	for (auto* entityBase : mEntityCache)
	{
		if (!entityBase->HasRunBeginPlay)
		{
			entityBase->BeginPlay();
			entityBase->HasRunBeginPlay = true;
		}
		if (entityBase)
		{
			entityBase->Update();
		}
	}
}

void EntityRuntimeCache::Free(const int handle)
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

void EntityRuntimeCache::Free()
{
	mEntityCache.clear();
	delete mEntityRuntimeCache;
}
