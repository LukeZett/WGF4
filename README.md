# WGF4
Framework for developing webGPU graphic applications using modern C++. This framework supports (or will support in the immediate future):

 - Window creation using the glfw library (TODO: add support for SDL2)
 - Easy management of graphic API objects, such as textures, using the RAII idiom
 - User input handling

## Getting started	
 - clone the repository into the source tree ``` git clone https://github.com/LukeZett/WGF4.git ```
 - add directory in CMake and link library ``` add_subdirectory ("WGF4") ``` ``` target_link_libraries(target PRIVATE WGF4) ```
 - copy the wgpu library binaries next to the executable binary ``` TARGET_COPY_WEBGPU_BINARIES(target) ```

### Requirements
 - CMake (>= 3.8)
 - C++ compiler (C++ 20)
 - Tested on Windows

## Usage
The minimal running application that only displays a window with a clear color that changes over time
~~~C++
#include "WGF4.h"

int main()
{
	auto limits = WGF::DeviceLimits();
	limits.SetTextureLimits(4096, 4096, 1, 1, 1); // Set texture limits to 4096x4096 pixels, needed for the screen pass
	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World")); // Initialize WGF with a window of 720x480 pixels

	WGF::ScreenPassFactory screenPassFactory;
	screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { 0.0f, 0.0f, 0.0f, 1.0f }); // Set the color attachment to clear to black

	float t = 0.0f; // time parameter
	while (!WGF::ShouldClose())
	{
		float r = 0.5f + 0.5f * sin(t);
		float g = 0.5f + 0.5f * cos(t);
		float b = 0.5f + 0.5f * sin(t + 3.14159f / 2.0f);
		t += 0.01f;
		screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { r, g, b, 1.0f }); // Set the color attachment to clear to a color that changes over time
		auto pass = screenPassFactory.BeginPass(); // Begin the screen pass
		if (!pass.IsValid()) break; // If the pass is invalid, break the loop (this can happen if the surface fails to provide the texture view)

		screenPassFactory.EndPass(pass); // End the screen pass
		WGF::Window().PollEvents(); // Poll user input events (needed for closing the window and resizing with the F11 key)
	}
	WGF::Finish(); // Clean up WGF
}
~~~
[WiP]

