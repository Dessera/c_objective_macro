cmake_minimum_required(VERSION 3.5.0)
project(c_objective_macro VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(c_objective_macro main.c test.c)
target_include_directories(c_objective_macro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
