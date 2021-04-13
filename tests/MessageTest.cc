#include "Message.h"
#include "defines.h"
#include <catch2/catch.hpp>
#include <cstring>
#include <iostream>

tc("Newly created message is of 0 length and 0 id") {
  Message message(MessageType::DATA);
  req(message.getLength() == 0);
  req(message.getId() == 0);
}

tc("Setting the message parameters return the same value") {
  Message message(MessageType::DATA);
  sec("Setting message type") {
    message.setType(MessageType::NEW);
    req(message.getType() == MessageType::NEW);
    message.setType(MessageType::CLOSE);
    req(message.getType() == MessageType::CLOSE);
  }
  sec("Setting the client ID in message") {
    message.setType(MessageType::DATA);
    message.setId(2);
    req(message.getId() == 2);
    message.setId(3);
    req(message.getId() == 3);
  }
}

tc("Filling data would properly set length") {
  Message message(MessageType::DATA);
  std::vector<std::byte> data;
  data.push_back(std::byte('a'));
  data.push_back(std::byte('a'));
  data.push_back(std::byte('b'));
  data.push_back(std::byte('b'));
  message.fillData(data.begin(), data.end());
  req(message.getLength() == 4);
  data.clear();
  data.push_back(std::byte('a'));
  data.push_back(std::byte('b'));
  data.push_back(std::byte('b'));
  message.fillData(data.begin(), data.end());
  req(message.getLength() == 3);
}

tc("Serializing the message should put bytes in correct order") {
  Message message(MessageType::CLOSE);
  message.setId(2);
  std::vector<std::byte> data;
  data.push_back(std::byte('a'));
  data.push_back(std::byte('a'));
  data.push_back(std::byte('b'));
  data.push_back(std::byte('b'));
  message.fillData(data.begin(), data.end());
  std::uint32_t length;
  std::uint8_t messageType;
  std::uint32_t id;
  auto buffer = message.serialize();
  const std::byte *rawData = buffer.data();
  std::size_t current = 0;
  std::memcpy(&id, (rawData + current), sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  req(id == 2);
  std::memcpy(&messageType, (rawData + current), sizeof(std::uint8_t));
  current += sizeof(std::uint8_t);
  req(MessageType(messageType) == MessageType::CLOSE);
  std::memcpy(&length, (rawData + current), sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  req(length == 4);
  req(*(rawData + current) == std::byte('a'));
  req(*(rawData + current + 1) == std::byte('a'));
  req(*(rawData + current + 2) == std::byte('b'));
  req(*(rawData + current + 3) == std::byte('b'));
}

tc("Message deserialize test: given a stream of bytes produce correct "
   "message") {
  std::byte raw[12];
  std::uint32_t id = 2;
  std::uint8_t type = 2;
  std::uint32_t length = 3;
  std::size_t current = 0;
  std::memcpy((raw + current), &id, sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  std::memcpy((raw + current), (void *)&type, sizeof(std::uint8_t));
  current += sizeof(std::uint8_t);
  std::memcpy((raw + current), (void *)&length, sizeof(std::uint32_t));
  current += sizeof(std::uint32_t);
  std::byte temp = std::byte('a');
  std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
  current += sizeof(std::byte);
  temp = std::byte('b');
  std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
  current += sizeof(std::byte);
  temp = std::byte('c');
  std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
  Message msg = Message::deserialize(raw, raw + 12);
  req(msg.getType() == MessageType::CLOSE);
  req(msg.getId() == 2);
  req(msg.getLength() == 3);
  auto data = msg.getData();
  req(msg.getLength() == data.size());
  req(std::equal(data.begin(), data.end(), raw + 9));
}

tc("Should throw exception on deserializing bad formatted message") {
  sec("Deserializing when message has bad type") {
    std::byte raw[12];
    std::uint32_t id = 2;
    std::uint8_t type = 4;
    std::uint32_t length = 3;
    std::size_t current = 0;
    std::memcpy((raw + current), &id, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    std::memcpy((raw + current), (void *)&type, sizeof(std::uint8_t));
    current += sizeof(std::uint8_t);
    std::memcpy((raw + current), (void *)&length, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    std::byte temp = std::byte('a');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    current += sizeof(std::byte);
    temp = std::byte('b');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    current += sizeof(std::byte);
    temp = std::byte('c');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    REQUIRE_THROWS(Message::deserialize(raw, raw + 12));
  }
  sec("Deserializing when length is bad") {
    std::byte raw[12];
    std::uint32_t id = 3;
    std::uint8_t type = 2;
    std::uint32_t length = 2;
    std::size_t current = 0;
    std::memcpy((raw + current), &id, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    std::memcpy((raw + current), (void *)&type, sizeof(std::uint8_t));
    current += sizeof(std::uint8_t);
    std::memcpy((raw + current), (void *)&length, sizeof(std::uint32_t));
    current += sizeof(std::uint32_t);
    std::byte temp = std::byte('a');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    current += sizeof(std::byte);
    temp = std::byte('b');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    current += sizeof(std::byte);
    temp = std::byte('c');
    std::memcpy((raw + current), (void *)&temp, sizeof(std::byte));
    REQUIRE_THROWS(Message::deserialize(raw, raw + 12));
  }
}
