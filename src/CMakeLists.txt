add_executable(rssh-server
  Message.cc
  IDAllocator.cc
  IDUnavailableException.cc
  MessageParsingException.cc
  main.cc
  )
target_include_directories(rssh-server PUBLIC ../include)
target_link_libraries(rssh-server PRIVATE Threads::Threads)
target_compile_features(rssh-server PUBLIC cxx_std_17)
install(TARGETS rssh-server RUNTIME DESTINATION bin)
