#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum CompareFunction
	{
		Never = WGPUCompareFunction_Never,
		Less = WGPUCompareFunction_Less,
		Equal = WGPUCompareFunction_Equal,
		LessEqual = WGPUCompareFunction_LessEqual,
		NotEqual = WGPUCompareFunction_NotEqual,
		Greater = WGPUCompareFunction_Greater,
		GreaterEqual = WGPUCompareFunction_GreaterEqual,
		Always = WGPUCompareFunction_Always,
		CmpUndefined = WGPUCompareFunction_Undefined,
	};

}