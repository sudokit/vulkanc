#include "../setup.h"

#include <stdlib.h>

#include <GLFW/glfw3.h>

#include "../callbacks.h"
#include <log.h>

void setupLogging()
{
    log_set_level(LOG_DEBUG);
    log_add_callback((void *)log_callback, (void *)0, LOG_ERROR); // wtf
}
void setupErrorHandling()
{
    glfwSetErrorCallback(glfwErrorCallback);
    atexit(exitCallback);
}