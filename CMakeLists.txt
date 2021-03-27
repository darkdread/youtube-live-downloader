cmake_minimum_required(VERSION 3.0.0)
project(yld VERSION 0.1.0)

# SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -gdwarf")

# if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#   set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
#     CACHE STRING "")
#     message(" [INFO] VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
# endif()


# set(CMAKE_TOOLCHAIN_FILE "C:/Users/walson.low/Desktop/vcpkg/scripts/buildsystems/vcpkg.cmake")
# message("${CMAKE_TOOLCHAIN_FILE}"

# SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -gdwarf")

include(CTest)
enable_testing()

include_directories(include)
include(src/ytchatdl/CMakeLists.txt)
include(src/ytchatrender/CMakeLists.txt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
