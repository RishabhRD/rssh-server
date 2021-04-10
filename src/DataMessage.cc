#include "DataMessage.h"
#include "InvalidMessageCastException.h"

DataMessage::DataMessage() : Message(MessageType::DATA){
}

DataMessage::DataMessage(Message &&msg) : Message(MessageType::DATA) {
  if (msg.getType() != MessageType::DATA) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to DataMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
}

DataMessage::DataMessage(const Message &msg) : Message(MessageType::DATA) {
  if (msg.getType() != MessageType::DATA) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to DataMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
}

void DataMessage::operator=(const Message& msg){
  if (msg.getType() != MessageType::DATA) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to DataMessage");
  }
  id = msg.getId();
  type = msg.getType();
  length = msg.getLength();
  data = msg.getData();
}

void DataMessage::operator=(Message&& msg){
  if (msg.getType() != MessageType::DATA) {
    throw InvalidMessageCastException(
        "Invalid casting of message type" +
        std::to_string(
            static_cast<std::underlying_type_t<MessageType>>(msg.getType())) +
        " to DataMessage");
  }
  id = std::move(msg.getId());
  type = std::move(msg.getType());
  length = std::move(msg.getLength());
  data = msg.getData();
}
