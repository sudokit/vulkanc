#include "../vulkan.h"
#include <GLFW/glfw3.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>

#include "../utils.h"

void vk_createInstance(State *state)
{
    // get the required extensions
    uint32_t requiredExtensionsCount = 0;
    const char **requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionsCount);

    // create vulkan appInfo
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = "vulkanc",
        .apiVersion = state->apiVersion,
    };

    // create vulkan createInfo
    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .ppEnabledExtensionNames = requiredExtensions,
        .enabledExtensionCount = requiredExtensionsCount,
    };

    // create vulkan instance
    VKRC(vkCreateInstance(&createInfo, state->allocator, &state->instance), "Couldn't create instance");
}