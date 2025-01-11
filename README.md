# WGF4
Framework for developing webGPU graphic applications using modern C++. This framework supports (or will support in the immediate future):

 - Window creation using glfw library (TODO: add support for SDL2)
 - Easy management of graphic API objects, such as textures, using the RAII idiom
 - User input handling

The minimal running application that only displays a blank window:

~~~
#include "WGF4.h"

int main()
{
	auto limits = WGF::DeviceLimits();
	limits.SetTextureLimits(4096, 4096, 1, 1, 1); // these limits are needed for the initialization of screen buffer

	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World")); // initialize framework and window

	while (!WGF::ShouldClose()) //main loop
	{
		WGF::Window().PollEvents(); // process user input
	}
  WGF::Finish();
}
~~~
[WiP]

