#include "Server.h"

Server::ptr Server::create(asio::io_context &context) {
  return ptr(new Server(context));
}

Server::Server(asio::io_context &context) : context(context), socket(context) {
}

tcp::socket& Server::getSocket(){
  return socket;
}

void Server::start(){
}
