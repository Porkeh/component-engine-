#define _USE_MATH_DEFINES
#include <cmath>


#include "components/QuatCamera.h"
#include <glm\gtc\matrix_transform.hpp>



//World coordinate System Axes
const glm::vec3 WORLDX = glm::vec3(1, 0, 0);
const glm::vec3 WORLDY = glm::vec3(0, 1, 0);
const glm::vec3 WORLDZ = glm::vec3(0, 0, 1);


/////////////////////////////////////////////////////////////////////////////////////////////
// Constructor
/////////////////////////////////////////////////////////////////////////////////////////////
QuatCamera::QuatCamera()
{
	_parent = nullptr;
}

QuatCamera::QuatCamera(Transform * parent)
{
	if (parent != nullptr)
	{
		_parent = parent;
	}
}

void QuatCamera::Initialize()
{
	reset();
}

/////////////////////////////////////////////////////////////////////
// Set the nearPlane and the farPlane
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::setNearAndFarPlanes(float nearPlane, float farPlane)
{
	assert(nearPlane > 0.0f);
	assert(farPlane > nearPlane);
	_nearPlane = nearPlane;
	_farPlane = farPlane;
}

///////////////////////////////////////////////////////////////////////////////////////////
// Generate a quaternion from axis and rotation angle in radians
//This is to construct the rotation quaternion
////////////////////////////////////////////////////////////////////////////////////////////

glm::quat fromAxisAngle(glm::vec3 axis, float angle)
{
	glm::quat rotation;

	/*TO DO */
	/*Need to return a Quaternion which will be used to change the camera orientation
	It will represent a rotation by 'angle' radians around the vector 'axis'
	*/
	//calculateion to get a quaternion based on the angle and the axis given
	rotation.w = glm::cos(angle / 2);
	rotation.x = glm::sin(angle / 2) * axis.x;
	rotation.y = glm::sin(angle / 2) * axis.y;
	rotation.z = glm::sin(angle / 2) * axis.z;
	rotation = glm::normalize(rotation); //normalise

	return rotation;

}

/////////////////////////////////////////////////////////////////////////////////////////////
//Rotate the camera
//Orient according to required pitch and yaw
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::rotate()
{


	/* TODO */
	/* Use method fromAxisAngle(...) to obtain a 'rotation' quaternion to rotate pitch around WORLDX
	then update camera orientation by multiplying rotation * _orientation.
	normalize the result.

	Then use method fromAxisAngle(...) to obtain a 'rotation' quaternion to rotate yaw around WORLDY
	then again update camera orientation by multiplying _orientation * rotation.
	Note the order of multiplication

	Lastly call updateView() to update the View matrix.
	*/
	//work out pitch rotation
	glm::quat rotation;
	rotation = fromAxisAngle(WORLDX, pitch);
	//set to orientation
	_orientation = rotation*_orientation;
	_orientation = glm::normalize(_orientation); //normalize
												 //work out yaw rotation
	rotation = fromAxisAngle(WORLDY, yaw);
	//set to orientation
	_orientation = _orientation*rotation;
	//normalize
	_orientation = glm::normalize(_orientation);

}


/////////////////////////////////////////////////////////////////////////////////////////////
// Pan the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::pan(const float x, const float y)
{

	_position += _xaxis * x;
	_position += _yaxis * -y;

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Zoom the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::zoom(const float z)
{

	_position += _zaxis * z;

	//Now call updateView()


}
void QuatCamera::setYawxPitch(float yaw, float pitch)
{
	QuatCamera::yaw = yaw;
	QuatCamera::pitch = pitch;
}
/////////////////////////////////////////////////////////////////////////////////////////////
// Update the camera view
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::Update(float deltaT, Renderer * renderer)
{
	yaw *= deltaT;
	pitch *= deltaT;

	rotate();
	//Construct the view matrix from orientation quaternion and position vector
	//rotate(0.1, 0);
	//First get the matrix from the 'orientaation' Quaternion
	//This deals with the rotation and scale part of the view matrix
	_view = glm::mat4_cast(_orientation); // Rotation and Scale
	glm::vec3 camPos;
	if (_parent != nullptr)
	{
		camPos =_position + _parent->getPosition();
	}
	else
	{
		camPos = _position;
	}
										  //Extract the camera coordinate axes from this matrix
	_xaxis = glm::vec3(_view[0][0], _view[1][0], _view[2][0]);
	_yaxis = glm::vec3(_view[0][1], _view[1][1], _view[2][1]);
	_zaxis = glm::vec3(_view[0][2], _view[1][2], _view[2][2]);

	//And use this and current camera position to set the translate part of the view matrix
	_view[3][0] = -glm::dot(_xaxis, camPos); //Translation x
	_view[3][1] = -glm::dot(_yaxis, camPos); //Translation y
	_view[3][2] = -glm::dot(_zaxis, camPos); //Translation z

	renderer->MessageGLm("view", _view);
	renderer->MessageGLm("projection", _projection);

}

/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the Up
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::roll(const float z)
{

	/* TO DO */
	/* The middle mouse button is set up to call this method
	in order to roll the camera around its z-axis
	This requires similar processing to the rotate(...) method above
	but, of course, should update the camera 'orientation' with
	a roll
	*/
	//work out the rotation on z axis
	glm::quat rotation = fromAxisAngle(WORLDZ, z);
	//set to orientation
	_orientation = _orientation*rotation;
	_orientation = glm::normalize(_orientation); //normalise

	
}


/////////////////////////////////////////////////////////////////////////////////////////////
// Reset the camera
/////////////////////////////////////////////////////////////////////////////////////////////
void QuatCamera::reset(void)
{
	//Initialise camera axes
	_xaxis = WORLDX;
	_yaxis = WORLDY;
	_zaxis = WORLDZ;

	//Initialise camera position 
	_position = glm::vec3(0.0f, 0.0f, 2.0f);

	//Initialise the orientation
	_orientation = glm::quat(1.0, 0.0, 0.0, 0.0);

	//Initialise camera perspective parameters
	_fieldOfView =50.0f;
	_nearPlane = 0.01f;
	_farPlane = 100.0f;
	_aspectRatio = 4.0f / 3.0f;

	_projection = glm::perspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane);

	
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera View matrix
/////////////////////////////////////////////////////////////////////////////////////////////
glm::mat4 QuatCamera::view()
{

	
	return _view;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// Return the camera Projection matrix
/////////////////////////////////////////////////////////////////////////////////////////////
glm::mat4 QuatCamera::projection()
{

	return _projection;

}

void QuatCamera::Render(Renderer * renderer)
{
	
}

