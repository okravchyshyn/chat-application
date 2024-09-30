add_executable(client client.cpp)

if(UNIX)
    target_link_libraries(client pthread)
endif()

