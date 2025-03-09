#ifndef APP_H
#define APP_H

#include "includes.h"

class Application
{
public:
	static void update();

	static bool isActive();
	static void shutdown();

private:
	static bool _active;
};

#endif