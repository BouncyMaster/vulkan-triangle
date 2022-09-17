#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define WIDTH  800
#define HEIGHT 600

#define NOT_FOUND 1
#define FOUND 2
#define MALLOC_FAILED 3

uint8_t
checkInstanceLayerProperties(const uint32_t neededCount, const char **needed)
{
	uint32_t availableCount, j;
	bool found;

	vkEnumerateInstanceLayerProperties(&availableCount, NULL);

	VkLayerProperties *available = malloc(
			sizeof(VkLayerProperties) * availableCount);
	if (!available)
		return MALLOC_FAILED;

	vkEnumerateInstanceLayerProperties(&availableCount, available);

	for (uint32_t i = 0; i < neededCount; ++i) {
		found = false;

		for (j = 0; j < availableCount; ++j) {
			if (strcmp(needed[i], available[j].layerName) == 0) {
				found = true;
				break;
			}
		}
		if (!found) {
			free(available);
			return NOT_FOUND;
		}
	}
	free(available);
	return FOUND;
}

int
main(void)
{
	const uint32_t validationCount = 1;
	const char *validationLayers[] = {
		"VK_LAYER_KHRONOS_validation"
	};

	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle", NULL, NULL);

	VkApplicationInfo appInfo;
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	appInfo.pNext = NULL;

	uint32_t glfwExtensionCount = 0;
	const char **glfwExtensions = glfwGetRequiredInstanceExtensions(
			&glfwExtensionCount);

	VkInstanceCreateInfo createInfo;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.flags = 0;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.pNext = NULL;
#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
#else
	switch (checkInstanceLayerProperties(validationCount, validationLayers)) {
	case NOT_FOUND:
		puts("Validation layers unavailable!");
		return NOT_FOUND;
	case MALLOC_FAILED:
		puts("Failed to allocate memory!");
		return MALLOC_FAILED;
	}

	createInfo.enabledLayerCount = validationCount;
	createInfo.ppEnabledLayerNames = validationLayers;
#endif // NDEBUG

	VkInstance instance;
	if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
		puts("Failed to create instance!");
		return 1;
	}

	// Take the first gpu
	uint32_t deviceCount = 1;
	VkPhysicalDevice devices[1];
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices);
	VkPhysicalDevice physicalDevice = devices[0];

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	vkDestroyInstance(instance, NULL);
	glfwTerminate();
}