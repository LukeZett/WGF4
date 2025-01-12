#include "WGF4.h"

int main()
{
	auto limits = WGF::DeviceLimits();
	limits.SetTextureLimits(4096, 4096, 1, 1, 1);

	WGF::Initialize(limits, WGF::WindowParameters(720, 480, "Hello World"));

	WGF::ScreenPassFactory screenPassFactory;
	screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { 0.0f, 0.0f, 0.0f, 1.0f });


	float r = 0.0f;
	float g = 1.0f;

	while (!WGF::ShouldClose())
	{
		screenPassFactory.SetColorAttachment(0, WGF::Clear, WGF::Store, { r, g, 0.0f, 1.0f });
		r += 0.01f;
		g -= 0.01f;
		if (r >= 1.f)
		{
			std::swap(r, g);
		}


		auto pass = screenPassFactory.BeginPass();
		if (!pass.IsValid()) break;

		screenPassFactory.EndPass(pass);

		WGF::Window().PollEvents();
	}
	WGF::Finish();
}