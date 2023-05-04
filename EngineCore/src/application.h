
#include <window.h>

namespace GameEngine
{
	class Application
	{
	public:
		Application();
		~Application();
	public:
		// удаляем copy конструкторы
		Application(const Application&) = delete;
		Application& operator = (const Application&) = delete;
	public:
		int start();
	};
}