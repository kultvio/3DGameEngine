#include <window.h>
#include "application.h"

namespace GameEngine
{
	GameEngine::Application::Application()
	{

		
	}
	Application::~Application()
	{
	}
	int Application::start()
	{
		GameEngine::Window& window = GameEngine::Window::getInstanse();
		while (!glfwWindowShouldClose(window.getGLFWwindow()))
		{
			window.onUpdate();
		}
		return 0;
	}
}