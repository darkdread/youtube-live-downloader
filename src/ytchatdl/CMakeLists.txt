cmake_minimum_required(VERSION 3.0.0)
project(ytchatdl VERSION 0.1.0)

find_package(cpr CONFIG REQUIRED)
find_path(TCLAP_INCLUDE_DIRS "tclap/Arg.h")
find_package(nlohmann_json CONFIG REQUIRED)

add_executable(ytchatdl ${CMAKE_CURRENT_LIST_DIR}/main.cpp ${CMAKE_CURRENT_LIST_DIR}/chat.cpp)
target_link_libraries(ytchatdl PRIVATE cpr)
target_include_directories(ytchatdl PRIVATE ${TCLAP_INCLUDE_DIRS})
target_link_libraries(ytchatdl PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
