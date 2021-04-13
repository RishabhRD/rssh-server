#include "NewMessage.h"
#include "InvalidMessageCastException.h"

NewMessage::NewMessage() : Message(MessageType::NEW){
}

NewMessage::NewMessage(Message &&msg) : Message(MessageType::NEW) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to NewMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
}

NewMessage::NewMessage(const Message &msg) : Message(MessageType::NEW) {
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to NewMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
}

void NewMessage::operator=(const Message& msg){
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to NewMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
}

void NewMessage::operator=(Message&& msg){
  if (msg.getType() != MessageType::NEW) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to NewMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to NewMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
}
