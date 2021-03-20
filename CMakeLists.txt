# Part of the Eelbot Framework project, under the MIT License.
# Copyright (c) 2020 The Emseers.

# Disable in-source builds.
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(FATAL_ERROR "FATAL: In-source builds are not supported.")
endif()

cmake_minimum_required(VERSION 3.15)

#======================================================================================================================
# Project
#======================================================================================================================
set(EF_LIB_NAME eelbot_framework)
project(${EF_LIB_NAME} VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Determine if project is built an embedded project or a top level project.
set(TOP_LEVEL_PROJECT OFF)
if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
	set(TOP_LEVEL_PROJECT ON)
endif ()

#======================================================================================================================
# Options
#======================================================================================================================
option(VERBOSE "" OFF)
option(EELBOT_FRAMEWORK_TESTS "Build the test target." ${TOP_LEVEL_PROJECT})

#======================================================================================================================
# Dependencies
#======================================================================================================================
include(GNUInstallDirs)

#======================================================================================================================
# Include directories and files
#======================================================================================================================
set(EF_PUBLIC_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/include
)
set(EF_INCLUDE_DIRS
	${PROJECT_SOURCE_DIR}/src/include
)
set(EF_ZLIB_INCLUDE_DIRS)
file(GLOB EF_HEADERS "${PROJECT_SOURCE_DIR}/include/${EF_LIB_NAME}/*.hpp")
file(GLOB EF_LOG_HEADERS "${PROJECT_SOURCE_DIR}/include/${EF_LIB_NAME}/log/*.hpp")
file(GLOB EF_DISCORD_BOT_HEADERS "${PROJECT_SOURCE_DIR}/include/${EF_LIB_NAME}/discord_bot/*.hpp")

#======================================================================================================================
# Link Libraries
#======================================================================================================================
set(EF_LINK_LIBS)

#======================================================================================================================
# Compile Definitions
#======================================================================================================================
set(EF_COMPILE_DEFS)

#======================================================================================================================
# Embedded dependencies
#======================================================================================================================
include(cmake/asio.cmake)
include(cmake/zlib.cmake)
include(cmake/cpr.cmake)
include(cmake/fmt.cmake)
include(cmake/json.cmake)
include(cmake/websocketpp.cmake)

#======================================================================================================================
# Sources
#======================================================================================================================
file(GLOB_RECURSE EF_SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

#======================================================================================================================
# Library
#======================================================================================================================
add_library(${EF_LIB_NAME} ${EF_SOURCES})
set_target_properties(${EF_LIB_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)
target_compile_features(${EF_LIB_NAME} PRIVATE cxx_std_17)
target_compile_definitions(${EF_LIB_NAME} PRIVATE ${EF_COMPILE_DEFS})
target_include_directories(${EF_LIB_NAME}
	PUBLIC ${EF_PUBLIC_INCLUDE_DIRS}
	PRIVATE ${EF_INCLUDE_DIRS}
)
target_link_libraries(${EF_LIB_NAME} ${EF_LINK_LIBS})

#======================================================================================================================
# Installation
#======================================================================================================================
install(TARGETS ${EF_LIB_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${EF_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EF_LIB_NAME})
install(FILES ${EF_LOG_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EF_LIB_NAME}/log)
install(FILES ${EF_DISCORD_BOT_HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${EF_LIB_NAME}/discord_bot)

#======================================================================================================================
# Tests
#======================================================================================================================
if (EELBOT_FRAMEWORK_TESTS)
	set(EF_TEST_NAME ${EF_LIB_NAME}_test)
	include(cmake/catch.cmake)
	file(GLOB_RECURSE EF_TESTS "${PROJECT_SOURCE_DIR}/test/*.cpp")

	add_executable(${EF_TEST_NAME} ${EF_SOURCES} ${EF_TESTS})
	set_target_properties(${EF_TEST_NAME} PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED YES
		CXX_EXTENSIONS NO
	)
	target_compile_features(${EF_TEST_NAME} PRIVATE cxx_std_17)
	target_compile_definitions(${EF_TEST_NAME} PRIVATE ${EF_COMPILE_DEFS})
	target_include_directories(${EF_TEST_NAME}
		PUBLIC ${EF_PUBLIC_INCLUDE_DIRS}
		PRIVATE ${EF_INCLUDE_DIRS}
	)
	target_link_libraries(${EF_TEST_NAME} ${EF_LINK_LIBS})
endif ()
