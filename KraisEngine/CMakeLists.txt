file(GLOB_RECURSE KE_SOURCES src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})

add_library(KraisEngine STATIC ${KE_SOURCES} ${KE_HEADERS})
set_property(TARGET KraisEngine PROPERTY CXX_STANDARD 17)

#find_package(glad PATHS KraisEngine/vendor/glad)
#find_package(glfw PATHS KraisEngine/vendor/glfw)

#file(GLOB_RECURSE IMGUI_HEADERS ${CMAKE_SOURCE_DIR}/vendor/imgui/*.h)
#file(GLOB_RECURSE IMGUI_SOURCES ${CMAKE_SOURCE_DIR}/vendor/imgui/*.cpp)
#target_sources(KraisEngine PUBLIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})

target_link_libraries(KraisEngine PRIVATE spdlog)
target_link_libraries(KraisEngine PUBLIC glad)
target_link_libraries(KraisEngine PUBLIC glfw)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_precompile_headers(KraisEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ke_pch.h)

