set (SANDBOX_SOURCES 
	src/CSandbox.cpp
)

set (SANDBOX_HEADERS
	src/CSandbox.h
)

add_executable(Sandbox ${SANDBOX_SOURCES} ${SANDBOX_HEADERS})

set_property(TARGET Sandbox PROPERTY CXX_STANDARD 17)

target_link_libraries(Sandbox PRIVATE KraisEngine)

# Решает проблему копирования библиотеки KraisEngine в Sandbox при билде из IDE
add_dependencies(Sandbox KraisEngine)

#add_copy_lib_script(Sandbox KraisEngine)

message(PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR})
message(PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR})