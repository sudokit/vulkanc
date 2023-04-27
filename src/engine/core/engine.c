#include "../engine.h"

#include "../setup.h"
#include "../state.h"
#include "../vulkan.h"
#include "../window.h"
#include "vulkan/vulkan_core.h"
#include <GLFW/glfw3.h>
#include <log.h>
#include <stdint.h>

void init(State *state)
{
    setupErrorHandling();
    setupLogging();
    createWindow(state);
    vk_createInstance(state);
}

void loop(State *state)
{
// vulkan debug stuff
#ifndef NDEBUG
    uint32_t instanceApiVersion = 0;
    vkEnumerateInstanceVersion(&instanceApiVersion);
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

void cleanup(State *state)
{
    log_info("Destroying window");
    glfwDestroyWindow(state->window);
    vkDestroyInstance(state->instance, state->allocator);
    state->window = NULL;
}

void run(State *state)
{
    init(state);
    loop(state);
    cleanup(state);
}