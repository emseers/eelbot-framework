if (NOT TARGET fmt)
	add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/fmt EXCLUDE_FROM_ALL)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} fmt)
