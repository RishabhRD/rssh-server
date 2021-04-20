#include <iostream>
#include "Client.h"
#include <asio.hpp>

Client::Client(asio::io_context &context, Server::ptr server, int id,
               IDAllocator &allocator)
    : context(context), socket(context), server(server), id(id),
      readBuffer(1024), allocator(allocator) {}

Client::ptr Client::create(asio::io_context &context, Server::ptr server,
                           int id, IDAllocator &allocaotor) {
  return ptr(new Client(context, server, id, allocaotor));
}

void Client::write(const Message &msg) {
  auto data = msg.getData();
  asio::write(socket, asio::buffer(data));
}

std::uint32_t Client::getId() const noexcept { return id; }

tcp::socket &Client::getSocket() noexcept { return socket; }

void Client::scheduleRead() {
  auto readFp = std::bind(&Client::handleRead, shared_from_this(),
                          std::placeholders::_1, std::placeholders::_2);
  socket.async_read_some(asio::buffer(readBuffer), readFp);
}

void Client::handleRead(std::error_code error, std::size_t readSize) {
  if (error == asio::error::eof) {
    handleConenctionClose();
    return;
  }
  Message readMessage(MessageType::DATA);
  readMessage.setId(id);
  readMessage.fillData(readBuffer.begin(), readBuffer.begin() + readSize);
  server->write(readMessage);
  scheduleRead();
}

void Client::handleConenctionClose() {
  std::cout<<"Closing from client"<<std::endl;
  server->removeClient(id);
}
