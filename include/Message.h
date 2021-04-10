#include "MessageType.h"
#include <cstddef>
#include <cstdint>
#include <vector>
class Message {
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
  template<typename Iter>
  void fillData(Iter begin, Iter end);
  std::vector<std::byte> getData();
  std::uint32_t getLength() noexcept;
  std::vector<std::byte> serialize() const noexcept;
  template<typename Iter>
  static Message deserialize(Iter begin, Iter end);
};
