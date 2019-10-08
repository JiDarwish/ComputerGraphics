#include <iostream>
#include "tucano/tucano.hpp"
#include "widget.hpp"
#include "GLFW/glfw3.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

/// note that we use pointers for the global variables because we need to call the constructor only some other initialization is done
/// widget can only be initialized after GLEW, for example

/// A pointer to the widget 
Widget* widget;
/// A pointer to our main window
GLFWwindow* main_window;

/**
 * @brief initialization
 * Initialize glew and the widget
 */
void initializeTucano (void)
{
    Tucano::Misc::initGlew();
	widget = new Widget();
	widget->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);
    widget->openMeshFile("../resources/models/bunny.ply");
}

/**
 * @brief callback for keyboard input
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
}

/**
 * @brief initialize GLFW
 * Initialize Glfw and create a new window to hold our widget
 */
int initializeGlfw (void)
{
	if (!glfwInit())
	{
    	std::cerr << "Failed to init glfw" << std::endl;
    	return -1;
	}
	
	// do not allow resizing
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	main_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Transformation Exercises", NULL, NULL);
	if (!main_window)
	{
		std::cerr << "Failed to create the GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(main_window);
	glfwSetKeyCallback(main_window, keyCallback);
	glfwSetInputMode(main_window, GLFW_STICKY_KEYS, true);

	return 1;
}

/**
 * @brief main function
 */
int main(int argc, char *argv[])
{
	initializeGlfw();
	initializeTucano();

	// run all static exercises        
    widget->runExercises();
    
    // run the main display loop
	while (!glfwWindowShouldClose(main_window))
	{		
		widget->render();
		// after each frame, swap the buffers
		glfwSwapBuffers( main_window );
		// check if any callback was activated
		glfwPollEvents();
	}

	glfwDestroyWindow(main_window);
	glfwTerminate();
	return 0;
}
