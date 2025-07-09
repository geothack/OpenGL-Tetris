#pragma once

#include <stacktrace>
#include <print>
#include <stdexcept>
#include <string_view>

class Verify
{
public:
	static bool Update(std::string_view message, int value);

	template<typename T>
	static bool Update(std::string_view message, T* var)
	{
		if (!var)
		{
			auto trace = std::to_string(std::stacktrace::current());
			throw std::runtime_error(message.data() + trace);
		}
	}
};

