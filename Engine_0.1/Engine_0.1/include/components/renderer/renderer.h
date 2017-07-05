#pragma once

#include <components\component.h>
#include <components\renderer\mesh.h>
#include <components\renderer\shader.h>
#include <components\renderer\texture.h>
#include <components\physics\transform.h>
#include "components/QuatCamera.h"
#include <components\physics\movement.h>
#include <components\GUIRenderer.h>
#include <GameObject.h>
#include <vector>

class GameObject;

class Renderer 
{
protected:
	
private:
	GLuint indicesSize;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
public:
	void Update(float deltaT, vector<GameObject*> comp);
	void Initialize();
	void Render(vector<GameObject*> comp);
	void MessageGLi(char* msg, GLuint value);
	void MessageGLm(char* msg, glm::mat4 value);
	glm::mat4 GetModel();
	glm::mat4 GetView();
	glm::mat4 GetProjection();

	Renderer();
	 ~Renderer();
};
