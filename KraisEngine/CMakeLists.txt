file(GLOB_RECURSE KE_SOURCES src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})

add_library(KraisEngine STATIC ${KE_SOURCES} ${KE_HEADERS})
set_property(TARGET KraisEngine PROPERTY CXX_STANDARD 17)

add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/glfw)

find_package(OpenGL REQUIRED)

target_link_libraries(KraisEngine PUBLIC spdlog)
target_link_libraries(KraisEngine PUBLIC glad)
target_link_libraries(KraisEngine PUBLIC glfw)

target_link_libraries(KraisEngine PUBLIC opengl32)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_precompile_headers(KraisEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/ke_pch.h)

