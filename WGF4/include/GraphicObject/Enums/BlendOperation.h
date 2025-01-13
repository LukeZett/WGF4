#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
    enum BlendOperation
    {
        Add = WGPUBlendOperation_Add,
        Subtract = WGPUBlendOperation_Subtract,
        ReverseSubtract = WGPUBlendOperation_ReverseSubtract,
        Min = WGPUBlendOperation_Min,
        Max = WGPUBlendOperation_Max,
    };
}

