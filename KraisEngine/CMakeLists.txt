file(GLOB_RECURSE KE_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})


add_library(KraisEngine STATIC ${KE_SOURCES} ${KE_HEADERS})


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


set_property(TARGET KraisEngine PROPERTY CXX_STANDARD 17)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
#add_subdirectory(vendor/stb)
#add_subdirectory(vendor/imgui)

find_package(OpenGL REQUIRED)

target_link_libraries(KraisEngine PUBLIC spdlog)
target_link_libraries(KraisEngine PUBLIC glad)
target_link_libraries(KraisEngine PUBLIC glfw)
target_link_libraries(KraisEngine PUBLIC glm::glm)
target_link_libraries(KraisEngine PUBLIC opengl32)
#target_link_libraries(KraisEngine PUBLIC stb)
#target_link_libraries(KraisEngine PUBLIC imgui)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)

target_precompile_headers(KraisEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ke_pch.h)

#add_custom_command(TARGET KraisEngine POST_BUILD COMMAND xcopy /i /e /s /y /f "$(ProjectDir)EngineRes" "$(OutDir)res")

