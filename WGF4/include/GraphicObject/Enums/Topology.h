#pragma once
#include <webgpu/webgpu.h>

namespace WGF
{
	enum Topology
	{
		TriangleList = WGPUPrimitiveTopology_TriangleList,
		TriangleStrip = WGPUPrimitiveTopology_TriangleStrip,
		LineList = WGPUPrimitiveTopology_LineList,
		LineStrip = WGPUPrimitiveTopology_LineStrip,
		PointList = WGPUPrimitiveTopology_PointList
	};
}
