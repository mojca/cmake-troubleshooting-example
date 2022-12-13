cmake_minimum_required(VERSION 3.18)

project(AWESOME
    VERSION 0.1.2
    LANGUAGES CXX
)

include(GNUInstallDirs)

option(MYAWESOMELIB_USE_SOURCE_BOOST "Build Boost library dependencies from source" ON)

include(external/boost/CMakeLists.txt)
#include(external/pybind11/CMakeLists.txt)

add_subdirectory(myawesomelib)
