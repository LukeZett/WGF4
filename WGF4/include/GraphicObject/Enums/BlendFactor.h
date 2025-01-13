#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum BlendFactor
	{
        Zero = WGPUBlendFactor_Zero,
        One = WGPUBlendFactor_One,
        Src = WGPUBlendFactor_Src,
        OneMinusSrc = WGPUBlendFactor_OneMinusSrc,
        SrcAlpha = WGPUBlendFactor_SrcAlpha,
        OneMinusSrcAlpha = WGPUBlendFactor_OneMinusSrcAlpha,
        Dst = WGPUBlendFactor_Dst,
        OneMinusDst = WGPUBlendFactor_OneMinusDst,
        DstAlpha = WGPUBlendFactor_DstAlpha,
        OneMinusDstAlpha = WGPUBlendFactor_OneMinusDstAlpha,
        SrcAlphaSaturated = WGPUBlendFactor_SrcAlphaSaturated,
        Constant = WGPUBlendFactor_Constant,
        OneMinusConstant = WGPUBlendFactor_OneMinusConstant,
	};
}

