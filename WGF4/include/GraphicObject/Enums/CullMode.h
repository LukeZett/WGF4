#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum CullMode
	{
		None = WGPUCullMode_None,
		Front = WGPUCullMode_Front,
		Back = WGPUCullMode_Back
	};
}