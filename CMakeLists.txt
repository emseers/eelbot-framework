cmake_minimum_required(VERSION 3.15)

#===============================================================================
# Project
#===============================================================================
set(EF_LIB_NAME eelbot_framework)
project(${EF_LIB_NAME} VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#===============================================================================
# Options
#===============================================================================
option(VERBOSE "" OFF)
# cpprestsdk
option(BUILD_SHARED_LIBS 0)
option(BUILD_TESTS OFF)
option(BUILD_SAMPLES OFF)
# json
option(JSON_BuildTests OFF)
option(JSON_Install OFF)

#===============================================================================
# Dependencies
#===============================================================================
include(GNUInstallDirs)

#===============================================================================
# Include directories and files
#===============================================================================
set(EF_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include     # Public headers
	${PROJECT_SOURCE_DIR}/src/include # Internal headers
)
file(GLOB_RECURSE EF_HEADERS RELATIVE "${PROJECT_SOURCE_DIR}/" "include/*.h*")

#===============================================================================
# Link Libraries
#===============================================================================
set(EF_LINK_LIBS
	cpprest
	fmt
	nlohmann_json
)

#===============================================================================
# Embedded dependencies
#===============================================================================
add_subdirectory(3rdparty/cpprestsdk)
add_subdirectory(3rdparty/fmt)
add_subdirectory(3rdparty/json)

#===============================================================================
# Sources
#===============================================================================
file(GLOB_RECURSE EF_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#===============================================================================
# Library
#===============================================================================
add_library(${EF_LIB_NAME} ${EF_SOURCES})
set_target_properties(${EF_LIB_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_compile_features(${EF_LIB_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${EF_LIB_NAME} PRIVATE _TURN_OFF_PLATFORM_STRING)
target_include_directories(${EF_LIB_NAME} PRIVATE ${EF_INCLUDE_DIRS})
target_link_libraries(${EF_LIB_NAME} ${EF_LINK_LIBS})

#===============================================================================
# Installation
#===============================================================================
install(TARGETS ${EF_LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${EF_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EF_LIB_NAME})
