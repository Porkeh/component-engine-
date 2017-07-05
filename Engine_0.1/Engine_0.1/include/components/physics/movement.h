#pragma once
#include <components\component.h>
#include <components\physics\transform.h>
class Movement : public Component
{
private:
	Transform * transform;
	glm::vec3 moveDir;
	float speed;
public:
	void Update(float deltaT, Renderer * Renderer);
	void Initialize();
	void Render(Renderer * renderer);
	Movement();
	Movement(Transform * trans);
	void setMoveDir();
	void SetSpeed(float newSpeed);

};