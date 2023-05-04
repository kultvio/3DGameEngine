#pragma once
#include "event.h"



namespace GameEngine
{
	class MouseMovedEvent : public Event
	{
	private:
		int x, y;
	public:
		MouseMovedEvent(int x, int y)
			:
			Event("Mouse moved Event", Event::EventType::MOUSE_MOVED_EVENT),
			x(x),
			y(y) {}
	public:
		std::string format() const override
		{
			std::string formatted = name + ": " + std::to_string(x) + ", " + std::to_string(y);
			return formatted;
		}
	};



	class MouseScrolledEvent : public Event
	{
	private:
		int offset;
	public:
		MouseScrolledEvent(int offset)
			:
			Event("Mouse Scrolled Event", Event::EventType::MOUSE_SCROLLED_EVENT),
			offset(offset) {}
	public:
		std::string format() const override
		{
			std::string formatted = "";
			return (offset < 0) ? formatted = name + ": " + "to bottom" : formatted = name + ": " + "to top";
		}
	};

	class MouseButtonPressedEvent : public Event
	{
	private:
		int button;
	public:
		MouseButtonPressedEvent(int button)
			:
			Event("Mouse Button Pressed Event", Event::EventType::MOUSE_BUTTON_PRESSED_EVENT),
			button(button) {}
	public:
		std::string format() const override
		{
			std::string formatted = "";
			return (button == GLFW_MOUSE_BUTTON_LEFT) ? formatted = name + ": " + "left button pressed" : formatted = name + ": " + "right button pressed";
		}

	};
	class MouseBttunReleasedEvent : public Event
	{
	private:
		int button;
	public:
		MouseBttunReleasedEvent(int button)
			:
			Event("Mouse Button Releasd Event", Event::EventType::MOUSE_BUTTON_RELEASED_EVENT),
			button(button) {}
	public:
		std::string format() const override
		{
			std::string formatted = "";
			return (button == GLFW_MOUSE_BUTTON_LEFT) ? formatted = name + ": " + "left button released" : formatted = name + ": " + "right button released";
		}
	};

}