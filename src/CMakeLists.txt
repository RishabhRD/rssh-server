add_executable(rssh-server
  ListenerMessage.cc
  ClientDatabase.cc
  Server.cc
  ServerListener.cc
  Client.cc
  ClientListener.cc
  InvalidMessageCastException.cc
  CloseMessage.cc
  NewMessage.cc
  DataMessage.cc
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
