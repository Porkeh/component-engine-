#pragma once
#include <components\component.h>
#include <components\renderer\renderer.h>


class GUIRenderer : public Component
{
private:
	glm::mat4 view;
	glm::mat4 proj;
public:
	void Update(float deltaT, Renderer * Renderer);
	void Initialize();
	void Render(Renderer * renderer);
	GUIRenderer();

};
