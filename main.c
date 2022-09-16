#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH  800
#define HEIGHT 600

int
main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

	printf("%u extensions supported\n", extensionCount);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}