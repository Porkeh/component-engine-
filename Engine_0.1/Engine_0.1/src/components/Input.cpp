#include <components\Input.h>


bool Input::allKeys[348];

void Input::processKeyPress(int key, int scancode, int action, int mods) {
	allKeys[key] = action != GLFW_RELEASE; // Sets keys position in array to be true if currently pressed. 
}

bool Input::isKeyPressed(int key) {
	return allKeys[key];
}

