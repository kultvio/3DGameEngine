#include "window.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include <imgui/backends/imgui_impl_glfw.h>
#include "mouseEvent.h"
#include "keyEvent.h"
#include "windowEvent.h"
#include "Rendering/ShaderProgram.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexArray.h"
#include <iostream>
namespace GameEngine
{

	GLfloat points[] = {
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	const char* vertex_shader =
		"#version 460\n"
		"layout(location = 0) in vec3 vertex_position;"
		"layout(location = 1) in vec3 vertex_color;"
		"out vec3 color;"
		"void main() {"
		"   color = vertex_color;"
		"   gl_Position = vec4(vertex_position, 2.0);"
		"}";
	const char* fragment_shader =
		"#version 460\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

	std::unique_ptr<ShaderProgram> p_shader_program;
	std::unique_ptr<VertexBuffer> p_points_vbo;
	std::unique_ptr<VertexBuffer> p_colors_vbo;
	std::unique_ptr<VertexArray> p_vao;

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
		ImGui_ImplGlfw_InitForOpenGL(window, true);
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
		p_shader_program = std::make_unique<ShaderProgram>(vertex_shader, fragment_shader);
		if (!p_shader_program->isCompiled())
		{
			return false;
		}

		p_points_vbo = std::make_unique<VertexBuffer>(points, sizeof(points));
		p_colors_vbo = std::make_unique<VertexBuffer>(colors, sizeof(colors));
		p_vao = std::make_unique<VertexArray>();

		p_vao->add_buffer(*p_points_vbo);
		p_vao->add_buffer(*p_colors_vbo);

		return 0;

	}
	void Window::onUpdate()
	{
		glClearColor(1, 0, 0, 0);
		glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		p_shader_program->bind();
		p_vao->bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		

		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize.x = width;
		io.DisplaySize.y = height;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Background Color Window");
		ImGui::ColorEdit4("Background Color", m_background_color);
		ImGui::End();
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
		glViewport(0, 0, width, height);
		handle.fnCallback(e);
	}

	Window::~Window()
	{
		glfwWindowShouldClose(window);
	}
}
