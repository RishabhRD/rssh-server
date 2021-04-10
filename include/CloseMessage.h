#include "Message.h"

class CloseMessage : public Message{
  public:
    CloseMessage();
    CloseMessage(Message&& msg);
    CloseMessage(const Message& msg);
    void setType(MessageType type) noexcept = delete;
    template <typename Iter> void fillData(Iter begin, Iter end) = delete;
    void operator=(const Message& msg);
    void operator=(Message&& msg);
};
