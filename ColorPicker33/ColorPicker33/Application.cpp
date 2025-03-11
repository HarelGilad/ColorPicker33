#include "Application.h"

bool Application::_active = true;
const ImVec2 Application::_windowSize = { 50, 50 };
ImGuiWindowFlags_ Application::_flags = (ImGuiWindowFlags_)(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
															ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | 
															ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse |
															ImGuiWindowFlags_NoNav);

void Application::update()
{
	ImGuiIO& io = ImGui::GetIO();
	const ImVec2 pos = ImVec2(io.MousePos.x - _windowSize.x, io.MousePos.y - _windowSize.y);
	ImGui::SetNextWindowPos(pos);

	ImGui::SetNextWindowSize(_windowSize);

	ImVec4 color = getColorAtCursor();
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = color;

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

ImVec4 Application::getColorAtCursor()
{
	ImVec4 color;
	COLORREF colorRef;
	POINT cursorPos;

	// Get cursor pos
	GetCursorPos(&cursorPos);

	// Get color at mouse pos
	HDC hdcScreen = GetDC(NULL);
	colorRef = GetPixel(hdcScreen, cursorPos.x, cursorPos.y);
	ReleaseDC(NULL, hdcScreen);

	// Convert into ImVec4
	color.x = (float)((colorRef & 0x00FF0000) >> 16) / 255.0f;
	color.y = (float)((colorRef & 0x0000FF00) >> 8) / 255.0f;
	color.z = (float)((colorRef & 0x000000FF)) / 255.0f;
	color.w = 1.0f;

	return color;
}
