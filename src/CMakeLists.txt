add_executable(test test.cxx)

target_include_directories(test 
  PUBLIC
    # ${CMAKE_SOURCE_DIR}/external/matplot/include
    $ENV{MATPLOTPP}/include
)

target_link_directories(test
  PUBLIC
    # ${CMAKE_SOURCE_DIR}/external/matplot/lib
    # ${CMAKE_SOURCE_DIR}/external/matplot/lib/Matplot++/
    $ENV{MATPLOTPP}/lib
    $ENV{MATPLOTPP}/lib/Matplot++
)

target_link_libraries(test
  PUBLIC
    matplot
    nodesoup
)

add_subdirectory(ch1)
