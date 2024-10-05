add_executable(client client.cpp)

set_target_properties(client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

if(UNIX)
    target_link_libraries(client pthread)
endif()

