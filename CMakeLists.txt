cmake_minimum_required(VERSION 3.22.1)

project(vulkanc LANGUAGES CXX C)

# SET(CMAKE_CXX_COMPILER /usr/lib/llvm-14/bin/clang)
# SET(CMAKE_C_COMPILER /usr/lib/llvm-14/bin/clang)
add_executable(${PROJECT_NAME}
  src/main.c
  src/engine/core/engine.c
  src/engine/core/setup.c
  src/engine/window/window.c
  src/engine/vulkan/vulkan.c
)

# -- CCACHE --
find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache) # Less useful to do it for linking, see edit2
endif(CCACHE_FOUND)

# -- CPM --
set(CPM_DOWNLOAD_VERSION 0.38.1)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

if(NOT(EXISTS ${CPM_DOWNLOAD_LOCATION}))
  message(STATUS "Downloading CPM.cmake")
  file(DOWNLOAD
    https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
    ${CPM_DOWNLOAD_LOCATION}
  )
endif()

include(${CPM_DOWNLOAD_LOCATION})

CPMAddPackage(
  NAME glfw
  VERSION 3.3.8
  GITHUB_REPOSITORY "glfw/glfw"
  GIT_TAG "3.3.8"
)

CPMAddPackage(
  NAME Ccache.cmake
  VERSION 1.2.4
  GITHUB_REPOSITORY "TheLartians/Ccache.cmake"
  GIT_TAG "v1.2.4"
)

# CPMAddPackage(
#   NAME spdlog
#   VERSION 1.11.0
#   GITHUB_REPOSITORY "gabime/spdlog"
#   GIT_TAG "v1.11.0"
# )

CPMAddPackage(
  NAME cglm
  VERSION 0.8.9
  GITHUB_REPOSITORY "recp/cglm"
  GIT_TAG "v0.8.9"
)

CPMAddPackage(
  NAME Vulkan-Headers
  VERSION 1.3.248
  GITHUB_REPOSITORY "KhronosGroup/Vulkan-Headers"
  GIT_TAG "v1.3.248"
)

CPMAddPackage(
  NAME VulkanMemoryAllocator
  VERSION 3.0.1
  GITHUB_REPOSITORY "GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator"
  GIT_TAG "v3.0.1"
)

# set (CMAKE_CXX_FLAGS "-dl -pthread") #-X11 -Xxf86vm -Xrandr -Xi")

# add_subdirectory(thirdparty/glad/)
# add_subdirectory(thirdparty/stb/)
add_subdirectory(thirdparty/log.c)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_compile_features(${PROJECT_NAME} PRIVATE c_std_17)
add_compile_options(-DLOG_USE_COLOR)
target_link_libraries(${PROJECT_NAME} PRIVATE -lm glfw Vulkan-Headers cglm log.c VulkanMemoryAllocator)
