#include "Message.h"
#include <iterator>

Message::Message(MessageType type) : type(type), id(0), length(0) {}

MessageType Message::getType() const noexcept { return type; }

void Message::setType(MessageType type) noexcept { this->type = type; }

void Message::setId(std::uint32_t id) noexcept { this->id = id; }

std::uint32_t Message::getId() const noexcept { return id; }

std::vector<std::byte> Message::getData() const noexcept { return data; }

std::uint32_t Message::getLength() const noexcept { return length; }

std::vector<std::byte> Message::serialize() const noexcept {
  std::byte
      rawData[data.size() + 2 * sizeof(std::uint32_t) + sizeof(std::uint8_t)];
  int current = 0;
  std::memcpy(rawData + current, &id, sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  auto messageType = getIntegerMessageType();
  std::memcpy(rawData + current, &messageType, sizeof(std::uint8_t));
  current += sizeof(std::uint8_t);
  std::memcpy(rawData + current, &length, sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  std::copy(data.begin(), data.end(), rawData + current);
  std::vector<std::byte> serializedContainer;
  std::copy(rawData, rawData + (sizeof(rawData) / sizeof(std::byte)),
            std::back_inserter(serializedContainer));
  return serializedContainer;
}

std::uint8_t Message::getIntegerMessageType() const noexcept {
  if (type == MessageType::DATA) {
    return 0;
  } else if (type == MessageType::NEW) {
    return 1;
  } else {
    return 2;
  }
}

MessageType Message::getMessageTypeFromInt(std::uint8_t mt) {
  if (mt < 0 || mt > 2) {
    throw MessageParsingException("Invalid message type: " +
                                  std::to_string(mt));
  }
  if (mt == 0) {
    return MessageType::DATA;
  }
  if (mt == 1) {
    return MessageType::NEW;
  }
  return MessageType::CLOSE;
}
