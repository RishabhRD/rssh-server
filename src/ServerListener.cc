#include "ServerListener.h"
#include "ClientListener.h"

ServerListener::ServerListener(asio::io_context &context, int port)
    : context(context), acceptor(context, tcp::endpoint(tcp::v4(), port)) {}

void ServerListener::startListening() {
  Server::ptr newServer = Server::create(context);
  acceptor.async_accept(newServer->getSocket(), [this, newServer](auto error) {
    onNewServerConnection(newServer, error);
  });
}

void ServerListener::close() {
  // TODO: handle error
  acceptor.close();
}

void ServerListener::onNewServerConnection(Server::ptr newServer,
                                           const std::error_code &error) {
  if (!error) {
    newServer->scheduleRead();
    auto newClientListener = ClientListener::create(
        context, newServer->shared_from_this());
    newClientListener->startListening();
  }
  startListening();
}
