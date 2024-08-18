add_executable(distribution_of_money main.cc distribution_of_money.cc)

target_include_directories(distribution_of_money
  PUBLIC
    ${CMAKE_SOURCE_DIR}/external
    ${IMGUI_SRC}
    ${IMGUI_SRC}/backends
)

target_link_libraries(distribution_of_money
  PUBLIC
    glfw
    imgui
    implot
    OpenGL::OpenGL
)

# target_include_directories(distribution_of_money
#   PUBLIC
#     $ENV{MATPLOTPP}/include
# )
#
# target_link_directories(distribution_of_money
#   PUBLIC
#     $ENV{MATPLOTPP}/lib
#     $ENV{MATPLOTPP}/lib/Matplot++
# )
#
# target_link_libraries(distribution_of_money
#   PUBLIC
#     matplot
#     nodesoup
# )
