#pragma once
#include <components\component.h>
#include <ModelReader.h>
#include <components\renderer\renderer.h>

class Mesh : public Component
{
private:
	GLuint vaoHandle;
	ModelReader * modelLoader;
public:
	void Update(float deltaT, Renderer * renderer);
	void Initialize();
	void LoadMeshFromOBJ(char * filePath);
	void Render(Renderer * renderer);
	GLuint GetVAO();
	GLuint GetIndicesSize();
	Mesh();
	Mesh(char * filePath);
};
