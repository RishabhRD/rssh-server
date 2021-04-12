#include <asio.hpp>
#include "Server.h"

using asio::ip::tcp;

class ServerListener{
  asio::io_context& context;
  tcp::acceptor acceptor;
  public:
  ServerListener(asio::io_context& context, int port);
  void startListening() ;
  void close();
  private:
  void onNewServerConnection(Server::ptr newServer, const std::error_code& error);
};
