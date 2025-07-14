#pragma once


class Helper
{
public:
	static Helper* Get();

	int GenerateRandomInt(const int bottomRange, const int topRange);

	void Free();

private:
	inline static Helper* mHelper = nullptr;
};

