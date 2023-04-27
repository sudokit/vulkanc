#ifndef STATE
#define STATE

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>

typedef struct State
{
    const char *wTitle;
    const int wWidth, wHeight;
    bool wResizable;

    GLFWwindow *window;

    VkAllocationCallbacks *allocator;
    VkInstance instance;
    uint32_t apiVersion;
} State;

#endif /* STATE */
