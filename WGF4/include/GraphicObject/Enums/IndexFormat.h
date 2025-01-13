#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum IndexFormat
	{
		Undefined = WGPUIndexFormat_Undefined,
		Uint16 = WGPUIndexFormat_Uint16,
		Uint32 = WGPUIndexFormat_Uint32
	};
}