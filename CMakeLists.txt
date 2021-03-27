cmake_minimum_required(VERSION 3.0.0)
project(ytchatdl VERSION 0.1.0)

# if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
#     CACHE STRING "")
#     message(" [INFO] VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
# endif()


# set(CMAKE_TOOLCHAIN_FILE "C:/Users/walson.low/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake")
# message("${CMAKE_TOOLCHAIN_FILE}"

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -gdwarf")

include(CTest)
enable_testing()

find_package(cpr CONFIG REQUIRED)
find_path(TCLAP_INCLUDE_DIRS "tclap/Arg.h")
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(include)

add_executable(ytchatdl main.cpp src/chat.cpp)
target_link_libraries(ytchatdl PRIVATE cpr)
target_include_directories(ytchatdl PRIVATE ${TCLAP_INCLUDE_DIRS})
target_link_libraries(ytchatdl PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
