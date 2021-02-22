
define_property(GLOBAL PROPERTY KE_IMPORTED_TARGETS
	BRIEF_DOCS "List of imported shared libs targets"
	FULL_DOCS "List of imported shared libs targets")
set_property(GLOBAL PROPERTY KE_IMPORTED_TARGETS "")

# Инициирует SHARED IMPORTED библиотеку в глобальном скоупе (не копирует dll)
macro(ke_import_shared dest_target import_target import_path implib_path inc_path)
	add_library(${import_target} SHARED IMPORTED GLOBAL)

	set_target_properties(${import_target} PROPERTIES 
		INTERFACE_INCLUDE_DIRECTORIES ${inc_path}
		IMPORTED_LOCATION ${import_path}
		IMPORTED_IMPLIB ${implib_path})

	target_link_libraries(${dest_target} PUBLIC ${import_target})
	ke_add_import_shared(${import_target})
endmacro(ke_import_shared)


# Регистрирует имя SHARED IMPORTED таргета (для копирования DLL)
macro(ke_add_import_shared source_target)
	message("ke_add_import_shared: " ${source_target})
	set_property(GLOBAL APPEND PROPERTY KE_IMPORTED_TARGETS ${source_target})
endmacro(ke_add_import_shared)


# Создаёт POST_BUILD команду для копирования DLL из IMPORTED_LOCATION
macro(ke_import_shared_dll source_target destination_target)
	message("TEST")
	message(${lib_location} " ==> " ${destination_target})
	#message(">>> copy from ${source_target} to ${destination_target}: ${lib_location}")	
	get_target_property(lib_location ${source_target} IMPORTED_LOCATION)	
	
	add_custom_command(
		TARGET ${destination_target} 
		POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			${lib_location}
			$<TARGET_FILE_DIR:${destination_target}>
	)
endmacro(ke_import_shared_dll)

# Вызывает ke_import_shared_dll для KE_IMPORTED_TARGETS
macro(ke_import_all_shared_dlls destination_target)
	get_property(import_targets GLOBAL PROPERTY KE_IMPORTED_TARGETS)
	message(">>> ke_import_all_shared_dlls to ${destination_target}, targets: ${import_targets}")
	foreach(source_target ${import_targets})
		message(ke_import_all_shared_dlls ${source_target})
		ke_import_shared_dll(${source_target} ${destination_target})
	endforeach()
endmacro(ke_import_all_shared_dlls)