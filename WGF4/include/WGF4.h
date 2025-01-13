#pragma once
#include "Framework/Instance.h"
#include "GraphicObject/Passes/ScreenPassFactory.h"
#include "GraphicObject/Passes/RenderPassFactory.h"
#include "GraphicObject/PipelineBuilder/RenderPipelineBuilder.h"

namespace WGF
{
	static bool Initialize(const DeviceLimits& limits, const WindowParameters& windowParameters)
	{
		return Framework::Get().Init(limits, windowParameters);
	}

	static void Finish()
	{
		Framework::Get().Finish();
	}

	static AppWindow& Window()
	{
		return *Framework::Get().Window();
	}

	static bool ShouldClose()
	{
		return Framework::Get().ShouldClose();
	}
};
