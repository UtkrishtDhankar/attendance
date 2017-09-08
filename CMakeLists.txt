cmake_minimum_required(VERSION 3.8)
project(attendance)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

set(EXEC_SRC src/main.cpp)
set(SRCS src/Student.cpp src/StudentContainer.cpp include/StudentContainer.hpp)

set(TEST_MAIN tests/tests.cpp)
set(TEST_SRCS tests/Student_test.cpp tests/StudentContainer_test.cpp)

add_executable(attendance ${SRCS} ${EXEC_SRC})
add_executable(tests ${SRCS} ${TEST_SRCS} ${TEST_MAIN})
