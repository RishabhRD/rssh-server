#include "IDAllocator.h"
#include "Server.h"
#include "Client.h"
#include <asio.hpp>
#include <memory>
using asio::ip::tcp;
class ClientListener : public std::enable_shared_from_this<ClientListener> {
  asio::io_context &context;
  tcp::acceptor acceptor;
  Server::ptr server;
  int listeningPort;

public:
  typedef std::shared_ptr<ClientListener> ptr;
  void startListening();
  void close();
  static ptr create(asio::io_context &context, Server::ptr server);

private:
  void onNewClientAdded(Client::ptr newClient, const std::error_code& error);
  ClientListener(asio::io_context &context, Server::ptr server);
};
