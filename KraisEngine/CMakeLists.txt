
file(GLOB_RECURSE KE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
#message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
#message(KE_HEADERS:  ${KE_HEADERS})

add_library(KraisEngine STATIC ${KE_SOURCES} ${KE_HEADERS})

set_property(TARGET KraisEngine PROPERTY CXX_STANDARD 17)

# ============================== #
# ImGUI as sources #
# Include main sources + specific backend files
file(GLOB IMGUI_MAIN_CPP RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} vendor/imgui/*.cpp)
file(GLOB IMGUI_MAIN_H RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} vendor/imgui/*.h)
list(APPEND IMGUI_BACKENDS_SRC 
	vendor/imgui/backends/imgui_impl_glfw.h
	vendor/imgui/backends/imgui_impl_opengl3.h

	vendor/imgui/backends/imgui_impl_glfw.cpp
	vendor/imgui/backends/imgui_impl_opengl3.cpp
)
message(IMGUI: ${IMGUI_MAIN_H} ${IMGUI_MAIN_CPP} ${IMGUI_BACKENDS_SRC})
target_sources(KraisEngine PRIVATE ${IMGUI_BACKENDS_SRC} ${IMGUI_MAIN_H} ${IMGUI_MAIN_CPP})
# ============================== #

add_subdirectory(vendor/spdlog EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glad EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glfw EXCLUDE_FROM_ALL)
add_subdirectory(vendor/glm EXCLUDE_FROM_ALL)

#add_subdirectory(vendor/openal)
#add_subdirectory(vendor/fmod)

#add_custom_command(
#    TARGET KraisEngine 
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy
#        $<TARGET_FILE:fmod>
#        $<TARGET_FILE_DIR:KraisEngine>
#)

#set(LIBTYPE STATIC)
#add_subdirectory(vendor/openal build)

#add_library(openal STATIC IMPORTED)
#set_property(TARGET openal PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}"vendor/openal/lib/OpenAL32.lib")


find_package(OpenGL REQUIRED)

target_link_libraries(KraisEngine PUBLIC spdlog)
target_link_libraries(KraisEngine PUBLIC glad)
target_link_libraries(KraisEngine PUBLIC glfw)
target_link_libraries(KraisEngine PUBLIC glm::glm)
target_link_libraries(KraisEngine PUBLIC opengl32)
#target_link_libraries(KraisEngine PUBLIC stb)
#target_link_libraries(KraisEngine PUBLIC openal)
#target_link_libraries(KraisEngine PUBLIC fmod)

KE_IMPORT_SHARED(KraisEngine fmod 
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/fmod/lib/x64/fmodL.dll 
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/fmod/lib/x64/fmodL_vc.lib 
	${CMAKE_CURRENT_SOURCE_DIR}/vendor/fmod/inc)


#target_link_libraries(KraisEngine PUBLIC vendor/openal/lib/OpenAL32.lib)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
#target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/openal/include)
target_precompile_headers(KraisEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ke_pch.h)



# openal в STATIC сборке требует этот флаг
#if (LIBTYPE STREQUAL "STATIC")
#	target_compile_definitions(KraisEngine PUBLIC AL_LIBTYPE_STATIC)
#endif()

#add_custom_command(TARGET KraisEngine POST_BUILD COMMAND xcopy /i /e /s /y /f "$(ProjectDir)EngineRes" "$(OutDir)res")

