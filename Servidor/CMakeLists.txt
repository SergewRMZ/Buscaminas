cmake_minimum_required(VERSION 3.15)

project(Servidor_Buscaminas)
include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

add_executable(server app.cpp 
  presentation/Server.cpp
  presentation/Game/GameBoard.cpp
  presentation/Game/GameController.cpp
  presentation/Services/game-service.cpp)

find_package(nlohmann_json REQUIRED)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json Ws2_32)