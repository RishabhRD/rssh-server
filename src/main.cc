#include <iostream>
#include "ServerListener.h"
int main() {
  asio::io_context context;
  ServerListener listener(context, 22222);
  listener.startListening();
  context.run();
}
