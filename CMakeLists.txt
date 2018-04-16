# setup project
cmake_minimum_required(VERSION 3.9)
project(bombe_hermann C)

set(CMAKE_C_STANDARD 11)

# setup files
include_directories(.)
include_directories(platforms/common)

if (WIN32)
    include_directories(platforms/windows)
    set(PLATFORM_SPECIFIC_FILES
            platforms/windows/socket_server.c platforms/windows/socket_server.h)
else()
    include_directories(platforms/posix)
    set(PLATFORM_SPECIFIC_FILES
            platforms/posix/socket.h
            platforms/posix/socket_client.c
            platforms/posix/socket_server.c)
endif(WIN32)

# build an executable
add_executable(${PROJECT_NAME}
        ${PLATFORM_SPECIFIC_FILES}
        platforms/common/socket.h
        bomb_party_v4.png
        bomberman.h
        client.c
        client.h
        client_actions.c
        client_actions.h
        display.c
        display.h
        err.h
        game.c
        game.h
        main.c
        main.h
        map.c
        map.h
        server.c
        server.h
        server_state.c
        server_state.h)


# include deps
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})