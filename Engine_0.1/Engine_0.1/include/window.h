#pragma once

#include "gl_core_4_3.hpp"
#include "GLFW\glfw3.h"



class Window
{
private:
	GLFWwindow * window;

public:
	Window();
	~Window();
	void Initialize(int width, int height);
	void loop();
	GLFWwindow* GetWindow();

};
