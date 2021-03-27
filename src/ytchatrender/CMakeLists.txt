cmake_minimum_required(VERSION 3.0.0)
project(ytchatrender VERSION 0.1.0)

find_path(TCLAP_INCLUDE_DIRS "tclap/Arg.h")
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ytchatrender ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_include_directories(ytchatrender PRIVATE ${TCLAP_INCLUDE_DIRS})
target_link_libraries(ytchatrender PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
