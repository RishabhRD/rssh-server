#pragma once
#include <Message.h>
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class Server : public std::enable_shared_from_this<Server>{
  tcp::socket socket;
  asio::io_context& context;
  public:
  typedef std::shared_ptr<Server> ptr;
  static ptr create(asio::io_context& context);
  tcp::socket& getSocket();
  void start();
  void write(const Message& msg) const;
  private:
  Server(asio::io_context& context);
  void onRead();
};
