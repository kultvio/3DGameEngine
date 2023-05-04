#pragma once
#include "event.h"
namespace GameEngine
{
	class KeyPressedEvent : public Event
	{
	private:
		int button;
	public:
		KeyPressedEvent(int button)
			:
			Event("Key Pressed Event", EventType::KEY_PRESSED_EVENT),
			button((button)) {}
	public:
		std::string format() const override
		{
			std::string formatted = name + ": " + (char)button + " pressed";
			return formatted;
		}
	};
	class KeyReleasedEvent : public Event
	{
	private:
		int button;
	public:
		KeyReleasedEvent(int button)
			:
			Event("Key Pressed Event", EventType::KEY_RELEASED_EVENT),
			button((button)) {}
	public:
		std::string format() const override
		{
			std::string formatted = name + ": " + (char)button + " released";
			return formatted;
		}
	};
}