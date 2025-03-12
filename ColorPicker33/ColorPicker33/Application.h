#ifndef APP_H
#define APP_H

#include "includes.h"
#include <string>

class Application
{
public:
	// Methods
	static void update();
	static void capture();

	static bool isActive();
	static void shutdown();

private:
	// Helper Methods
	static void saveColorAtPixel(const POINT& cursorPos);
	static std::string getColorHexValue();

	// Fields
	static bool _active;
	static const ImVec2 _windowSize;
	static ImGuiWindowFlags_ _flags;
	static ImVec4 _color;
};

#endif