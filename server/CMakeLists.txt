add_executable(server server.cpp)

set_target_properties(server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

if(UNIX)
    target_link_libraries(server pthread)
endif()

