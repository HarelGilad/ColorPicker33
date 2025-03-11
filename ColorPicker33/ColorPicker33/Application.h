#ifndef APP_H
#define APP_H

#include "includes.h"

class Application
{
public:
	// Methods
	static void update();

	static bool isActive();
	static void shutdown();

private:
	// Helper Methods
	static ImVec4 getColorAtCursor();

	// Fields
	static bool _active;
	static const ImVec2 _windowSize;
	static ImGuiWindowFlags_ _flags;
};

#endif