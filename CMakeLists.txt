cmake_minimum_required(VERSION 3.5)

project(TestWork LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(TestWork
  main.cpp
  verylonginteger.cpp
  verylonginteger.h
  int64filereader.cpp
  int64filereader.h
  int64queue.cpp
  int64queue.h
  int64worker.cpp
  int64worker.h
)
target_link_libraries(TestWork Qt5::Core)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  TestWorks_tests
  verylonginteger_tests.cpp
  verylonginteger.cpp
  verylonginteger.h
)

target_link_libraries(
  TestWorks_tests
  gtest_main
  Qt5::Core
)
