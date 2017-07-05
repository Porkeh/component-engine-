#include <components\physics\transform.h>

Transform::Transform()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(500, 600, 1);
	rotation = glm::vec3(0, 0, 0);
}
Transform::Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
	Transform::position = position;
	Transform::scale = scale;
	Transform::rotation = rotation;
}

void Transform::Initialize()
{
	model = glm::mat4(1.0);
	
	MoveModel();
	
	
	//parent = glm::mat4(1.0);
}

void Transform::Update(float deltaT, Renderer * renderer)
{
	//model = glm::rotate(model, 2.0f, glm::vec3(1, 0, 0));
	//model = glm::rotate(model, 2.0f, glm::vec3(0, 1, 0));
	if (moved)
	{
		MoveModel();
		
	}
	renderer->MessageGLm("model", model);
	

}
void Transform::MoveModel()
{
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rotation.x, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rotation.x, glm::vec3(0, 0, 1));
	model = glm::scale(model, scale);
	moved = false;
}
glm::vec3 Transform::getPosition()
{
	return position;
}
glm::vec3 Transform::getScale()
{
	return scale;
}
glm::vec3 Transform::getRotation()
{
	return rotation;
}
glm::mat4 Transform::getModel()
{
	return model;

}
void Transform::SetPosition(glm::vec3 pos)
{
	position = pos;
	moved = true;
}
void Transform::Render(Renderer * renderer)
{

}