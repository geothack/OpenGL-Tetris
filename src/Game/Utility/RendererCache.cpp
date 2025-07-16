#include "Utility/PreLibrary.h"
#include "RendererCache.h"

RendererCache* RendererCache::Get()
{
	if (!mRendererCache)
	{
		mRendererCache = new RendererCache();
	}

	return mRendererCache;
}

void RendererCache::Update()
{
	for (auto* render : mRenderCache)
	{
		if (render)
		{
			render->Update();
		}
	}
}

void RendererCache::Free()
{
	delete mRendererCache;
}
