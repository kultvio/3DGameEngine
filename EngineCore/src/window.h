#pragma once
#include<imgui/imgui.h>
#include <glad/glad.h>
#include<GLFW/glfw3.h>


#include <string>
#include <functional>
#include "event.h"
namespace GameEngine
{
	class Window final 
	{
	private:
		std::string name;
		int width, height;
		GLFWwindow* window = nullptr;
		std::function<void(Event&)> fnCallback;
		float m_background_color[4] = { 0.25f, 0.25f, 0.25f, 0.f };
	public:
		// удаляем copy конструкторы
		Window(const Window&) = delete;
		Window& operator = (const Window&) = delete;

	private:
		Window(const std::string& name, int width, int height);
		~Window();

	public:
		static Window& getInstanse() {
			static Window instanse("Window", 1280, 720);
			return instanse;
		}

		int init(const std::string& name, int width, int height);
		__forceinline GLFWwindow* getGLFWwindow() const { return window; }
		void setfnCallback(const std::function<void(Event&)>& fn) { fnCallback = fn; }
		void onUpdate();
	public:
		static void mouseMoveCallback(GLFWwindow* window, double x, double y);
		static void mouseScrolledCallback(GLFWwindow* window, double x, double y);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void windowCloseCallback(GLFWwindow* window);
		static void windowSizeCallback(GLFWwindow* window, int width, int height);
	};
}