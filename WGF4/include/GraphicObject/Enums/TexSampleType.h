#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum TexSampleType
	{
		Float = WGPUTextureSampleType_Float,
		UnfilterableFloat = WGPUTextureSampleType_UnfilterableFloat,
		Depth = WGPUTextureSampleType_Depth,
		Sint = WGPUTextureSampleType_Sint,
		Uint = WGPUTextureSampleType_Uint
	};
}