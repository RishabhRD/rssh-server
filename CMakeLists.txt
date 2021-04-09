cmake_minimum_required(VERSION 3.14)
project(rssh-server)

find_package(Threads REQUIRED)

add_subdirectory(src)
if(BUILD_TESTING)
  include(CTest)
  find_package(Catch2 REQUIRED)
  find_package(Threads REQUIRED)
  include(Catch)
  add_subdirectory(tests)
  catch_discover_tests(tests)
endif()

