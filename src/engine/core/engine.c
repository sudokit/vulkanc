#include "../engine.h"

#include "../setup.h"
#include "../state.h"
#include "../utils.h"
#include "../vulkan.h"
#include "../window.h"
#include <GLFW/glfw3.h>
#include <log.h>
#include <stdint.h>
#include <vulkan/vulkan_core.h>

void loop(State *state)
{
// vulkan debug stuff
#ifndef NDEBUG
    uint32_t instanceApiVersion = 0;
    PANIC(vkEnumerateInstanceVersion(&instanceApiVersion), "Couldn't enumerate instance version.");
    uint32_t apiVersionVariant = VK_API_VERSION_VARIANT(instanceApiVersion);
    uint32_t apiVersionMajor = VK_API_VERSION_MAJOR(instanceApiVersion);
    uint32_t apiVersionMinor = VK_API_VERSION_MINOR(instanceApiVersion);
    uint32_t apiVersionPatch = VK_API_VERSION_PATCH(instanceApiVersion);
    log_debug("Vulkan API: %i.%i.%i.%i", apiVersionVariant, apiVersionMajor, apiVersionMinor, apiVersionPatch);
    log_debug("GLFW API: %s", glfwGetVersionString());
#endif

    log_info("Entering loop");
    while (!glfwWindowShouldClose(state->window))
    {
        if (glfwGetKey(state->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(state->window, true);

        glfwPollEvents();
    }
    log_info("Exiting loop");
}

void init(State *state)
{
    setupErrorHandling();
    setupLogging();
    createWindow(state);      // 1
    vk_createInstance(state); // 2

    vk_selectPhysicalDevice(state);
    vk_createSurface(state); // 3
    vk_selectQueueFamily(state);
    vk_createDevice(state); // 4
    vk_getQueues(state);
    // vk_createSwapchain(state);
}

void cleanup(State *state)
{
    log_info("Destroying device");
    vkDestroyDevice(state->vk_device, state->vk_allocator);
    log_info("Destroying surface");
    vkDestroySurfaceKHR(state->vk_instance, state->vk_surface, state->vk_allocator); // 3
    log_info("Destroying instance");
    vkDestroyInstance(state->vk_instance, state->vk_allocator); // 2
    log_info("Destroying window");
    glfwDestroyWindow(state->window); // 1
    state->window = NULL;
}

void run(State *state)
{
    init(state);
    loop(state);
    cleanup(state);
}