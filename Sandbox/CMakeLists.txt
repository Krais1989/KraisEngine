
# Создаёт для target_name POST-BUILD скрипт копирования динамической библиотеки lib_name
function(add_copy_lib_script target_name lib_name)
	get_target_property(TARGET_BIN_PATH ${target_name} BINARY_DIR)
	get_target_property(LIB_BIN_PATH ${lib_name} BINARY_DIR)

	string(APPEND TARGET_BIN_PATH "/$(Configuration)")
	string(APPEND LIB_BIN_PATH "/$(Configuration)/${lib_name}.dll")

	message(Import: ${LIB_BIN_PATH} => ${TARGET_BIN_PATH})

	add_custom_command(
		TARGET ${target_name} POST_BUILD 
		COMMAND ${CMAKE_COMMAND} -E copy ${LIB_BIN_PATH} ${TARGET_BIN_PATH} )
endfunction()


add_definitions(-DKE_PLATFORM_WINDOWS)
set (SANDBOX_SOURCES 
	src/CSandbox.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})
target_link_libraries(Sandbox PRIVATE KraisEngine)

add_copy_lib_script(Sandbox KraisEngine)