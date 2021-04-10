#include <iostream>
#include <IDAllocator.h>
#include <Message.h>
IDAllocator IDAllocator::defaultAllocator = IDAllocator();
int main() {

  try {
    std::byte raw[2*sizeof(std::uint32_t)+sizeof(std::uint8_t)];
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
    auto data = msg.getData();
  } catch (MessageParsingException e) {
    std::cout << e.what() << std::endl;
    /* throw e; */
  }
}
