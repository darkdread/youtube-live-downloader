set(CMAKE_VERBOSE_MAKEFILE ON)
cmake_minimum_required(VERSION 3.0.0)
project(ytchatrender VERSION 0.1.0)

find_path(TCLAP_INCLUDE_DIRS "tclap/Arg.h")
find_package(nlohmann_json CONFIG REQUIRED)
# find_package(skia CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

message("hello ${CMAKE_CXX_FLAGS_DEBUG}")
# SET(CMAKE_CXX_FLAGS_DEBUG "-g -Xclang -gcodeview -O0 -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd")
message("hello ${CMAKE_CXX_FLAGS_DEBUG}")

add_executable(ytchatrender ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${CMAKE_CURRENT_LIST_DIR}/chatwindow.cpp)

target_include_directories(ytchatrender PRIVATE ${TCLAP_INCLUDE_DIRS})
target_include_directories(ytchatrender PRIVATE ${CMAKE_SOURCE_DIR}/third_party/skia)
target_link_libraries(ytchatrender PRIVATE glfw)
target_link_libraries(ytchatrender PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(ytchatrender PRIVATE ${CMAKE_SOURCE_DIR}/third_party/skia/skia.lib)
target_link_libraries(ytchatrender PRIVATE ${CMAKE_SOURCE_DIR}/third_party/skia/opengl32.lib)
# target_link_libraries(ytchatrender PRIVATE skia skia::skia)

# Disable minwindef.h min/max macro
target_compile_options(ytchatrender PRIVATE -DNOMINMAX)