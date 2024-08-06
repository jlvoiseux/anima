#pragma once

#include "Application.h"

class OpenGLApp : public Application
{
public:
	void initWindow() override;
	void initApi() override;
	void mainLoop() override;
	void cleanUp() override;

private:
	GLFWwindow* window;
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
};