if (NOT TARGET Catch2)
	add_subdirectory(3rdparty/catch)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} Catch2)
set(EF_COMPILE_DEFS ${EF_COMPILE_DEFS} CATCH_CONFIG_MAIN)
