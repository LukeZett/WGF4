#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum TexViewDimension
	{
		V1D = WGPUTextureViewDimension_1D,
		V2D = WGPUTextureViewDimension_2D,
		V2DArray = WGPUTextureViewDimension_2DArray,
		Cube = WGPUTextureViewDimension_Cube,
		CubeArray = WGPUTextureViewDimension_CubeArray,
		V3D = WGPUTextureViewDimension_3D
	};

	enum TexDimension
	{
		_1D = WGPUTextureDimension_1D,
		_2D = WGPUTextureDimension_2D,
		_3D = WGPUTextureDimension_3D,
	};
}