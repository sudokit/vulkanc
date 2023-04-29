#ifndef VULKAN
#define VULKAN

#include "state.h"

void vk_createInstance(State *state);
void vk_selectPhysicalDevice(State *state);
void vk_createSurface(State *state);
void vk_selectQueueFamily(State *state);
void vk_createDevice(State *state);
void vk_getQueues(State *state);

#endif /* VULKAN */
