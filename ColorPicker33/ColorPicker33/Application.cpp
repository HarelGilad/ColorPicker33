#include "Application.h"

bool Application::_active = true;

void Application::update()
{
}

bool Application::isActive()
{
	return _active;
}

void Application::shutdown()
{
	_active = false;
}
