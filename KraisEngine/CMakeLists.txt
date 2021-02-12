file(GLOB_RECURSE KE_SOURCES src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})


add_library(KraisEngine STATIC ${KE_SOURCES} ${KE_HEADERS})

#file(GLOB_RECURSE IMGUI_SOURCES vendor/imgui/*.cpp)
#file(GLOB_RECURSE IMGUI_HEADERS vendor/imgui/*.h)
#target_sources(KraisEngine PRIVATE ${IMGUI_SOURCES} ${IMGUI_HEADERS})

#imgui_impl_opengl3.cpp
#imgui_impl_opengl3.h
#imgui_impl_glfw.cpp
#imgui_impl_glfw.h

file(GLOB IMGUI_MAIN_CPP vendor/imgui/*.cpp)
file(GLOB IMGUI_MAIN_H vendor/imgui/*.h)

list(APPEND IMGUI_BACKENDS_SRC 
	vendor/imgui/backends/imgui_impl_glfw.h 
	vendor/imgui/backends/imgui_impl_glfw.cpp
	vendor/imgui/backends/imgui_impl_opengl3.h
	vendor/imgui/backends/imgui_impl_opengl3.cpp
)
message(IMGUI: ${IMGUI_BACKENDS_SRC})
target_sources(KraisEngine PRIVATE ${IMGUI_BACKENDS_SRC} ${IMGUI_MAIN_H} ${IMGUI_MAIN_CPP})
#target_sources(KraisEngine PUBLIC res)

set_property(TARGET KraisEngine PROPERTY CXX_STANDARD 17)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
#add_subdirectory(vendor/stb)

find_package(OpenGL REQUIRED)

target_link_libraries(KraisEngine PUBLIC spdlog)
target_link_libraries(KraisEngine PUBLIC glad)
target_link_libraries(KraisEngine PUBLIC glfw)
target_link_libraries(KraisEngine PUBLIC glm::glm)
target_link_libraries(KraisEngine PUBLIC opengl32)
#target_link_libraries(KraisEngine PUBLIC stb)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glm)
target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)

target_precompile_headers(KraisEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ke_pch.h)

#add_custom_command(TARGET KraisEngine POST_BUILD COMMAND xcopy /i /e /s /y /f "$(ProjectDir)EngineRes" "$(OutDir)res")

