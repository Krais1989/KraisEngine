cmake_minimum_required(VERSION 3.16)
project(KraisEngine LANGUAGES CXX)

set (KraisEngine_VERSION_MAJOR 0)
set (KraisEngine_VERSION_MINOR 1)
set (KraisEngine_VERSION_PATCH 0)
set (KraisEngine_VERSION "${KraisEngine_VERSION_MAJOR}.${KraisEngine_VERSION_MINOR}.${KraisEngine_VERSION_PATCH}")

#set (CPACK_PACKAGE_FILE_NAME)

#set(CPACK_PACKAGE_DESCRIPTION )
#set(CPACK_PACKAGE_ICON)

message(${CMAKE_COMMAND})

if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE DEBUG)
endif()
message(CMAKE_BUILD_TYPE>${CMAKE_BUILD_TYPE})

add_subdirectory(vendor/spdlog)
add_subdirectory(KraisEngine/vendor/glad)
add_subdirectory(KraisEngine/vendor/glfw)

set_target_properties(glfw PROPERTIES FOLDER "VENDOR")
set_target_properties(uninstall PROPERTIES FOLDER "VENDOR")
set_target_properties(glad PROPERTIES FOLDER "VENDOR")
set_target_properties(glad-generate-files PROPERTIES FOLDER "VENDOR")
set_target_properties(spdlog PROPERTIES FOLDER "VENDOR")

add_subdirectory(KraisEngine)
add_subdirectory(Sandbox)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug) 

if (${CMAKE_SYSTEM_NAME} STREQUAL Windows)
	target_compile_definitions(KraisEngine PUBLIC KE_PLATFORM_WINDOWS)
elseif (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
	target_compile_definitions(KraisEngine PUBLIC KE_PLATFORM_LINUX)
endif()

# ======================================
# INSTALL
# ======================================
install(TARGETS Sandbox DESTINATION bin)

set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_PREFIX "E:/INSTALLS/KraisEngine")
set(CPACK_PACKAGE_VENDOR "Krais")
include(CPack)