enable_testing()
add_executable(unit_test
  MainTest.cc
  IDAllocatorTest.cc
  ../src/IDAllocator.cc
  ../src/IDUnavailableException.cc
  )
target_include_directories(unit_test PUBLIC ../include)
target_link_libraries(unit_test PRIVATE Threads::Threads Catch2::Catch2)
target_compile_features(unit_test PUBLIC cxx_std_17)
include(CTest)
include(Catch)
catch_discover_tests(unit_test)
