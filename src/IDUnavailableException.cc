#include "IDUnavailableException.h"
const char *IDUnavailableException::what() const noexcept {
  return message.c_str();
}

IDUnavailableException::IDUnavailableException(std::string message)
    : message(message) {}
