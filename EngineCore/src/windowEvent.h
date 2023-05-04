#pragma once
#include "event.h"
namespace GameEngine
{
	class WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent()
			:
			Event("Window Closed Event", EventType::WINDOW_CLOSED_EVENT){}
	public:
		std::string format() const override
		{
			return name;
		}
	};
	class WindowResizedEvent : public Event
	{
	private:
		int width;
		int height;
	public:
		WindowResizedEvent(int width, int height)
			:
			Event("Window Resized Event", EventType::WINDOW_RESIZED_EVENT),
			width(width),
			height(height) {}
	public:
		std::string format() const override
		{
			return name + ": width: " + std::to_string(width) + " heigth: " + std::to_string(height);
		}
	};
}