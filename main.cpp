#include "WGF4.h"

int main()
{
	auto limits = WGF::DeviceLimits();
	limits.SetTextureLimits(4096, 4096, 1, 1, 1); // Set texture limits to 4096x4096 pixels, needed for the screen pass

	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World")); // Initialize WGF with a window of 720x480 pixels

	WGF::ScreenPassFactory screenPassFactory;
	screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { 0.0f, 0.0f, 0.0f, 1.0f }); // Set the color attachment to clear to black
	WGF::Window().UseDepth();

	float t = 0.0f; // time parameter

	WGF::RenderPipeline pipeline = WGF::RenderPipelineBuilder()
		.AddScreenTarget(WGF::BlendState(), WGF::DepthStencilState())
		.Build();

	while (!WGF::ShouldClose())
	{
		float r = 0.5f + 0.5f * sin(t);
		float g = 0.5f + 0.5f * cos(t);
		float b = 0.5f + 0.5f * sin(t + 3.14159f / 2.0f);
		screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { r, g, b, 1.0f }); // Set the color attachment to clear to a color that changes over time
		
		t += 0.01f;

		auto pass = screenPassFactory.BeginPass(); // Begin the screen pass
		pass.BindPipeline(pipeline); // Bind the pipeline to the pass
		pass.Draw(3); // Draw a triangle

		if (!pass.IsValid()) break; // If the pass is invalid, break the loop (this can happen if the surface fails to provide the texture view)

		screenPassFactory.EndPass(pass); // End the screen pass

		WGF::Window().PollEvents(); // Poll user input events (needed for closing the window, and resizing with the F11 key)
	}
	WGF::Finish(); // Clean up WGF
}

/**
* WGF::RenderPipeline pipeline = builder
*	.SetShader(path, "vs_main", "fs_main")
*	.SetPrimitiveState(WGF::Topology::TriangleList, WGF::IndexFormat::Uint32, WGF::FrontFace::CCW, WGF::CullMode::None)
*	.SetBlendState(WGF::BlendOperation::Add, WGF::BlendFactor::SrcAlpha, WGF::BlendFactor::OneMinusSrcAlpha)
*	.SetDepthStencilState(WGF::CompareFunction::Less, true, true)
*	.SetMultisampleState(1, 0xFFFFFFFF, false)
*	...
*/
