#pragma once
#include <cstdint>


namespace WGF
{
	class Tracker
	{
	public:
		Tracker() = default;


		template<typename T>
		static void AddResource(size_t allocationSize, uint64_t id)
		{
		}

		template<typename T>
		static void RemoveResource(uint64_t id)
		{
		}

		~Tracker() = default;

	private:

	};
}
