#pragma once

#include <gl_core_4_3.hpp>
#include <glm\glm.hpp>
//#include <components\renderer\renderer.h>

class Renderer;

class Component
{
protected:
private:
public:
	virtual void Update(float deltaT, Renderer * Renderer) = 0;
	virtual void Initialize() = 0;
	virtual void Render(Renderer * renderer) = 0;
	

};