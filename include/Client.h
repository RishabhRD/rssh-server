#pragma once
#include "Server.h"
#include <asio.hpp>
#include <memory>

using asio::ip::tcp;

class Client : public std::enable_shared_from_this<Client>{
  asio::io_context& context;
  tcp::socket socket;
  Server::ptr server;
  int id;
  std::vector<std::byte> readBuffer;
public:
  typedef std::shared_ptr<Client> ptr;
  static ptr create(asio::io_context &context, Server::ptr server, int id);
  tcp::socket &getSocket() noexcept;
  std::uint32_t getId() const noexcept;
  void scheduleRead();
  void write(const Message& msg) const;
private:
  Client(asio::io_context& context, Server::ptr server, int id);
  void handleRead(std::error_code error, std::size_t readSize);
  void handleConenctionClose();
};
