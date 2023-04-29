#include "../window.h"

#include <GLFW/glfw3.h>

#include <log.h>
#include <stdint.h>

void createWindow(State *state)
{
    log_info("Initializing GLFW");
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, state->wResizable);
    log_info("Creating window: size: (%i %i) title: \"%s\"", state->wWidth, state->wHeight, state->wTitle);
    state->window = glfwCreateWindow((uint32_t)state->wWidth, (uint32_t)state->wHeight, state->wTitle, NULL, NULL);
}