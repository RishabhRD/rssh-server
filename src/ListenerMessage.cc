#include "ListenerMessage.h"
#include "InvalidMessageCastException.h"
#include <stdexcept>

ListenerMessage::ListenerMessage() : Message(MessageType::LISTEN) {
  data.reserve(sizeof(std::uint32_t));
}

ListenerMessage::ListenerMessage(Message &&msg) : Message(MessageType::LISTEN) {
  if (msg.getType() != MessageType::LISTEN) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to ListenerMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length "
        "!= sizeof(std::uint32_t) to ListenerMessage");
  }
  id = std::move(msg.getId());
  if (id > 0) {
    throw InvalidMessageCastException(
        "Invalid message casting to listen: id > 0 discovered");
  }
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException("Invalid message casting to listen "
                                      "message with port greater than 65535");
  }
}

ListenerMessage::ListenerMessage(const Message &msg)
    : Message(MessageType::LISTEN) {
  if (msg.getType() != MessageType::LISTEN) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to ListenerMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length "
        "!= sizeof(std::uint32_t) to ListenerMessage");
  }
  id = msg.getId();
  if (id > 0) {
    throw InvalidMessageCastException(
        "Invalid message casting to listen: id > 0 discovered");
  }
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException("Invalid message casting to listen "
                                      "message with port greater than 65535");
  }
}

void ListenerMessage::operator=(const Message &msg) {
  if (msg.getType() != MessageType::LISTEN) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to ListenerMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length "
        "!= sizeof(std::uint32_t) to ListenerMessage");
  }
  id = msg.getId();
  if (id > 0) {
    throw InvalidMessageCastException(
        "Invalid message casting to listen: id > 0 discovered");
  }
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException("Invalid message casting to listen "
                                      "message with port greater than 65535");
  }
}

void ListenerMessage::operator=(Message &&msg) {
  if (msg.getType() != MessageType::LISTEN) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to ListenerMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length "
        "!= sizeof(std::uint32_t) to ListenerMessage");
  }
  id = std::move(msg.getId());
  if (id > 0) {
    throw InvalidMessageCastException(
        "Invalid message casting to listen: id > 0 discovered");
  }
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException("Invalid message casting to listen "
                                      "message with port greater than 65535");
  }
}

void ListenerMessage::setPort(std::uint32_t port) {
  if (port > 65535) {
    throw std::invalid_argument("Port cannot be greater than 65535");
  }
  std::byte *portRawPointer = (std::byte *)&port;
  std::copy(portRawPointer, portRawPointer + sizeof(std::uint32_t),
            std::begin(data));
}

std::uint32_t ListenerMessage::getPort() const noexcept {
  const int *portPointer = (int *)data.data();
  return *portPointer;
}
