#include "window.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "mouseEvent.h"
#include "keyEvent.h"
#include "windowEvent.h"
#include <iostream>
namespace GameEngine 
{
	Window::Window(const std::string& name, int width, int height)
	{
		init(name, width, height);
		setfnCallback([this](Event& e)
			{
				if (e.getType() == Event::EventType::WINDOW_CLOSED_EVENT)
				{
					glfwSetWindowShouldClose(window, GL_TRUE);
				}
				std::cout << e.format() << std::endl;
			});
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplOpenGL3_Init();
	}

	int Window::init(const std::string& name, int width, int height)
	{
		this->name = name;
		this->width = width;
		this->height = height;

		if (!glfwInit())
		{
			return -1;

		}
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
		window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

		if (!window)
		{
			return -2;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return -3;
		}

		glfwSetWindowUserPointer(window, this);
		glfwSetCursorPosCallback(window, mouseMoveCallback);
		glfwSetScrollCallback(window, mouseScrolledCallback);
		glfwSetMouseButtonCallback(window, mouseButtonCallback);
		glfwSetKeyCallback(window, keyCallback);
		glfwSetWindowCloseCallback(window, windowCloseCallback);
		glfwSetWindowSizeCallback(window, windowSizeCallback);

	}
	void Window::onUpdate()
	{
		glClearColor(1, 0, 0, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize.x = width;
		io.DisplaySize.y = height;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	void Window::mouseMoveCallback(GLFWwindow* window, double x, double y)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseMovedEvent e(x, y);
		handle.fnCallback(e);
	}
	void Window::mouseScrolledCallback(GLFWwindow* window, double x, double y)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent e(y);
		handle.fnCallback(e);
	}
	void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		
		if (action == GLFW_PRESS) { MouseButtonPressedEvent e(button); handle.fnCallback(e); }
		else { MouseBttunReleasedEvent e(button); handle.fnCallback(e);  }

	}
	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		if (action == GLFW_PRESS) { KeyPressedEvent e(key); handle.fnCallback(e); }
		else {
				KeyReleasedEvent e(key);
				handle.fnCallback(e);
		}
	}

	void Window::windowCloseCallback(GLFWwindow* window)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowClosedEvent e;
		handle.fnCallback(e);
	}
	void Window::windowSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto& handle = *(Window*)glfwGetWindowUserPointer(window);
		WindowResizedEvent e(width, height);
		handle.width = width;
		handle.height = height;
		handle.fnCallback(e);
	}

	Window::~Window()
	{
		glfwWindowShouldClose(window);
	}
}
