#ifndef STATE
#define STATE

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>

typedef struct State
{
    const char *wTitle;
    const unsigned int wWidth, wHeight;
    bool wResizable;

    GLFWwindow *window;

    VkAllocationCallbacks *vk_allocator;
    VkInstance vk_instance;
    VkPhysicalDevice vk_physicalDevice;
    VkSurfaceKHR vk_surface;
    uint32_t vk_apiVersion;
    int32_t vk_queueFamily;
    VkDevice vk_device;
    VkQueue vk_queue;
    const char *vk_applicationName;
    const char *vk_engineName;
} State;

#endif /* STATE */
