#include <window.h>


Window::Window()
{
	;
}

Window::~Window()
{

}

void Window::Initialize(int width, int height)
{


	// Initialize GLFW
	glfwInit();

	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

	// Open the window
	
	window = glfwCreateWindow(width, height, "Robot Game", NULL, NULL);
	if (!window) {
		glfwTerminate();
		
	}
	glfwMakeContextCurrent(window);


	

}
GLFWwindow* Window::GetWindow()
{
	return window;
}
void Window::loop()
{


}