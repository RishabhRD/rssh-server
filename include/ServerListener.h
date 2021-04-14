#include "Server.h"
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class ServerListener : public std::enable_shared_from_this<ServerListener> {
  asio::io_context &context;
  tcp::acceptor acceptor;

public:
  typedef std::shared_ptr<ServerListener> ptr;
  void startListening();
  void close();
  static ptr create(asio::io_context& context, int port);

private:
  void onNewServerConnection(Server::ptr newServer,
                             const std::error_code &error);
  ServerListener(asio::io_context &context, int port);
};
