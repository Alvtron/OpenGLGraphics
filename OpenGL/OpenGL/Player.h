#pragma once
#include "camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Text.h"

// 3D Object classes
#include "CubeMap.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Diamond.h"
#include "Texture.h"

#include <string>
#include <vector>
#include <time.h>

//Test klasser
#include "Player.h"
#include "Entity.h"


class Player {

public:
	int mass = 70;
	vec3 position;
	vec3 hitbox = vec3();
	bool isJumping = false;
	Player();
	Camera camera = Camera(vec3(0.0f, 2.0f, 2.0f));
	void processInput(GLFWwindow *window, float deltaTime, bool flyingmode);
	void collision(vec3 player_position);
	std::string consolePlayerPosition();
	std::string consolePlayerCollision();
	std::string consoleOtherTings();

	//Test variabel
	int numberOfEntities = 2;

	Entity entities[2];
	void addCollidableEntity(Entity entity);

private:
	float jumpStrength = 7.0f;
	float gravityPlayer = 0.0f;

};