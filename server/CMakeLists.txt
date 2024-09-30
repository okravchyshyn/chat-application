add_executable(server server.cpp)

if(UNIX)
    target_link_libraries(server pthread)
endif()

