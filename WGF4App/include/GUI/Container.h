#pragma once
#include "GUIElement.h"
#include <glm/glm.hpp>
#include <imgui.h>
#include <string>
#include <functional>

namespace WGF::UI
{
	class Container : public GUIElement
	{
		std::string m_name;
		UIvec2 m_position;
		UIvec2 m_size;
		ImGuiWindowFlags m_flags;
		std::function<void(const std::string& name, const UIvec2& position, const UIvec2& size)> DrawElements = DrawEmpty;
	
	public:
		Container(const std::string& name, ImGuiWindowFlags flags = 0);

		static void DrawEmpty(const std::string& name, const UIvec2& position, const UIvec2& size);

		inline std::string& Name() { return m_name; }

		inline UIvec2& Position() { return m_position; }

		inline UIvec2& Size() { return m_size; }

		inline ImGuiWindowFlags& Flags() { return m_flags; }

		// Inherited via GUIElement
		void OnFrame() override;

		void OnResize(WGF::ResizeEvent& e) override;
	};
}
