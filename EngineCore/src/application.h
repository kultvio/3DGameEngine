
#include <window.h>

namespace GameEngine
{
	class Application
	{
	public:
		Application();
		~Application();
	public:
		// ������� copy ������������
		Application(const Application&) = delete;
		Application& operator = (const Application&) = delete;
	public:
		int start();
	};
}