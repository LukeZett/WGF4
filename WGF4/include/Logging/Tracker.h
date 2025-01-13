#pragma once
#include <cstdint>
#include <iostream>
#include "Logging/Logging.h"
#include <webgpu/webgpu.h>

namespace WGF
{
	class Tracker
	{
	public:
		Tracker() = default;


		template<typename T>
		static void AddResource(size_t allocationSize, uint64_t id)
		{
			std::cout << "Resource " << id << " added" << std::endl;
		}

		template<>
		static void AddResource<WGPUTexture>(size_t allocationSize, uint64_t id)
		{
			std::cout << "Texture " << id << " added" << std::endl;
		}

		template<>
		static void AddResource<WGPUTextureView>(size_t allocationSize, uint64_t id)
		{
			std::cout << "Texture View " << id << " added" << std::endl;
		}

		template<typename T>
		static void RemoveResource(uint64_t id)
		{
			std::cout << "Resource " << id << " removed" << std::endl;
		}

		template<>
		static void RemoveResource<WGPUTexture>(uint64_t id)
		{
			std::cout << "Texture " << id << " removed" << std::endl;
		}

		template<>
		static void RemoveResource<WGPUTextureView>(uint64_t id)
		{
			std::cout << "Texture View " << id << " removed" << std::endl;
		}

		~Tracker() = default;

	private:

	};
}
