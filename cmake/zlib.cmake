include_directories(${PROJECT_SOURCE_DIR}/3rdparty/zlib) # Workaround for https://github.com/madler/zlib/issues/218.
add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/zlib ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/zlib EXCLUDE_FROM_ALL)
set(EF_ZLIB_INCLUDE_DIRS ${EF_ZLIB_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/3rdparty/zlib ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/zlib)
set(EF_INCLUDE_DIRS ${EF_INCLUDE_DIRS} ${EF_ZLIB_INCLUDE_DIRS})
set(EF_LINK_LIBS ${EF_LINK_LIBS} zlibstatic)
