#include "Utility/PreLibrary.h"
#include "Helper.h"

Helper* Helper::Get()
{
	if (!mHelper)
	{
		mHelper = new Helper();
	}

	return mHelper;
}

int Helper::GenerateRandomInt(const int bottomRange, const int topRange)
{
	std::random_device rd;
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(bottomRange, topRange);
	return distrib(gen);
}

void Helper::Free()
{
	delete mHelper;
}
