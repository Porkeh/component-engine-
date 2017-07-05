#pragma once
#include <components\component.h>
#include <glm/gtc/matrix_transform.hpp>
#include <components\renderer\renderer.h>

class Transform : public Component
{
private:
	glm::mat4 model;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::vec3 position;

	bool moved;
	void MoveModel();
	//glm::mat4 parent;
public:
	void Update(float deltaT, Renderer * renderer);
	void Initialize();
	void Render(Renderer * renderer);
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::vec3 getRotation();
	glm::mat4 getModel();
	void SetPosition(glm::vec3 movement);
	Transform();
	Transform(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);

};

