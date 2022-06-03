cmake_minimum_required(VERSION 3.0.0)
project(hw_1)

set(CMAKE_CXX_STANDARD 20)

set(HW_1_SOURCES
    ${PROJECT_SOURCE_DIR}/i_graph/i_graph.h
    ${PROJECT_SOURCE_DIR}/arc_graph/arc_graph.h
    ${PROJECT_SOURCE_DIR}/arc_graph/arc_graph.cc
    ${PROJECT_SOURCE_DIR}/list_graph/list_graph.h
    ${PROJECT_SOURCE_DIR}/list_graph/list_graph.cc
    ${PROJECT_SOURCE_DIR}/matrix_graph/matrix_graph.h
    ${PROJECT_SOURCE_DIR}/matrix_graph/matrix_graph.cc
    ${PROJECT_SOURCE_DIR}/set_graph/set_graph.h
    ${PROJECT_SOURCE_DIR}/set_graph/set_graph.cc
    ${PROJECT_SOURCE_DIR}/test/test.h
    ${PROJECT_SOURCE_DIR}/test/test.cc)

add_executable(${PROJECT_NAME} main.cc ${HW_1_SOURCES})