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
  Message();
  MessageType getType();
  void setType(MessageType type);
  void setId(std::uint32_t id);
  std::uint32_t getId();
  template <template <typename, typename> class Container,
            typename Allocator = std::allocator<std::byte>>
  void fillData(Container<std::byte, Allocator>,
                Container<std::byte, Allocator>);
  std::uint32_t getLength();
  std::vector<std::byte> serialize();
  template <template <typename, typename> class Container,
            typename Allocator = std::allocator<std::byte>>
  static Message deserialize(Container<std::byte, Allocator>,
                             Container<std::byte, Allocator>);
};
