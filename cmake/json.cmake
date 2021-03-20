if (NOT TARGET nlohmann_json)
	option(JSON_BuildTests OFF)
	option(JSON_Install OFF)

	add_subdirectory(${PROJECT_SOURCE_DIR}/3rdparty/json)
endif()

set(EF_LINK_LIBS ${EF_LINK_LIBS} nlohmann_json)
