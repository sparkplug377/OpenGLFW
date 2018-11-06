/* ============================================================================================================================ */
/* OpenGL-Framework																												*/
/* Copyright (c) 2018 Ramkumar Thiyagarajan																						*/
/* ============================================================================================================================ */
/* Description:	Create an OpenGL window and render the sprites drawn on the screen. 											*/
/*				The scripts for the game should be added in this class.															*/
/* ============================================================================================================================ */

#include "Application2D.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

/* GLFW - Initialize */
Application2D::Application2D() : m_gameOver(false), m_window(nullptr)
{
	glfwInit();
}

/* GLFW - Window creation */
bool Application2D::createWindow(int width, int height, const char * title, bool fullscreen)
{
	m_window = glfwCreateWindow(width, height, title, (fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);
	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}
	// viewport matches the new window dimensions
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow*, int w, int h) {glViewport(0, 0, w, h); });
	// GLFW - Make the window's context current
	glfwMakeContextCurrent(m_window);

	// GLAD - load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}

	return true;
}

void Application2D::quit(GLFWwindow * window)
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		m_gameOver = true;
	}
	// set it true if the escape key or close button is pressed
	m_gameOver = m_gameOver || glfwWindowShouldClose(window) == true;
}



void Application2D::runApp(const char * title, int width, int height, bool fullscreen)
{
	// check if the window has been successfully created
	if (createWindow(width, height, title, fullscreen))
	{
		start();
		// GLFW - Loop until the user closes the window
		while (!m_gameOver)
		{
			// input from the user to close the window
			quit(m_window);

			// Render here
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// check for any keys or mouse movements
			glfwPollEvents();

			draw();

			// swap front and back buffers
			glfwSwapBuffers(m_window);

		}
	}
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Application2D::start()
{
	renderer2D = new Renderer2D();
}

void Application2D::draw()
{
	// clear the screen each frame before drawing
	clearScreen();
	// begin drawing by using the shader program
	renderer2D->begin();

	// draw here
	renderer2D->drawPoint(0.8f, 0.5f, 5.0f);
	renderer2D->drawPoint(0.1f, 0.6f, 2.0f);
}

void Application2D::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

Application2D::~Application2D()
{
}

