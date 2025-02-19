#pragma once
#include <AppWindow/Events.h>
#include <imgui.h>
#include <glm/glm.hpp>

namespace WGF::UI
{
	using UIvec2 = glm::vec2;
	using Color = glm::vec3;
	using ColorAlpha = glm::vec4;

	struct Margins
	{
		float left = 0.f;
		float right = 0.f;
		float top = 0.f;
		float bottom = 0.f;
	};

	class GUIElement
	{
	protected:
		Margins m_margins;

	public:
		virtual void OnFrame() = 0;
		
		virtual void OnResize(WGF::ResizeEvent& e) = 0;
		
		virtual ~GUIElement() {};
	};

	static ImVec2 assign(const UIvec2& vec)
	{
		return ImVec2(vec.x, vec.y);
	}

	static ImVec4 assign(const ColorAlpha& vec)
	{
		return ImVec4(vec.x, vec.y, vec.z, vec.w);
	}

	static ImVec4 assign(const Color& vec)
	{
		return ImVec4(vec.x, vec.y, vec.z, 1.f);
	}
}


