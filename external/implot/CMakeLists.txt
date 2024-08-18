add_library(implot
  ${IMPLOT_SRC}/implot.cpp
  ${IMPLOT_SRC}/implot_items.cpp
  ${IMPLOT_SRC}/implot_demo.cpp
)

target_include_directories(implot
  PUBLIC
    ${IMPLOT_SRC}
    ${IMGUI_SRC}
    ${IMGUI_SRC}/backends
)
