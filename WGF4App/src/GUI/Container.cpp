#include "GUI/Container.h"

WGF::UI::Container::Container(const std::string& name, ImGuiWindowFlags flags)
	: m_name(name), m_flags(flags)
{
}

void WGF::UI::Container::DrawEmpty(const std::string& name, const UIvec2& position, const UIvec2& size)
{
	ImGui::Text("__This is an empty container__");
	ImGui::Text("Name: %s", name.c_str());
	ImGui::Text("Position: (%f, %f)", position.x, position.y);
	ImGui::Text("Size: (%f, %f)", size.x, size.y);
}

void WGF::UI::Container::OnFrame()
{
	if (!ImGui::Begin(Name().c_str(), 0, Flags()))
	{
		ImGui::End();
		return;
	}

	ImGui::SetWindowPos(assign(Position()));
	ImGui::SetWindowSize(assign(Size()));
	DrawElements(Name(), Position(), Size());
	ImGui::End();
}

void WGF::UI::Container::OnResize(WGF::ResizeEvent& e)
{
}
