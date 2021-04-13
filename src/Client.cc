#include "Client.h"
#include <asio.hpp>

Client::Client(asio::io_context &context, Server::ptr server, int id, IDAllocator& allocator)
    : context(context), socket(context), server(server), id(id),
      readBuffer(1024), allocator(allocator) {}

Client::ptr Client::create(asio::io_context &context, Server::ptr server,
                           int id, IDAllocator& allocaotor) {
  return ptr(new Client(context, server, id, allocaotor));
}

void Client::write(const Message &msg) {
  auto data = msg.getData();
  asio::async_write(socket, asio::buffer(data), [](auto c1, auto c2) {});
}

std::uint32_t Client::getId() const noexcept { return id; }

tcp::socket &Client::getSocket() noexcept { return socket; }

void Client::scheduleRead() {
  socket.async_read_some(
      asio::buffer(readBuffer),
      [this](auto error, auto size) { handleRead(error, size); });
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

void Client::handleConenctionClose() { socket.close(); 
  server->removeClient(id);
}
