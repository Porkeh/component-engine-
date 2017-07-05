#pragma once
#include <window.h>
#include <components\renderer\renderer.h>
#include <components\component.h>
#include <GameObject.h>



class Game
{
private:
	Window * window;
	Renderer * renderer;
	GameObject * player;
	vector<GameObject*> components;
	vector<GameObject*> guiObjects;
	double lastCursorPositionX, lastCursorPositionY, cursorPositionX, cursorPositionY;
public:
	Game() {}
	Game(Window * window);
	GameObject * getPlayer();
	void HandleInput(float dX, float dY);
	~Game();
	void loop();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};