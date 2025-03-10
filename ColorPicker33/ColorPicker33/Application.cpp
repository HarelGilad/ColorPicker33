#include "Application.h"

bool Application::_active = true;
const ImVec2 Application::_windowSize = { 50, 50 };
ImGuiWindowFlags_ Application::_flags = (ImGuiWindowFlags_)(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
															ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoMove |
															ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoDocking |
															ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav);

void Application::update()
{
	ImGuiIO& io = ImGui::GetIO();
	const ImVec2 pos = ImVec2(io.MousePos.x - _windowSize.x, io.MousePos.y - _windowSize.y);
	ImGui::SetNextWindowPos(pos);

	ImGui::SetNextWindowSize(_windowSize);

	ImGui::Begin(APP_NAME, &_active, _flags);
	ImGui::End();
}

bool Application::isActive()
{
	return _active;
}

void Application::shutdown()
{
	_active = false;
}
