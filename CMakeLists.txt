cmake_minimum_required(VERSION 3.7)
project(DimondParkour)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/main.cpp source/Encoding.cpp source/SerializeStream.cpp source/Message.cpp header/Convert.h source/Convert.cpp header/GameLobby.h header/Player.h header/Client.h source/Client.cpp header/ThreadManager.h source/GameLobby.cpp header/Debug.h header/CheckLobby.h source/CheckLobby.cpp)
add_executable(DimondParkour ${SOURCE_FILES} header/GameLobby.h source/Client.cpp header/ThreadManager.h source/GameLobby.cpp header/Debug.h header/CheckLobby.h source/CheckLobby.cpp)
target_link_libraries(DimondParkour pthread)