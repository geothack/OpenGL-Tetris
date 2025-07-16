#pragma once


class RendererCache
{
public:
	static RendererCache* Get();

	template<typename T>
	void Add(T& object,const int index)
	{
		Renderer* render = &object;
		mRenderCache[index] = render;
	}

	void Update();

	void Free();

private:
	inline static RendererCache* mRendererCache = nullptr;

	std::array<Renderer*, 2> mRenderCache;
};

