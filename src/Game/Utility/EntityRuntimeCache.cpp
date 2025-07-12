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

void EntityRuntimeCache::Free()
{
	mEntityCache.clear();
	delete mEntityRuntimeCache;
}
