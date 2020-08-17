add_definitions(-DKE_PLATFORM_WINDOWS -DKE_BUILD_DLL)
#set (KE_SOURCES 
#	src/KraisEngine/CApplication.cpp
#	src/KraisEngine/CLog.cpp
#)

file(GLOB_RECURSE KE_SOURCES src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE KE_HEADERS src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})

add_library(KraisEngine SHARED ${KE_SOURCES} ${KE_HEADERS})

file(GLOB_RECURSE IMGUI_HEADERS ${CMAKE_SOURCE_DIR}/vendor/imgui/*.h)
file(GLOB_RECURSE IMGUI_SOURCES ${CMAKE_SOURCE_DIR}/vendor/imgui/*.cpp)
target_sources(KraisEngine PUBLIC ${IMGUI_HEADERS} ${IMGUI_SOURCES})

target_link_libraries(KraisEngine PUBLIC spdlog)

target_include_directories(KraisEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

