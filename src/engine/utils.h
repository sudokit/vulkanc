#ifndef UTILS
#define UTILS

#include <log.h>
#include <signal.h>

#define VKRC(ERROR, FORMAT, ...)                                                                                       \
    {                                                                                                                  \
        if (ERROR)                                                                                                     \
        {                                                                                                              \
            log_error("Error(%i): " FORMAT, ERROR, ##__VA_ARGS__);                                                     \
            raise(SIGABRT);                                                                                            \
        }                                                                                                              \
    }

#endif /* UTILS */
