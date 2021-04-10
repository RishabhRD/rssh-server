#include <catch2/catch.hpp>
#include "NewMessage.h"
#include "defines.h"

tc("On initilization, NewMessage should have message type NEW"){
  NewMessage newMessage;
  req(newMessage.getType() == MessageType::NEW);
}
