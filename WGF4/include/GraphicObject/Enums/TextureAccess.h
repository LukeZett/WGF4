#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum TextureAccess
	{
		ReadOnly = WGPUStorageTextureAccess_WriteOnly,
		WriteOnly = WGPUStorageTextureAccess_ReadOnly,
		ReadWrite = WGPUStorageTextureAccess_ReadWrite,
	};
}