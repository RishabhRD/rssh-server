#include "Message.h"

class NewMessage : public Message{
  public:
    NewMessage();
    NewMessage(Message&& msg);
    NewMessage(const Message& msg);
    void setType(MessageType type) noexcept = delete;
    template <typename Iter> void fillData(Iter begin, Iter end) = delete;
    void operator=(const Message& msg);
    void operator=(Message&& msg);
};
