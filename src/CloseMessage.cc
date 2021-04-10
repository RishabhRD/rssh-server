#include "CloseMessage.h"
#include "InvalidMessageCastException.h"

CloseMessage::CloseMessage() : Message(MessageType::CLOSE) {}

CloseMessage::CloseMessage(Message &&msg) : Message(MessageType::CLOSE) {
  if (msg.getType() != MessageType::CLOSE) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to CloseMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to CloseMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
}

CloseMessage::CloseMessage(const Message &msg) : Message(MessageType::CLOSE) {
  if (msg.getType() != MessageType::CLOSE) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to CloseMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to CloseMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
}

void CloseMessage::operator=(const Message& msg){
  if (msg.getType() != MessageType::CLOSE) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to CloseMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to CloseMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
}

void CloseMessage::operator=(Message&& msg){
  if (msg.getType() != MessageType::CLOSE) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to CloseMessage");
  }
  if (msg.getLength() > 0) {
    throw InvalidMessageCastException(
        "Invalid casting of message with length > 0 to CloseMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
}
