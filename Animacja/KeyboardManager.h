#pragma once
#include <GLFW\glfw3.h>
#include <map>
#include <functional>
//void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);


class KeyboardManager
{
	std::map<int, std::function<void()>> events;
public:
	bool keys[1024];

	KeyboardManager();
	~KeyboardManager();

	void RegisterKey(int key, std::function<void()> function)
	{
		events[key] = function;
	}

	void ProcessKeys()
	{
		for (auto const & event : events)
			if (keys[event.first])
				event.second();
	}
};

