#include "Player.h"
#include <iostream>
#include <sstream>

//Prototypes

/*

Collision detection code
Up:			0
Down:		1
Forward:	2
Back:		3
Left:		4
Right:		5

*/



//Algorithms that can be used (not in use now)
//http://www.codercorner.com/SAP.pdf
//http://www.peroxide.dk/papers/collision/collision.pdf

int up = 0;
int down = 1;
int forward = 2;
int back = 3;
int left = 4;
int right = 5;

bool collision_detected[6] = { 0,0,0,0,0,0 };
int numbofEntities = 0;

void Player::collision(vec3 player_position)
{

	for (int i = 0; i < 6; i++)
		collision_detected[i] = false;

	for (int i = 0; i < numberOfEntities; i++)
	{
		//Down
#if 1
		if ((position.y - hitbox.y - 0.1f) < entities[i].position.y &&
			(position.x + hitbox.x) < entities[i].hitbox.x * entities[i].scale.x * 0.5f &&
			(position.x - hitbox.x) > -entities[i].hitbox.x * entities[i].scale.x * 0.5f &&
			(position.z - hitbox.z) > -entities[i].hitbox.z * entities[i].scale.z * 0.5f &&
			(position.z + hitbox.z) < entities[i].hitbox.z * entities[i].scale.z * 0.5f) {

			collision_detected[down] = true;
		}

		//Forward
		if ((position.z + hitbox.z) > entities[i].position.z + (entities[i].hitbox.z * entities[i].scale.z - entities[i].scale.z * 2 + 1.0f) &&
			(position.z + hitbox.z) < entities[i].position.z + (entities[i].hitbox.z * entities[i].scale.z) &&
			(position.y - hitbox.y) < entities[i].position.y + (entities[i].hitbox.y * entities[i].scale.y - 0.1f) &&
			(position.x - hitbox.x) < entities[i].position.x + (entities[i].hitbox.x * entities[i].scale.x - 1.0f) &&
			(position.x + hitbox.x) > entities[i].position.x + (entities[i].hitbox.x * entities[i].scale.x - entities[i].scale.x * 2 + 1.0f)
			)
		{

			collision_detected[forward] = true;
		}
#endif
		//Right is the same as forward

		/*
		if ((position.z + hitbox.z) > entities[i].position.z + (entities[i].hitbox.z * entities[i].scale.z - entities[i].scale.z * 2 + 1.0f) &&
		(position.z + hitbox.z) < entities[i].position.z + (entities[i].hitbox.z * entities[i].scale.z) &&
		(position.y - hitbox.y) < entities[i].position.y + (entities[i].hitbox.y * entities[i].scale.y - 0.1f) &&
		(position.x - hitbox.x) < entities[i].position.x + (entities[i].hitbox.x * entities[i].scale.x - 1.0f) &&
		(position.x + hitbox.x) > entities[i].position.x + (entities[i].hitbox.x * entities[i].scale.x - entities[i].scale.x * 2 + 1.0f)
		)
		{
		collision_detected[right] = true;
		}
		*/

	}

	return;


}

Player::Player()
{

}

std::string Player::consolePlayerPosition()
{

	std::ostringstream oss;

	oss << "Player x: " << position.x << " y: " << position.y << " z: " << position.z;

	return oss.str();

}

std::string Player::consolePlayerCollision()
{
	std::ostringstream oss;

	oss << "Collision detected: ";

	if (collision_detected[down])
		oss << "Down, ";

	if (collision_detected[forward])
		oss << "Forward ";

	if (collision_detected[right])
		oss << "Right ";

	return oss.str();
}

std::string Player::consoleOtherTings()
{
	std::ostringstream oss;

	oss << "Log: ";

	return oss.str();
}

void Player::addCollidableEntity(Entity ent)
{

	entities[numbofEntities] = ent;
	numbofEntities++;
}



void Player::processInput(GLFWwindow *window, float deltaTime, bool flyingmode)
{

	/*

	Quadtrær
	Octrær
	BSP

	*/


	//Check collision under player test
	/*
	if ((position.y - hitbox.y) < entity.position.y &&
	(position.x + hitbox.x) < entity.hitbox.x * entity.scale.x * 0.5f &&
	(position.x - hitbox.x) > -entity.hitbox.x * entity.scale.x * 0.5f&&
	(position.z - hitbox.z) > -entity.hitbox.z * entity.scale.z * 0.5f&&
	(position.z + hitbox.z) < entity.hitbox.z * entity.scale.z * 0.5f)
	{
	collisionDetected = true;
	}
	else
	{
	collisionDetected = false;
	}
	*/

	collision(vec3(0, 0, 0));

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !collision_detected[forward])
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime, true, flyingmode);
		else
			camera.ProcessKeyboard(FORWARD, deltaTime,false, flyingmode);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime, true, flyingmode);
		else
			camera.ProcessKeyboard(BACKWARD, deltaTime,false, flyingmode);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime, true, flyingmode);
		else
			camera.ProcessKeyboard(LEFT, deltaTime,false, flyingmode);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime, true, flyingmode);
		else
			camera.ProcessKeyboard(RIGHT, deltaTime, false, flyingmode);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		isJumping = true;

	}

	if (!collision_detected[down]) {

		if(gravityPlayer < 100.0f)
			gravityPlayer = gravityPlayer + 0.1f;

		camera.ProcessKeyboardJump(deltaTime, -gravityPlayer);
	}
	else
	{
		gravityPlayer = 0;
	}


	//Jumping
	if (isJumping)
	{
		jumpStrength = jumpStrength - 0.1f;
		camera.ProcessKeyboardJump(deltaTime, jumpStrength);
	}

	if (collision_detected[down])
	{
		jumpStrength = 7.0f;
		isJumping = false;
	}

	/*
	if ((glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS && !((position.y - hitbox.y) < entity.position.y)))
	{
	camera.ProcessKeyboardJump(deltaTime, -jumpStrength);
	}
	*/


	position = camera.Position;

}