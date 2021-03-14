if (NOT TARGET zlibstatic)
	add_subdirectory(3rdparty/zlib)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} zlibstatic)
