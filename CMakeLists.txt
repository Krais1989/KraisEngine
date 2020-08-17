cmake_minimum_required(VERSION 3.10)
project(KraisEngine LANGUAGES CXX)

#set(CMAKE_SUPPRESS_REGENERATION true)

message(${CMAKE_COMMAND})

if (NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE DEBUG)
endif()
message(CMAKE_BUILD_TYPE>${CMAKE_BUILD_TYPE})

add_subdirectory(vendor/spdlog)
#set_target_properties(spdlog PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/library)

add_subdirectory(KraisEngine)
add_subdirectory(Sandbox)

#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVS")
#	set_target_properties(KraisEngine PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
#endif()

#target_include_directories(KraisEngine PUBLIC "${<PROJECT-NAME>_BINARY_DIR}")