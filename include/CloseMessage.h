#include "Message.h"

class CloseMessage : public Message{
  public:
    CloseMessage();
    void setType(MessageType type) noexcept = delete;
    template <typename Iter> void fillData(Iter begin, Iter end) = delete;
};
