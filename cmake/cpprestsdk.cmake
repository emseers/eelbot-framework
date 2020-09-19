if (NOT TARGET cpprest)
	option(BUILD_SHARED_LIBS 0)
	option(BUILD_TESTS OFF)
	option(BUILD_SAMPLES OFF)

	add_subdirectory(3rdparty/cpprestsdk)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} cpprest)
set(EF_COMPILE_DEFS ${EF_COMPILE_DEFS} _TURN_OFF_PLATFORM_STRING)
