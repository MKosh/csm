add_library(implot
  $ENV{IMPLOT}/implot.cpp
  $ENV{IMPLOT}/implot_items.cpp
  $ENV{IMPLOT}/implot_demo.cpp
)

target_include_directories(implot
  PUBLIC
    $ENV{IMPLOT}
    $ENV{IMGUI}/include
    $ENV{IMGUI}/include/imgui
    $ENV{IMGUI}/include/imgui/backends
)

# target_link_libraries(implot
#   PUBLIC
#     OpenGL::OpenGL
# )
