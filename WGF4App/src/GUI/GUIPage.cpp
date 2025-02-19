#include "GUI/GUIPage.h"

void WGF::UI::GUIPage::OnFrame()
{
	m_style.ApplyStyle();
	DrawInterface();
	m_style.RevertStyle();
}

void WGF::UI::GUIPage::OnResize(WGF::ResizeEvent& e)
{
	m_grid.OnResize(e);
}

void WGF::UI::GUIPage::DrawInterface()
{
	m_grid.OnFrame();
}
