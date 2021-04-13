#include "NewMessage.h"
#include "InvalidMessageCastException.h"
#include <stdexcept>

NewMessage::NewMessage() : Message(MessageType::NEW) {
  data.reserve(sizeof(std::uint32_t));
}

NewMessage::NewMessage(Message &&msg) : Message(MessageType::NEW) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException("Invalid casting of message with length "
                                      "!= sizeof(std::uint32_t) to NewMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException(
        "Invalid message casting to new message with port greater than 65535");
  }
}

NewMessage::NewMessage(const Message &msg) : Message(MessageType::NEW) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException("Invalid casting of message with length "
                                      "!= sizeof(std::uint32_t) to NewMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException(
        "Invalid message casting to new message with port greater than 65535");
  }
}

void NewMessage::operator=(const Message &msg) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException("Invalid casting of message with length "
                                      "!= sizeof(std::uint32_t) to NewMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException(
        "Invalid message casting to new message with port greater than 65535");
  }
}

void NewMessage::operator=(Message &&msg) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() != sizeof(std::uint32_t)) {
    throw InvalidMessageCastException("Invalid casting of message with length "
                                      "!= sizeof(std::uint32_t) to NewMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
  if (getPort() > 65535) {
    throw InvalidMessageCastException(
        "Invalid message casting to new message with port greater than 65535");
  }
}

void NewMessage::setPort(std::uint32_t port) {
  if (port > 65535) {
    throw std::invalid_argument("Port cannot be greater than 65535");
  }
  std::byte *portRawPointer = (std::byte *)&port;
  std::copy(portRawPointer, portRawPointer + sizeof(std::uint32_t),
            std::begin(data));
}

std::uint32_t NewMessage::getPort() const noexcept {
  const int *portPointer = (int *)data.data();
  return *portPointer;
}
