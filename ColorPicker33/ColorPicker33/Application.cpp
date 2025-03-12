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
	POINT cursorPos;
	// Get cursor position

	GetCursorPos(&cursorPos);

	// Set window position next to cursor
	const ImVec2 pos = ImVec2(cursorPos.x - _windowSize.x, cursorPos.y - _windowSize.y);
	ImGui::SetNextWindowPos(pos);

	// Set window size (fixed size)
	ImGui::SetNextWindowSize(_windowSize);

	// Get color at current position on screen & set it as the background
	saveColorAtPixel(cursorPos);
	ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = _color;

	// Draw the window
	ImGui::Begin(APP_NAME, &_active, _flags);
	ImGui::End();
}

void Application::capture()
{
	POINT cursorPos;

	// Get cursor position
	GetCursorPos(&cursorPos);

	// Save color
	saveColorAtPixel(cursorPos);

	// Copy to clipboard as hex
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

void Application::saveColorAtPixel(const POINT& cursorPos)
{
	HDC hdcScreen;
	COLORREF colorRef;

	// Get color at mouse pos
	hdcScreen = GetDC(NULL);
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