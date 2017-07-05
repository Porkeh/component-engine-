#pragma once 

#include "GLFW\glfw3.h"

class Input {
private:

	static bool allKeys[348]; // All possible keys, array should be big enough to fit all possibilities. GLFW goes to 348 but whatever.


public:
	static void processKeyPress(int key, int scancode, int action, int mods);
	static bool isKeyPressed(int key);
};

