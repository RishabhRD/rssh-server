#include "Server.h"
#include "Client.h"
#include "ClientListener.h"
#include "CloseMessage.h"
#include "NewMessage.h"
#include <asio/error.hpp>
#include <functional>
#include <iostream>

Server::ptr Server::create(asio::io_context &context) {
  return ptr(new Server(context));
}

Server::Server(asio::io_context &context)
    : context(context), socket(context), readBuffer(1024) {}

tcp::socket &Server::getSocket() { return socket; }

void Server::write(const Message &msg) {
  auto data = msg.serialize();
  try {
    asio::write(socket, asio::buffer(data));
  } catch (...) {
  }
}

void Server::scheduleReadId() {
  auto handleReadFp = std::bind(&Server::handleReadId, shared_from_this(),
                                std::placeholders::_1, std::placeholders::_2);
  asio::async_read(socket, asio::buffer(&id, sizeof(id)), handleReadFp);
}

void Server::handleReadId(std::error_code code, std::size_t readSize) {
  if (code == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  scheduleReadType();
}

void Server::scheduleReadType() {
  auto handleReadFp = std::bind(&Server::handleReadType, shared_from_this(),
                                std::placeholders::_1, std::placeholders::_2);
  asio::async_read(socket, asio::buffer(&type, sizeof(type)), handleReadFp);
}

void Server::handleReadType(std::error_code code, std::size_t readSize) {
  if (code == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  scheduleReadLength();
}

void Server::scheduleReadLength() {
  auto handleReadFp = std::bind(&Server::handleReadLength, shared_from_this(),
                                std::placeholders::_1, std::placeholders::_2);
  asio::async_read(socket, asio::buffer(&length, sizeof(length)), handleReadFp);
}

void Server::handleReadLength(std::error_code code, std::size_t readSize) {
  if (length > 0) {
    scheduleReadData();
  } else {
    Message msg(convertIntegerToMessageType(type));
    msg.setId(id);
    if (msg.getType() == MessageType::CLOSE) {
      // TODO: handle client disconnection
      handleConenctionClose();
      scheduleReadId();
      return;
    } else {
      scheduleReadId();
    }
  }
}

void Server::scheduleReadData() {
  auto handleReadFp = std::bind(&Server::handleReadData, shared_from_this(),
                                std::placeholders::_1, std::placeholders::_2);
  asio::async_read(socket, asio::buffer(readBuffer, length), handleReadFp);
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
  std::shared_ptr<Client> client = clientDB.getClientFromId(msg.getId()).lock();
  client->write(msg);
}

void Server::handleConenctionClose() {
  clientDB.removeAll();
  listener.lock()->close();
}

void Server::scheduleRead(std::weak_ptr<ClientListener> listener) {
  this->listener = listener;
  scheduleReadId();
}

void Server::registerClient(std::uint32_t id, std::weak_ptr<Client> client) {
  clientDB.registerClient(id, client);
  NewMessage clientAddedMessage;
  clientAddedMessage.setId(id);
  write(clientAddedMessage);
}

void Server::removeClient(std::uint32_t id) {
  clientDB.removeClient(id);
  CloseMessage clientCloseMessage;
  clientCloseMessage.setId(id);
  write(clientCloseMessage);
}
