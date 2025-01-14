#include "WGF4.h"

const char *shaderSource =
"@group(0) @binding(0) var<uniform> uColor: vec4f;                                    "
"@vertex																			  "
"fn vs_main(@builtin(vertex_index) in_vertex_index: u32) -> @builtin(position) vec4f {"
"	var p = vec2f(0.0, 0.0);														  "
"	if (in_vertex_index == 0u) {													  "
"		p = vec2f(-0.5, -0.5);														  "
"	}																				  "
"	else if (in_vertex_index == 1u) {												  "
"		p = vec2f(0.5, -0.5);														  "
"	}																				  "
"	else {																			  "
"		p = vec2f(0.0, 0.5);														  "
"	}																				  "
"	return vec4f(p, 0.0, 1.0);														  "
"}																					  "
"																					  "
"@fragment																			  "
"fn fs_main() -> @location(0) vec4f {												  "
"	return uColor;												                      "
"}																					  ";


int main()
{
	/// initialize WGF
	auto limits = WGF::DeviceLimits();
	limits
		.SetTextureLimits(4096, 4096, 1, 1, 1) // Set texture limits to 4096x4096 pixels, needed for the screen pass
		.SetBindGroupsLimits(1, 1, 96, 4) // Set bind group limits
		.SetVertexRequiredLimits(4, 4, 4096, 96);

	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World")); // Initialize WGF with a window of 720x480 pixels


	//define a screen pass
	WGF::ScreenPassFactory screenPassFactory;
	screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { 0.0f, 0.0f, 0.0f, 1.0f }); // Set the color attachment to clear to black
	WGF::Window().UseDepth();

	//define a render pipeline and its layout
	WGF::RenderPipelineBuilder builder;
	builder.AddScreenTarget(WGF::BlendState(), WGF::DepthStencilState())
		.SetShaderFromText(shaderSource, "vs_main", "fs_main")
		.AddBindGroupLayout().AddUniformBinding(0, WGF::Fragment, 4 * sizeof(float));

	WGF::RenderPipeline pipeline = builder.Build(); // Build the pipeline

	// define a single bind group that will be used by the pipeline
	glm::vec4 uTriangleColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f); // Triangle color
	WGF::Buffer<glm::vec4> buffer = WGF::Buffer<glm::vec4>(WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, 1); // Create a buffer with 4 floats
	WGF::BindGroup bindGroup = WGF::BindGroup(pipeline.GetBindGroupLayout(0));
	bindGroup.AddUniformBinding(0, buffer.Get(), 0, 4 * sizeof(float)); // Add the buffer to the bind group
	bindGroup.Init();

	float t = 0.0f; // time parameter
	while (!WGF::ShouldClose())
	{
		// update the colors
		float r = 0.5f + 0.5f * sin(t);
		float g = 0.5f + 0.5f * cos(t);
		float b = 0.5f + 0.5f * sin(t + 3.14159f / 2.0f);
		screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { r, g, b, 1.0f }); // Set the color attachment to clear to a color that changes over time
		
		uTriangleColor = glm::vec4(1.f-r, 1.f-g, 1.f-b, 1.0f); // Update the triangle color
		buffer.Write(&uTriangleColor, 1, 0); // Write the triangle color to the buffer

		// render pass
		auto pass = screenPassFactory.BeginPass(); // Begin the screen pass
		if (!pass.IsValid()) break; // If the pass is invalid, break the loop (this can happen if the surface fails to provide the texture view)
		
		pass.BindPipeline(pipeline); // Bind the pipeline to the pass
		pass.BindBindGroup(bindGroup, 0); // Bind the bind group to the pass
		pass.Draw(3); // Draw a triangle

		screenPassFactory.EndPass(pass); // End the screen pass

		// update
		WGF::Window().PollEvents(); // Poll user input events (needed for closing the window, and resizing with the F11 key)
		t += 0.01f;
	}
	WGF::Finish(); // Clean up WGF
}
