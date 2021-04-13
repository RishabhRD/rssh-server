#include "Server.h"
#include "NewMessage.h"
#include "CloseMessage.h"
#include "Client.h"
#include "ClienListener.h"
#include "ClientDatabase.h"
#include <asio/error.hpp>

Server::ptr Server::create(asio::io_context &context) {
  return ptr(new Server(context));
}

Server::Server(asio::io_context &context)
    : context(context), socket(context), readBuffer(1024) {}

tcp::socket &Server::getSocket() { return socket; }

void Server::write(const Message &msg) const {
  auto data = msg.serialize();
  // TODO: decide if anything should be done on write
  asio::async_write(socket, asio::buffer(data), [](auto c1, auto c2) {});
}

void Server::scheduleReadId() {
  asio::async_read(socket, asio::buffer(&id, sizeof(id)),
                   [this](auto errorCode, auto readSize) {
                     handleReadId(errorCode, readSize);
                   });
}

void Server::handleReadId(std::error_code code, std::size_t readSize) {
  if (code == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  scheduleReadType();
}

void Server::scheduleReadType() {
  asio::async_read(socket, asio::buffer(&type, sizeof(type)),
                   [this](auto errorCode, auto readSize) {
                     handleReadType(errorCode, readSize);
                   });
}

void Server::handleReadType(std::error_code code, std::size_t readSize) {
  if (code == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  scheduleReadLength();
}

void Server::scheduleReadLength() {
  asio::async_read(socket, asio::buffer(&type, sizeof(type)),
                   [this](auto errorCode, auto readSize) {
                     handleReadLength(errorCode, readSize);
                   });
}

void Server::handleReadLength(std::error_code code, std::size_t readSize) {
  if (length > 0) {
    scheduleReadData();
  } else {
    Message msg(convertIntegerToMessageType(type));
    msg.setId(id);
    if (msg.getType() == MessageType::CLOSE) {
      handleConenctionClose();
      return;
    }
  }
}

void Server::scheduleReadData() {
  socket.async_read_some(
      asio::buffer(readBuffer),
      [this](auto error, auto size) { handleReadData(error, size); });
}

void Server::handleReadData(std::error_code code, std::size_t readSize) {
  if (code == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  Message msg(convertIntegerToMessageType(type));
  msg.setId(id);
  msg.fillData(readBuffer.begin(), readBuffer.begin() + readSize);
  sendMessageToClient(msg);
  scheduleReadId();
}

void Server::sendMessageToClient(const Message &msg) {
  auto &db = ClientDatabase::getDefault();
  std::shared_ptr<Client> client = db.getClientFromId(msg.getId()).lock();
  client->write(msg);
}

void Server::handleConenctionClose() { socket.close(); }

void Server::scheduleRead() { scheduleReadId(); }

void Server::registerClient(std::uint32_t id, std::weak_ptr<Client> client){
  ClientDatabase::getDefault().registerClient(id, client);
  NewMessage clientAddedMessage;
  clientAddedMessage.setId(id);
  write(clientAddedMessage);
}

void Server::removeClient(std::uint32_t id){
  ClientDatabase::getDefault().removeClient(id);
  CloseMessage clientCloseMessage;
  clientCloseMessage.setId(id);
  write(clientCloseMessage);
}
