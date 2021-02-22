add_library(fmod SHARED IMPORTED GLOBAL)

message(${CMAKE_CURRENT_SOURCE_DIR}/inc)

set_target_properties(fmod PROPERTIES 
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/inc
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL.dll
    IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL_vc.lib)



#add_library(fmod INTERFACE)
#add_library(fmod_lib SHARED IMPORTED)
#
#set_target_properties(fmod_lib PROPERTIES 
#    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/inc
#    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL_vc.dll
#    IMPORTED_IMPLIB ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL_vc.lib)
#
#target_link_libraries(fmod INTERFACE fmod_lib)
#target_include_directories(fmod INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)




#add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL_vc.dll ${CMAKE_CURRENT_SOURCE_DIR}/lib/x64/fmodL_vc.lib)
#add_custom_target(fmod_target ALL SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#add_custom_command(TARGET fmod_target
#    POST_BUILD
#    COMMAND "HEY"
#    VERBATIM
#)

#target_sources(fmod_target PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#target_include_directories(fmod_target INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
#target_link_libraries(fmod_target INTERFACE fmod_lib)
