#include "Client.h"
#include <Message.h>
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class Server{
  public:
  typedef std::shared_ptr<Server> ptr;
  static ptr create(asio::io_context& context);
  tcp::socket& getSocket();
  void start();
  void write(const Message& msg) const;
  void registerClient(std::weak_ptr<Client> client);
  void removeClient(std::weak_ptr<Client> client);
  private:
  void onRead();
};
