cmake_minimum_required(VERSION 3.0.0)
project(youtubelivedownloader VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(cpr CONFIG REQUIRED)
find_path(TCLAP_INCLUDE_DIRS "tclap/Arg.h")

add_executable(youtubelivedownloader main.cpp)
target_link_libraries(youtubelivedownloader PRIVATE cpr)
target_include_directories(youtubelivedownloader PRIVATE ${TCLAP_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
