#pragma once
#include <cstdint>
enum class MessageType{
  DATA,
  NEW,
  CLOSE,
  LISTEN
};

std::uint8_t convertMessageTypeToInteger(MessageType type);

MessageType convertIntegerToMessageType(std::uint8_t type);
