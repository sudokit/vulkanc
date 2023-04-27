#include <stdlib.h>

#include "GLFW/glfw3.h"
#include "log.h"
#include "vulkan/vulkan_core.h"

#include "engine/engine.h"
#include "engine/state.h"

int main()
{
    State state = {
        .wTitle = "WINDOW!",
        .wWidth = 800,
        .wHeight = 600,
        .wResizable = false,
        .apiVersion = VK_API_VERSION_1_3,
    };
    run(&state);

    // init(&state);
    // loop(&state);
    // cleanup(&state);

    log_info("Exiting");
    return 0;
}