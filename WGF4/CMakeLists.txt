# CMakeList.txt : CMake project for WGF4, include source and define
# project specific logic here.

# Add source to this project's executable.
add_library(WGF4 
    "include/WGF4.h"
    "include/AppWindow/AppWindow.h"
    "include/AppWindow/Events.h"
    "src/WGF4.cpp"
    "src/AppWindow/AppWindow.cpp"
    "include/GraphicObject/GraphicObject.h" 
    "include/Logging/Tracker.h" 
    "include/GraphicObject/Textures/Texture.h" 
    "src/GraphicObject/Textures/Image.cpp" 
    "include/Framework/Device.h" 
    "include/Framework/DeviceLimits.h" 
    "src/Framework/Device.cpp" 
    "include/Logging/Logging.h" 
    "src/Logging/Logging.cpp" 
    "include/Framework/Instance.h" 
    "src/Framework/Instance.cpp" 
    "include/Framework/Adapter.h" 
    "src/Framework/Adapter.cpp" 
    "include/AppWindow/WindowParameters.h" 
    "include/GraphicObject/Textures/TextureView.h" 
    "include/GraphicObject/Textures/Image.h"
 "src/GraphicObject/Textures/Texture2D.cpp" "include/GraphicObject/Textures/Texture2D.h" "include/GraphicObject/Textures/Texture1D.h" "include/GraphicObject/Textures/DepthTexture.h"  "include/GraphicObject/Textures/Texture2DArray.h" "include/GraphicObject/Textures/Texture3D.h" "include/GraphicObject/Passes/RenderPass.h" "include/GraphicObject/Passes/RenderPassFactory.h" "include/GraphicObject/Passes/ScreenPassFactory.h" "include/GraphicObject/Shader/Shader.h" "src/GraphicObject/Shader/Shader.cpp")


set_target_properties(WGF4 PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

target_include_directories(WGF4 PUBLIC "include")
target_include_directories(WGF4 PUBLIC "../vendor/headerOnly")

if (CMAKE_VERSION VERSION_GREATER 3.16)
  set_property(TARGET WGF4 PROPERTY CXX_STANDARD 20)
endif()

include(FetchContent)

FetchContent_Declare(
    webgpu
    GIT_REPOSITORY https://github.com/eliemichel/WebGPU-distribution
    GIT_TAG        wgpu
)

FetchContent_MakeAvailable(webgpu)
target_link_libraries(WGF4 PUBLIC glfw webgpu glfw3webgpu glm)
target_copy_webgpu_binaries(WGF4)

