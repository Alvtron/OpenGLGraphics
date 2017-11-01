/*

Created by Thomas Angeland, student at �stfold University College, Norway.

Based heavily on Joey de Vries' camera class from LearnOpenGL.com:
https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/camera.h (sourced 27.09.2017)

*/

#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <vector>
#include "maths.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVTY = 0.1f;
const float FOV = 50.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	
	// Eular Angles
	float Yaw; // Magnitude of looking left or right
	float Pitch; // Angle for looking up or down
	
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float fov;

	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), fov(FOV)
	{
		Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), fov(FOV)
	{
		Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

	/*
	
	// Returns the view matrix calculated using Eular Angles
	mat4 getViewMatrix()
	{
	vec3 Center(vec3::add(Position, Front));
	vec3 f(vec3::normalize(vec3::subtract(Center, Position)));
	vec3 s(vec3::normalize(vec3::cross(f, Up)));
	vec3 u(vec3::cross(s, f));

	mat4 result;

	result.matrix[0] = s.x;
	result.matrix[4] = s.y;
	result.matrix[8] = s.z;
	result.matrix[1] = u.x;
	result.matrix[5] = u.y;
	result.matrix[9] = u.z;
	result.matrix[2] = -f.x;
	result.matrix[6] = -f.y;
	result.matrix[10] = -f.z;
	result.matrix[12] = -vec3::dot(s, Position);
	result.matrix[13] = -vec3::dot(u, Position);
	result.matrix[14] = vec3::dot(f, Position);
	result.matrix[15] = 1.0f;

	return result;
	}
	
	*/

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Front * velocity;
		if (direction == BACKWARD)
			Position -= Front * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool sprint)
	{
		if (!sprint) ProcessKeyboard(direction, deltaTime);
		else
		{
			float velocity = MovementSpeed * deltaTime * 2;
			if (direction == FORWARD)
				Position += Front * velocity;
			if (direction == BACKWARD)
				Position -= Front * velocity;
			if (direction == LEFT)
				Position -= Right * velocity;
			if (direction == RIGHT)
				Position += Right * velocity;
		}
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (Pitch > 89.9f)
				Pitch = 89.9f;
			if (Pitch < -89.9f)
				Pitch = -89.9f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void setFOV(float yoffset)
	{
		if (fov >= 1.0f && fov <= 90.0f)
			fov -= yoffset;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 90.0f)
			fov = 90.0f;
	}

private:
	// Calculates the front vector from the Camera's Eular Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
};