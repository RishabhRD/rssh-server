#include "InvalidMessageCastException.h"

const char *InvalidMessageCastException::what() const noexcept {
  return message.c_str();
}

InvalidMessageCastException::InvalidMessageCastException(std::string msg)
    : message(msg) {}
