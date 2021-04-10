#include "Message.h"

class NewMessage : public Message{
  public:
    NewMessage();
    void setType(MessageType type) noexcept = delete;
    template <typename Iter> void fillData(Iter begin, Iter end) = delete;
};
