#include <game.h>
#include <iostream>
#include <components\Input.h>

const float REFRESH_RATE = 1 / 60;


void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	
	Input::processKeyPress(key, scancode, action, mods);

}

Game::Game(Window * window)
{

	glfwSwapInterval(false);
	Game::window = window;
	::glfwSetKeyCallback(Game::window->GetWindow(), Game::key_callback);
	int xSize, ySize;
	glfwGetWindowSize(Game::window->GetWindow(), &xSize, &ySize);
	glfwSetCursorPos(Game::window->GetWindow(), xSize / 2, ySize / 2);
	glfwGetCursorPos(Game::window->GetWindow(), &lastCursorPositionX, &lastCursorPositionY);


	renderer = new Renderer();
	player = new GameObject();
	
	player->AddComponent(new Mesh("./cube.obj"));
	player->AddComponent(new Texture("./texture.bmp"));
	player->AddComponent(new Transform(glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 0, 0)));
	player->AddComponent(new Movement(player->GetComponentByType<Transform>()));
	player->AddComponent(new QuatCamera(player->GetComponentByType<Transform>()));
	player->AddComponent(new Shader(0));
	components.push_back(player);
	GameObject * temp = nullptr;
	temp = new GameObject();
	temp->AddComponent(new Mesh("./cube.obj"));
	temp->AddComponent(new Texture("./uvtemplate.bmp"));
	temp->AddComponent(new Transform(glm::vec3(5, 0, 5), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0)));
	temp->AddComponent(new Shader(0));
	components.push_back(temp);

	temp = new GameObject();
	temp->AddComponent(new Mesh("./cube.obj"));
	temp->AddComponent(new Texture("./uvtemplate.bmp"));
	temp->AddComponent(new Transform(glm::vec3(-5, 0, 5), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0)));
	temp->AddComponent(new Shader(0));
	components.push_back(temp);

	temp = new GameObject();
	temp->AddComponent(new Mesh("./cube.obj"));
	temp->AddComponent(new Texture("./uvtemplate.bmp"));
	temp->AddComponent(new Transform(glm::vec3(-5, 0, -5), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0)));
	temp->AddComponent(new Shader(0));
	components.push_back(temp);

	temp = new GameObject();
	temp->AddComponent(new Mesh("./cube.obj"));
	temp->AddComponent(new Texture("./texture.bmp"));
	temp->AddComponent(new Transform(glm::vec3(0,5,0),glm::vec3(10,10,10),glm::vec3(0,0,0)));
	temp->AddComponent(new Shader(0));
	components.push_back(temp);
   

	temp = new GameObject();
	temp->AddComponent(new Mesh("./cube.obj"));
	temp->AddComponent(new Texture("./uvtemplate.bmp"));
	temp->AddComponent(new Transform());
	temp->AddComponent(new GUIRenderer());
	temp->AddComponent(new Shader(0));

	guiObjects.push_back(temp);
	//components.push_back(temp);
   //

	//temp = new GameObject();
	//temp->AddComponent(new QuatCamera());
	//components.push_back(temp);
	
	for (auto c : components)
	{
		c->Initialize();
	}
	for (auto c : guiObjects)
	{
		c->Initialize();
	}
	
}
void Game::HandleInput(float dX, float dY)
{

	player->GetComponentByType<Movement>()->setMoveDir();
	player->GetComponentByType<QuatCamera>()->setYawxPitch(-dX,-dY);
	
}
Game::~Game()
{
	for (int i=0; i<components.size(); i++)
	{
		delete components[i];
	}
}

GameObject * Game::getPlayer()
{
	return player;
}
int nbFrames = 0;
void Game::loop()
{
	float currentTime = glfwGetTime();
	float frameTime = glfwGetTime();
	// Measure speed
	
	

	

	while (!glfwWindowShouldClose(window->GetWindow()) && !glfwGetKey(window->GetWindow(), GLFW_KEY_ESCAPE)) {
		//GLUtils::checkForOpenGLError(__FILE__,__LINE__);
		nbFrames++;


		float elapsedFrameTime = glfwGetTime() - frameTime;
		if (elapsedFrameTime >= 1.0) {
			std::cout << nbFrames << std::endl;
			nbFrames = 0;
			frameTime = glfwGetTime();


		}

		gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
		//Get the current cursor position
		glfwGetCursorPos(window->GetWindow(), &cursorPositionX, &cursorPositionY);

		//See how much the cursor has moved
		float deltaX = (float)(lastCursorPositionX - cursorPositionX);
		float deltaY = (float)(lastCursorPositionY - cursorPositionY);
		float elapsedTime = glfwGetTime() - currentTime;
		if (elapsedTime > REFRESH_RATE)
		{
			
			HandleInput(deltaX,deltaY);
			renderer->Update(elapsedTime, components);
			currentTime = glfwGetTime();
			int xSize, ySize;
			glfwGetWindowSize(Game::window->GetWindow(), &xSize, &ySize);
			glfwSetCursorPos(Game::window->GetWindow(), xSize / 2, ySize / 2);
			glfwGetCursorPos(window->GetWindow(), &lastCursorPositionX, &lastCursorPositionY);
			
		}
		renderer->Render(components);
		renderer->Render(guiObjects);
		glfwSwapBuffers(window->GetWindow());
		glfwPollEvents();
	
	}
}