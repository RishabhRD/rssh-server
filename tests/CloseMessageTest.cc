#include <catch2/catch.hpp>
#include "CloseMessage.h"
#include "defines.h"

tc("On initilization, CloseMessage should have message type CLOSE"){
  CloseMessage closeMessage;
  req(closeMessage.getType() == MessageType::CLOSE);
  req(closeMessage.getLength() == 0);
}
