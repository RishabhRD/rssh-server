#include "Client.h"
#include "IDAllocator.h"
#include <asio.hpp>
#include <memory>
using asio::ip::tcp;
class ClientListener {
  asio::io_context& context;
  tcp::acceptor acceptor;
  IDAllocator& idAllocator;
public:
  void startListening();
  ClientListener(asio::io_context& context, int port, IDAllocator& allocator);
  void close();
private:
  void onNewServerConnection(Client::ptr newClient, const std::error_code& error);
};
