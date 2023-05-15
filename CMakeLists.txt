# CMakeLists.txt
# (C) Martin Alebachew, 2023

cmake_minimum_required(VERSION 3.26)
project(commandeer C CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file(GLOB SOURCES src/*.cpp src/*/*.cpp)
add_executable(commandeer ${SOURCES})

include_directories(${Boost_INCLUDE_DIRS})
find_package(Boost REQUIRED)
target_link_libraries(commandeer PRIVATE ${Boost_SYSTEM_LIBRARY})

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(commandeer PRIVATE nlohmann_json::nlohmann_json)

find_package(CURL CONFIG REQUIRED)
target_link_libraries(commandeer PRIVATE CURL::libcurl)

target_precompile_headers(commandeer
  PUBLIC src/commandeer.hpp 
  PRIVATE <iostream> <vector> <fstream>
  PRIVATE <Windows.h> <tlhelp32.h>
  PRIVATE <curl/curl.h> <nlohmann/json.hpp>
  PRIVATE <boost/beast/core.hpp> <boost/beast/websocket.hpp> <boost/asio/connect.hpp> <boost/asio/ip/tcp.hpp>
)