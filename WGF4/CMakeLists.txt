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
    "src/GraphicObject/Textures/Texture2D.cpp" 
    "include/GraphicObject/Textures/Texture2D.h" 
    "include/GraphicObject/Textures/Texture1D.h" 
    "include/GraphicObject/Textures/DepthTexture.h"  
    "include/GraphicObject/Textures/Texture2DArray.h" 
    "include/GraphicObject/Textures/Texture3D.h" 
    "include/GraphicObject/Passes/RenderPass.h" 
    "include/GraphicObject/Passes/RenderPassFactory.h" 
    "include/GraphicObject/Passes/ScreenPassFactory.h" 
    "include/GraphicObject/Shader/Shader.h" 
    "src/GraphicObject/Shader/Shader.cpp" 
    "include/GraphicObject/BindGroup/BindGroup.h" 
    "src/GraphicObject/BindGroup/BindGroup.cpp" 
    "include/GraphicObject/Buffer/Buffer.h" 
    "include/GraphicObject/Buffer/BaseBuffer.h" 
    "src/GraphicObject/Buffer/BaseBuffer.cpp" 
    "include/GraphicObject/Buffer/BufferLayout.h" 
    "src/GraphicObject/Buffer/BufferLayout.cpp" 
    "include/GraphicObject/Pipeline/RenderPipeline.h"
    "include/GraphicObject/Pipeline/Pipeline.h" 
    "include/GraphicObject/PipelineBuilder/RenderPipelineBuilder.h" 
    "include/GraphicObject/Enums/Topology.h" 
    "include/GraphicObject/Enums/IndexFormat.h" 
    "include/GraphicObject/Enums/FrontFace.h" 
    "include/GraphicObject/Enums/CullMode.h"
    "src/GraphicObject/PipelineBuilder/RenderPipelineBuilder.cpp" 
    "include/GraphicObject/Enums/BlendFactor.h" 
    "include/GraphicObject/Enums/BlendOperation.h" 
    "include/GraphicObject/Enums/TextureFormat.h"
    "include/GraphicObject/Enums/CompareFunction.h"
 "include/GraphicObject/PipelineBuilder/BlendState.h" "include/GraphicObject/PipelineBuilder/DepthStencilState.h" "include/GraphicObject/BindGroup/BindGroupLayout.h"  "include/GraphicObject/Enums/TexDimension.h" "include/GraphicObject/Enums/ShaderStage.h" "include/GraphicObject/Enums/TexSampleType.h" "include/GraphicObject/Enums/TextureAccess.h" "include/GraphicObject/PipelineBuilder/PipelineBuilder.h" "src/GraphicObject/PipelineBuilder/PipelineBuilder.cpp" "include/GraphicObject/BindGroup/BindGroupLayoutBuilder.h" "src/GraphicObject/BindGroup/BindGroupLayoutBuilder.cpp" "include/GraphicObject/Pipeline/PipelineLayout.h")


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

