

add_library(WGF4App
    "include/Application/Application.h"
    "include/Application/Scene.h"
    "src/Application/Application.cpp"
    "src/GUI/GUIPage.cpp" 
    "src/Application/Scene.cpp" 
    "include/GUI/GUIStyle.h" 
    "include/GUI/Grid/Grid.h"
    "include/GUI/GUIElement.h" 
    "src/GUI/GUIPage.cpp" "src/GUI/Grid/Grid.cpp" "include/GUI/Grid/GridSegment.h" "include/GUI/Container.h" "src/GUI/Container.cpp")

set_target_properties(WGF4App PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)

add_subdirectory("dep/imgui-docking")

target_include_directories(WGF4App PUBLIC "include/")
target_link_libraries(WGF4App PUBLIC WGF4 imgui)

TARGET_COPY_WEBGPU_BINARIES(WGF4App)