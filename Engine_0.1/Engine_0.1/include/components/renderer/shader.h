#pragma once
#include <components\component.h>
#include <components\renderer\renderer.h>

class Shader : public Component
{
private:
	int shaderID;
	GLuint shaderProgram;
public:
	Shader(int id);
	virtual void Update(float deltaT, Renderer * renderer);
	virtual void Initialize();
	void Render(Renderer * renderer);
	GLuint GetProgram();
	void SetUniform(char * name, GLuint data);
	void SetUniform(char * name, glm::mat4 data);
};