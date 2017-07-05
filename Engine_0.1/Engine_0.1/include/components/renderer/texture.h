#pragma once
#include <components\component.h>

class Component;

class Texture : public Component
{
protected:
private:

	GLuint textureID;
	GLuint width, height;
	char * texPath;
	void LoadBMP();

public:
	void Update(float deltaT, Renderer * renderer);
	void Initialize();
	void Render(Renderer * renderer);
	GLuint getTexture();
	Texture(char * filePath);
	Texture() {}






};