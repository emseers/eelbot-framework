cmake_minimum_required(VERSION 3.14)

#===============================================================================
# Project information
#===============================================================================
set(EF_LIB_NAME eelbot_framework)
project(${EF_LIB_NAME} VERSION 0.0.1 LANGUAGES CXX)

#===============================================================================
# Options
#===============================================================================
option(VERBOSE "" OFF)

#===============================================================================
# Dependencies
#===============================================================================
include(GNUInstallDirs)

#===============================================================================
# Include directories and files
#===============================================================================
set(EF_INCLUDE_DIRS
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/3rdparty/asio/asio/include
)
file(GLOB_RECURSE EF_HEADERS RELATIVE "${PROJECT_SOURCE_DIR}/" "include/*.h*")

#===============================================================================
# Sources
#===============================================================================
file(GLOB_RECURSE EF_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#===============================================================================
# Library
#===============================================================================
add_library(${EF_LIB_NAME} ${EF_SOURCES})
set_target_properties(${EF_LIB_NAME} PROPERTIES
  VERSION ${PROJECT_VERSION})
target_include_directories(${EF_LIB_NAME} PRIVATE ${EF_INCLUDE_DIRS})

#===============================================================================
# Installation
#===============================================================================
install(TARGETS ${EF_LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${EF_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EF_LIB_NAME})
