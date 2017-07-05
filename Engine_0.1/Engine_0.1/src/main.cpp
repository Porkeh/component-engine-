
#include <window.h>
#include <game.h>
#include <gl_core_4_3.hpp>
Window * window;
Game * game;


int main()
{
	


	window = new Window();
	window->Initialize(800, 600);
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();
	if (!didLoad)
	{
		glfwTerminate();
	}
	gl::ClearColor(0.f, 1.f, 0.0f, 1.0f);
	gl::Enable(gl::DEPTH_TEST);
//	gl::DepthFunc(gl::LEQUAL);
	game = new Game(window);

	





	game->loop();

	return 0;
}