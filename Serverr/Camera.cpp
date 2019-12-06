#include "camera.h"


Camera::Camera()
{
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMovementSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, 1.0f);

	movementSpeed = startMovementSpeed;
	turnSpeed = startTurnSpeed;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	if (keys[GLFW_KEY_W])
	{
		position += front * movementSpeed * deltaTime;
	}


	if (keys[GLFW_KEY_S])
	{
		position -= front * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_A])
	{
		position -= right * movementSpeed * deltaTime;
	}

	if (keys[GLFW_KEY_D])
	{
		position += right * movementSpeed * deltaTime;
	}
}

void Camera::mouseControl(GLfloat changeX, GLfloat changeY)
{
	changeX = changeX * turnSpeed;
	changeY = changeY * turnSpeed;

	yaw += changeX;
	pitch += changeY;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	if (yaw > 360)
	{
		yaw = 0;
	}

	if (yaw < 0)
	{
		yaw = 360;
	}

	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCamPosition()
{
	return position;
}

glm::vec3 Camera::getCamDirection()
{
	return glm::normalize(front);
}

Camera::~Camera()
{
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));

}