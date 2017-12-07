#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

class Framebuffer
{
public:
	unsigned int fbo, rbo, colorBuffer[2];
	/* Default constructor */
	Framebuffer();
	/* De-constructor */
	~Framebuffer();
	/* Create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values) */
	void createSceneFramebuffer(unsigned int & width, unsigned int & height);
	/* Create cloud framebuffer with 2 color buffers */
	void createCloudFramebuffer(unsigned int & width, unsigned int & height);
	/* Create two ping-pong-framebuffers for blurring */
	static void createPingPongFramebuffer(Framebuffer framebuffer[2], unsigned int & width, unsigned int & height);
	/* Bind this framebuffer */
	void bind();
	void bindRBO();
	/* Unbind the current bound framebuffer */
	void unbind();
	/* Delete this framebuffer */
	void remove();
};

