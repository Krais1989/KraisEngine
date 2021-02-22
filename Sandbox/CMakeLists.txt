
file(GLOB_RECURSE SANDBOX_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.cpp)
message(KE_SOURCES:  ${KE_SOURCES})
file(GLOB_RECURSE SANDBOX_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/*.h)
message(KE_HEADERS:  ${KE_HEADERS})

add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

# Добавить папку с ресурсами
#file(GLOB_RECURSE SANDBOX_ASSETS ${CMAKE_CURRENT_SOURCE_DIR}/Assets/*)
#message(SANDBOX_ASSETS:  ${SANDBOX_ASSETS})
#target_include_directories(Sandbox PUBLIC SANDBOX_ASSETS)

set_property(TARGET Sandbox PROPERTY CXX_STANDARD 17)

target_link_libraries(Sandbox PRIVATE KraisEngine)
KE_IMPORT_ALL_SHARED_DLLS(Sandbox)

# Решает проблему копирования библиотеки KraisEngine в Sandbox при билде из IDE
add_dependencies(Sandbox KraisEngine)

message(PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR})
message(PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR})

#KECopyDLL(fmod Sandbox)

add_custom_command(TARGET Sandbox PRE_BUILD COMMAND xcopy /i /e /s /y /f "$(ProjectDir)Assets" "$(OutDir)Assets")