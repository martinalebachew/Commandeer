# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.25)
project(commandeer C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED COMPONENTS system)
set(used_libs ${Boost_SYSTEM_LIBRARY})

file(GLOB SOURCES src/*.cpp src/*/*.cpp)
add_executable(commandeer ${SOURCES})

target_link_libraries(commandeer ${used_libs})
target_precompile_headers(commandeer
  PUBLIC src/commandeer.hpp 
  PRIVATE <iostream> <vector> <fstream>
  PRIVATE <Windows.h> <tlhelp32.h>
  PRIVATE <boost/beast/core.hpp> <boost/beast/websocket.hpp> <boost/asio/connect.hpp> <boost/asio/ip/tcp.hpp>
  PRIVATE <curl/curl.h> <json/json.hpp>
)