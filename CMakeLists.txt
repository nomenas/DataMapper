cmake_minimum_required(VERSION 3.10)

project(DataMapper)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)

file(GLOB PROTO_FILES protos/*.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HEADER ${PROTO_FILES})

add_executable(${PROJECT_NAME} ${PROTO_SRC} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROTOBUF_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} protobuf::libprotobuf)