#include "ClientListener.h"
#include "Client.h"
#include "ListenerMessage.h"

ClientListener::ClientListener(asio::io_context &context, Server::ptr server)
    : context(context), acceptor(context, tcp::endpoint(tcp::v4(), 0)),
      server(server), listeningPort(acceptor.local_endpoint().port()) {
  ListenerMessage listeningMessage;
  listeningMessage.setPort(listeningPort);
  server->write(listeningMessage);
}

void ClientListener::startListening() {
  std::uint32_t id = allocator.allocate();
  Client::ptr newClient = Client::create(context, server, id, allocator);
  acceptor.async_accept(newClient->getSocket(),
                        [this, newClient, id](auto error) {
                          onNewClientConnection(newClient, error);
                        });
}

void ClientListener::onNewClientAdded(Client::ptr newClient,
                                      const std::error_code &error) {
  if (!error) {
    server->registerClient(newClient->getId(), newClient);
    newClient->scheduleRead();
  }
  startListening();
}

void ClientListener::close() { acceptor.close(); }

ClientListener::ptr ClientListener::create(asio::io_context &context,
                                           Server::ptr server) {
  return ptr(new ClientListener(context, server));
}
