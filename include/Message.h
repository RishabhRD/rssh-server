#pragma once
#include "MessageParsingException.h"
#include "MessageType.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

class Message {
protected:
  std::uint32_t id;
  MessageType type;
  std::uint32_t length;
  std::vector<std::byte> data;

public:
  Message(MessageType type);
  MessageType getType() const noexcept;
  void setType(MessageType type) noexcept;
  void setId(std::uint32_t id) noexcept;
  std::uint32_t getId() const noexcept;
  template <typename Iter> void fillData(Iter begin, Iter end) {
    data.clear();
    std::copy(begin, end, std::back_inserter(data));
    length = data.size();
  }
  std::vector<std::byte> getData() const noexcept;
  std::uint32_t getLength() const noexcept;
  std::vector<std::byte> serialize() const noexcept;

  // TODO: confirm is a random access iterator and contiguous in memory
  template <typename Iter> static Message deserialize(Iter begin, Iter end) {
    const std::byte *rawPtr = &(*begin);
    const int size = end - begin;
    const int dataSize = size - (2 * sizeof(uint32_t) + sizeof(uint8_t));
    int current = 0;
    Message msg(MessageType::DATA);
    std::memcpy(&msg.id, rawPtr + current, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    uint8_t mt;
    std::memcpy(&mt, rawPtr + current, sizeof(std::uint8_t));
    current += sizeof(std::uint8_t);
    MessageType messageType = convertIntegerToMessageType(mt);
    msg.setType(messageType);
    std::memcpy(&msg.length, rawPtr + current, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    if (msg.length != dataSize) {
      std::string message = "Parsing Exception: MessageLength(";
      message += std::to_string(msg.length);
      message += ") doesn't match the data length(";
      message += std::to_string(dataSize) + ")";
      throw MessageParsingException(message);
    }
    std::copy_n(rawPtr + current, dataSize, std::back_inserter(msg.data));
    return msg;
  }

};
