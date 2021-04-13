#include "MessageType.h"
#include "MessageParsingException.h"
#include <string>

std::uint8_t convertMessageTypeToInteger(MessageType type){
  if (type == MessageType::DATA) {
    return 0;
  } else if (type == MessageType::NEW) {
    return 1;
  } else if (type == MessageType::CLOSE) {
    return 2;
  }else{
    return 3;
  }
}

MessageType convertIntegerToMessageType(std::uint8_t mt){
  if (mt < 0 || mt > 3) {
    throw MessageParsingException("Invalid message type: " +
                                  std::to_string(mt));
  }
  if (mt == 0) {
    return MessageType::DATA;
  }
  if (mt == 1) {
    return MessageType::NEW;
  }
  if(mt == 2){
    return MessageType::CLOSE;
  }
  return MessageType::LISTEN;
}
