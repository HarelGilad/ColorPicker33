#include "Application.h"

bool Application::_active = true;
const ImVec2 Application::_windowSize = { 50, 50 };
ImGuiWindowFlags_ Application::_flags = (ImGuiWindowFlags_)(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
															ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | 
															ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoCollapse |
															ImGuiWindowFlags_NoNav);
ImVec4 Application::_color = { 0, 0, 0, 1 };

void Application::update()
{
	ImGuiIO& io = ImGui::GetIO();
	const ImVec2 pos = ImVec2(io.MousePos.x - _windowSize.x, io.MousePos.y - _windowSize.y);
	ImGui::SetNextWindowPos(pos);

	ImGui::SetNextWindowSize(_windowSize);

	saveColorAtCursor();
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = _color;

	ImGui::Begin(APP_NAME, &_active, _flags);
	ImGui::End();
}

void Application::capture()
{
	saveColorAtCursor();
	const std::string color = getColorHexValue();
	ImGui::SetClipboardText(color.c_str());
}

bool Application::isActive()
{
	return _active;
}

void Application::shutdown()
{
	_active = false;
}

void Application::saveColorAtCursor()
{
	COLORREF colorRef;
	POINT cursorPos;

	// Get cursor pos
	GetCursorPos(&cursorPos);

	// Get color at mouse pos
	HDC hdcScreen = GetDC(NULL);
	colorRef = GetPixel(hdcScreen, cursorPos.x, cursorPos.y);
	ReleaseDC(NULL, hdcScreen);

	// Convert into ImVec4
	_color.x = (float)(GetRValue(colorRef)) / 255.0f;
	_color.y = (float)(GetGValue(colorRef)) / 255.0f;
	_color.z = (float)(GetBValue(colorRef)) / 255.0f;
}

std::string Application::getColorHexValue()
{
	const size_t len = 8; // # + 3 hex values + null
	char hexColor[len];

	const int r = (int)(_color.x * 255);
	const int g = (int)(_color.y * 255);
	const int b = (int)(_color.z * 255);

	std::snprintf(hexColor, len, "#%02X%02X%02X", r, g, b);

	return std::string(hexColor);
}