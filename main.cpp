#include "WGF4.h"

int main()
{
	auto limits = WGF::DeviceLimits();
	limits.SetTextureLimits(1, 4096, 1, 1, 1);

	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World"));

	while (!WGF::ShouldClose())
	{
		WGF::Window().PollEvents();
	}
	WGF::Finish();
}