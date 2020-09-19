if (NOT TARGET cpr)
	option(BUILD_SHARED_LIBS OFF)
	option(BUILD_CPR_TESTS OFF)

	add_subdirectory(3rdparty/cpr)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} cpr)
