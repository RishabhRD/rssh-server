#include "Message.h"

class ListenerMessage : public Message{
  public:
    ListenerMessage();
    ListenerMessage(Message&& msg);
    ListenerMessage(const Message& msg);
    void setType(MessageType type) noexcept = delete;
    void setId(MessageType) noexcept = delete;
    template <typename Iter> void fillData(Iter begin, Iter end) = delete;
    void operator=(const Message& msg);
    void operator=(Message&& msg);
    void setPort(std::uint32_t port);
    std::uint32_t getPort() const noexcept;
};
