#include "../vulkan.h"

#include <GLFW/glfw3.h>
#include <stdint.h>
#include <stdlib.h>
#include <vulkan/vulkan_core.h>

#include "../utils.h"
#include "log.h"

// define it here bc my ide couldn't find it

void vk_createInstance(State *state)
{
    // get the required extensions
    uint32_t requiredExtensionsCount = 0;
    const char **requiredExtensions = glfwGetRequiredInstanceExtensions(&requiredExtensionsCount);

    // create a vulkan instance
    PANIC(vkCreateInstance(
              &(VkInstanceCreateInfo){
                  .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
                  .pApplicationInfo =
                      &(VkApplicationInfo){
                          .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                          .pApplicationName = state->vk_applicationName,
                          .pEngineName = state->vk_engineName,
                          .apiVersion = state->vk_apiVersion,
                      },
                  .enabledExtensionCount = requiredExtensionsCount,
                  .ppEnabledExtensionNames = requiredExtensions,
              },
              state->vk_allocator, &state->vk_instance),
          "Couldn't create instance");
}

void vk_selectPhysicalDevice(State *state)
{
    // get the number of physical devices
    uint32_t count = 0;
    log_info("Getting devices");
    PANIC(vkEnumeratePhysicalDevices(state->vk_instance, &count, NULL), "Couldn't enumerate physical devices");
    PANIC(count == 0, "Couldn't find any vulkan supported physical device(s)");
    log_info("Found %i devices", count);
    // select the first physical device
    log_info("Selecting device");
    PANIC(vkEnumeratePhysicalDevices(state->vk_instance, &(uint32_t){1}, &state->vk_physicalDevice),
          "Couldn't enumerate physical devices");
}
void vk_createSurface(State *state)
{
    log_info("Creating surface");
    glfwCreateWindowSurface(state->vk_instance, state->window, state->vk_allocator, &state->vk_surface);
}
void vk_selectQueueFamily(State *state)
{
    log_info("Selecting queue familie(s)");
    state->vk_queueFamily = -1;
    uint32_t count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(state->vk_physicalDevice, &count, NULL);
    log_info("Found %u queue familie(s)", count);
    VkQueueFamilyProperties *queue_families = malloc(count * sizeof(VkQueueFamilyProperties));
    PANIC(queue_families == NULL, "Could't allocate memory for queue_families");
    vkGetPhysicalDeviceQueueFamilyProperties(state->vk_physicalDevice, &count, queue_families);

    for (uint32_t queue_family_index = 0; queue_family_index < count; ++queue_family_index)
    {
        VkQueueFamilyProperties properties = queue_families[queue_family_index];
        if (properties.queueFlags & VK_QUEUE_GRAPHICS_BIT &&
            glfwGetPhysicalDevicePresentationSupport(state->vk_instance, state->vk_physicalDevice, queue_family_index))
        {
            state->vk_queueFamily = queue_family_index;
            log_info("Found and using queue family at index: %u with %u queue(s)", queue_family_index,
                     queue_families->queueCount);
            break;
        }
    }

    PANIC(state->vk_queueFamily == -1, "Couldn't find a suitable queue family");
    free(queue_families);
}
void vk_createDevice(State *state)
{
    log_info("Creating device and queue(s)");
    PANIC(vkCreateDevice(state->vk_physicalDevice,
                         &(VkDeviceCreateInfo){
                             .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                             .pQueueCreateInfos =
                                 &(VkDeviceQueueCreateInfo){
                                     .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
                                     .queueFamilyIndex = state->vk_queueFamily,
                                     .queueCount = 1,
                                     .pQueuePriorities = &(float){1.0},
                                 },
                             .queueCreateInfoCount = 1,
                             .enabledExtensionCount = 1,
                             .ppEnabledExtensionNames = &(const char *){VK_KHR_SWAPCHAIN_EXTENSION_NAME},
                         },
                         state->vk_allocator, &state->vk_device),
          "Couldn't create device and queue(s)");
}
void vk_getQueues(State *state)
{
    log_info("Getting queue from device");
    vkGetDeviceQueue(state->vk_device, state->vk_queueFamily, 0, &state->vk_queue);
}