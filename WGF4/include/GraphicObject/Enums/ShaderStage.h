#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum ShaderStage
	{
		Vertex = WGPUShaderStage_Vertex,
		Fragment = WGPUShaderStage_Fragment,
		Compute = WGPUShaderStage_Compute,
		NoneStage = WGPUShaderStage_None,
		VertFrag = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment,
		VertComp = WGPUShaderStage_Vertex | WGPUShaderStage_Compute,
		FragComp = WGPUShaderStage_Fragment | WGPUShaderStage_Compute,
		All = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment | WGPUShaderStage_Compute,
	};
}