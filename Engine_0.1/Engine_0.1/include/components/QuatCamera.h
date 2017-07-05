#pragma once
#include "component.h"
#include <components\renderer\renderer.h>
#include <components\physics\transform.h>
#include<glm\gtc\quaternion.hpp>

class Transform;

class QuatCamera : public Component
{
public:

	QuatCamera();  //Constructor
	QuatCamera(Transform * parent);
	void setNearAndFarPlanes(float nearPlane, float farPlane); //nearPlane and farPLane setter method


	void rotate(); //Rotate camera
	void pan(const float x, const float y);  //Pan camera
	void roll(const float z); //Roll camera
	void zoom(const float z); //Zoom camera
	void setYawxPitch(float yaw, float pitch);


	void Update(float deltaT, Renderer * Renderer);
	void Initialize();
	void Render(Renderer * renderer);

	void reset(void); //Reset the camera

	glm::mat4 view(); //Get the View matrix
	glm::mat4 projection(); //Get the Projection matrix


private:

	float _fieldOfView;
	float _nearPlane;
	float _farPlane;
	float _aspectRatio;
	float yaw;
	float pitch;

	//The camera coordinate axes
	glm::vec3 _xaxis;
	glm::vec3 _yaxis;
	glm::vec3 _zaxis;

	//Camera position vector and Quaternoin to represent camera orientation
	glm::vec3 _position;
	glm::quat _orientation;

	glm::mat4 _view;
	glm::mat4 _projection;
	Transform * _parent;


};
