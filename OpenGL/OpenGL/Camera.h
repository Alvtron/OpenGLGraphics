#pragma once

#include "Maths.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 5.0f;
const float SENSITIVTY = 0.1f;
const float FOV = 45.0f;

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

	// Camera Attributes
	vec3 Position;
	vec3 Front;
	vec3 Up;
	vec3 Right;
	const vec3 WORLD_UP = vec3(0.0f, 1.0f, 0.0f);

	// Eular Angles
	double Yaw;
	double Pitch;

	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Fov;

	// Constructor
	Camera(vec3 eye)
	{
		Position = eye;
		Front = vec3(0.0f, 0.0f, -1.0f);

		Yaw = YAW;
		Pitch = PITCH;

		MovementSpeed = SPEED;
		MouseSensitivity = SENSITIVTY;
		Fov = FOV;

		updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles
	mat4 GetViewMatrix()
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

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool sprint = false)
	{
		float velocity = (!sprint) ? MovementSpeed * deltaTime : MovementSpeed * deltaTime * 2;
		if (direction == FORWARD)
			Position = vec3::add(Position, vec3::scale(Front,velocity));
		if (direction == BACKWARD)
			Position = vec3::subtract(Position, vec3::scale(Front, velocity));
		if (direction == LEFT)
			Position = vec3::subtract(Position, vec3::scale(Right, velocity));
		if (direction == RIGHT)
			Position = vec3::add(Position, vec3::scale(Right, velocity));
	}
	// Same as previous ProcessKeyBoard method, but this locks camera to only be able to move in z and x directions. This is necessary for 
	// a more first person game control, only way to move in y direction is with space key jumping (method for that further down) 
	void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool sprint, bool flyingmode)
	{
		
		if (flyingmode)
		{
			ProcessKeyboard(direction, deltaTime, sprint);
		}
		else
		{

			float velocity = (!sprint) ? MovementSpeed * deltaTime : MovementSpeed * deltaTime * 2;
			if (direction == FORWARD)
				Position = vec3::add(Position, vec3::scale(vec3(Front.x, 0.0f, Front.z), velocity));
			if (direction == BACKWARD)
				Position = vec3::subtract(Position, vec3::scale(vec3(Front.x, 0.0f, Front.z), velocity));
			if (direction == LEFT)
				Position = vec3::subtract(Position, vec3::scale(Right, velocity));
			if (direction == RIGHT)
				Position = vec3::add(Position, vec3::scale(Right, velocity));
		}
	}

	//Processing movment for y direction
	void ProcessKeyboardJump(float deltaTime, float jumpStrength)
	{

		float velocity = jumpStrength * deltaTime;
		Position = vec3::add(Position, vec3(0.0f, velocity, 0.0f));
	}

	//Set position camera
	void SetCameraPosition(vec3 v)
	{
		Position = (v);
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(double xoffset, double yoffset)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		// Update Front, Right and Up Vectors using the updated Eular angles
		updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void setFOV(float yoffset)
	{
		if (Fov >= 1.0f && Fov <= 45.0f)
			Fov -= yoffset;
		if (Fov <= 1.0f)
			Fov = 1.0f;
		if (Fov >= 45.0f)
			Fov = 45.0f;
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors()
	{
		float y = (float)(Yaw * (M_PI / 180.0f));
		float p = (float)(Pitch * (M_PI / 180.0f));

		// Calculate the new Front vector
		vec3 front(cos(y) * cos(p), sin(p), sin(y) * cos(p));
		Front = vec3::normalize(front);

		// Also re-calculate the Right and Up vector
		Right = vec3::normalize(vec3::cross(Front, WORLD_UP));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = vec3::normalize(vec3::cross(Right, Front));
	}
};