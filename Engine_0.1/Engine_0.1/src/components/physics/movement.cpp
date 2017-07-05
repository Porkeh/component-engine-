#include <components\physics\movement.h>
#include <components\Input.h>

void Movement::Update(float deltaT, Renderer * Renderer)
{
	if (transform != nullptr)
	{
		glm::vec3 move = moveDir * speed * deltaT;
		move += transform->getPosition();
		transform->SetPosition(move);
	}
	moveDir = glm::vec3(0, 0, 0);
}
void Movement::Initialize()
{
	moveDir = glm::vec3(0, 0, 0);
	speed = 1.0f;
}
void Movement::Render(Renderer * renderer)
{

}
Movement::Movement()
{
	transform = nullptr;
}
Movement::Movement(Transform * trans)
{
	transform = trans;
}
void Movement::setMoveDir()
{
	if (Input::isKeyPressed(GLFW_KEY_W))
	{
		moveDir.z = -1;
	}
	if (Input::isKeyPressed(GLFW_KEY_A))
	{
		moveDir.x = -1;
	}
	if (Input::isKeyPressed(GLFW_KEY_D))
	{
		moveDir.x = 1;
	}
	if (Input::isKeyPressed(GLFW_KEY_S))
	{
		moveDir.z = 1;
	}


}
void Movement::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}