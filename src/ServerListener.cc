#include "ServerListener.h"
#include "ClientListener.h"
#include "ListenerMessage.h"

ServerListener::ServerListener(asio::io_context &context, int port)
    : context(context), acceptor(context, tcp::endpoint(tcp::v4(), port)) {}

void ServerListener::startListening() {
  Server::ptr newServer = Server::create(context);
  auto acceptFp =
      std::bind(&ServerListener::onNewServerConnection, shared_from_this(),
                newServer, std::placeholders::_1);
  acceptor.async_accept(newServer->getSocket(), acceptFp);
}

void ServerListener::close() {
  // TODO: handle error
  acceptor.close();
}

void ServerListener::onNewServerConnection(Server::ptr newServer,
                                           const std::error_code &error) {
  if (!error) {
    auto newClientListener =
        ClientListener::create(context, newServer->shared_from_this());
    newServer->scheduleRead(newClientListener);
    newClientListener->startListening();
  }
  startListening();
}

ServerListener::ptr ServerListener::create(asio::io_context &context,
                                           int port) {
  return ptr(new ServerListener(context, port));
}
