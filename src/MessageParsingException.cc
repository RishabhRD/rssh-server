#include "MessageParsingException.h"

MessageParsingException::MessageParsingException(std::string msg) : message(msg){
}

const char *MessageParsingException::what() const noexcept{
  return message.c_str();
}
