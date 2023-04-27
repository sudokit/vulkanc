#ifndef CALLBACKS
#define CALLBACKS

#include <GLFW/glfw3.h>
#include <log.h>

#include <signal.h>

log_LogFn log_callback(log_Event *logev)
{
    if (logev->level == LOG_ERROR)
    {
        raise(SIGABRT);
    }

    return 0;
}

void glfwErrorCallback(int error_code, const char *description)
{
    error_code ? log_error("GLFW: %s", description) : log_warn("GLFW: %s", description);
}

void exitCallback()
{
    log_info("Terminating GLFW");
    glfwTerminate();
}

#endif /* CALLBACKS */
