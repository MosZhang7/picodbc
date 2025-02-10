cmake_minimum_required(VERSION 3.14...3.22)

project(GreeterTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})
target_link_libraries(${PROJECT_NAME} Greeter)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)


# ---- Add GreeterTests ----

enable_testing()

