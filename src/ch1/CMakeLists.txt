add_executable(distribution_of_money distribution_of_money.cc)

target_include_directories(distribution_of_money
  PUBLIC
    $ENV{MATPLOTPP}/include
)

target_link_directories(distribution_of_money
  PUBLIC
    $ENV{MATPLOTPP}/lib
    $ENV{MATPLOTPP}/lib/Matplot++
)

target_link_libraries(distribution_of_money
  PUBLIC
    matplot
    nodesoup
)
