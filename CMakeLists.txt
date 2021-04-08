cmake_minimum_required(VERSION 3.1.0)
project(rssh-server)

enable_testing()

include_directories(include)

file(GLOB_RECURSE src "src/*".cc)

# set (CMAKE_CXX_STANDARD 17)

add_executable(rssh-server ${src})
install(TARGETS rssh-server RUNTIME DESTINATION bin)
find_package(Catch2 REQUIRED)
find_package(Threads REQUIRED)
file(GLOB testfiles "tests/*".cc "src/*".cc)
add_executable(tests ${testfiles})
target_link_libraries(tests PUBLIC Catch2::Catch2 Threads::Threads)

include(CTest)
include(Catch)
catch_discover_tests(tests)

install(TARGETS tests DESTINATION bin)
