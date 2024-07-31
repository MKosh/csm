add_library(imgui 
  $ENV{IMGUI}/include/imgui/imgui.cpp
  $ENV{IMGUI}/include/imgui/imgui_demo.cpp
  $ENV{IMGUI}/include/imgui/imgui_draw.cpp
  $ENV{IMGUI}/include/imgui/imgui_tables.cpp
  $ENV{IMGUI}/include/imgui/imgui_widgets.cpp
  $ENV{IMGUI}/include/imgui/backends/imgui_impl_glfw.cpp
  $ENV{IMGUI}/include/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui
  PUBLIC
    $ENV{IMGUI}/include
    $ENV{IMGUI}/include/imgui
    $ENV{IMGUI}/include/imgui/backends
)

# target_link_libraries(imgui
#   PUBLIC
#     OpenGL::OpenGL
# )
