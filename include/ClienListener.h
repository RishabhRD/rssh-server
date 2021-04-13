#include "Server.h"
#include "Client.h"
#include "IDAllocator.h"
#include <asio.hpp>
#include <memory>
using asio::ip::tcp;
class ClientListener : public std::enable_shared_from_this<ClientListener>{
  asio::io_context& context;
  tcp::acceptor acceptor;
  IDAllocator& idAllocator;
public:
  typedef std::shared_ptr<ClientListener> ptr;
  void startListening();
  void close();
  static ptr create(asio::io_context& context, Server::ptr server, IDAllocator& allocator);
private:
  void onNewServerConnection(Client::ptr newClient, const std::error_code& error);
  ClientListener(asio::io_context& context, IDAllocator& allocator);
};
