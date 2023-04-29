#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "log.h"
#include "vulkan/vulkan_core.h"

#include "engine/engine.h"
#include "engine/state.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

int main()
{
    State state = {
        .wTitle = "WINDOW!",
        .wWidth = WINDOW_WIDTH,
        .wHeight = WINDOW_HEIGHT,
        .wResizable = false,
        .vk_apiVersion = VK_API_VERSION_1_3,
        .vk_applicationName = "vulkanc",
        .vk_engineName = "vulkanc engine",
    };
    run(&state);

    // init(&state);
    // loop(&state);
    // cleanup(&state);

    log_info("Exiting");
    return 0;
}