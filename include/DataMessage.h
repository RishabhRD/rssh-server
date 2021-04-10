#include "Message.h"

class DataMessage : public Message{
  public:
  DataMessage();
  void setType(MessageType type) = delete;
};
