#include "Message.h"

class DataMessage : public Message{
  public:
  DataMessage();
  void setType(MessageType type) = delete;
  DataMessage(Message&& msg);
  DataMessage(const Message& msg);
  void operator=(const Message& msg);
  void operator=(Message&& msg);
};
