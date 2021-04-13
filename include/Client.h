#pragma once
#include "Server.h"
#include <asio.hpp>
#include <memory>
class Client {
public:
  typedef std::shared_ptr<Client> ptr;
  static ptr create(asio::io_context &context, Server::ptr server, int id);
  void write(const Message &msg);
  tcp::socket &getSocket();
  std::uint32_t getId() const noexcept;
  void start();
};
