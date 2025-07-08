#include "Verify.h"

void Verify::Update(std::string_view message, int value)
{
	if (value == 0)
	{
		auto trace = std::to_string(std::stacktrace::current());
		throw std::runtime_error(message.data() + trace);
	}
}
