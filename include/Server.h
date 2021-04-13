#pragma once
#include "ClientDatabase.h"
#include <Message.h>
#include <asio.hpp>
#include <memory>

class Client;
using asio::ip::tcp;

class Server : public std::enable_shared_from_this<Server> {
  tcp::socket socket;
  asio::io_context &context;
  std::vector<std::byte> readBuffer;
  std::uint32_t id;
  std::uint8_t type;
  std::uint32_t length;
  ClientDatabase clientDB;

public:
  typedef std::shared_ptr<Server> ptr;
  static ptr create(asio::io_context &context);
  tcp::socket &getSocket();
  void scheduleRead();
  void write(const Message &msg) ;
  void registerClient(std::uint32_t id, std::weak_ptr<Client>);
  void removeClient(std::uint32_t id);

private:
  Server(asio::io_context &context);
  void handleConenctionClose();
  void onRead();
  void scheduleReadId();
  void scheduleReadType();
  void scheduleReadLength();
  void scheduleReadData();
  void handleReadId(std::error_code code, std::size_t readSize);
  void handleReadType(std::error_code code, std::size_t readSize);
  void handleReadLength(std::error_code code, std::size_t readSize);
  void handleReadData(std::error_code code, std::size_t readSize);
  void sendMessageToClient(const Message &msg);
};
