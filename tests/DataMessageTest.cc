#include <catch2/catch.hpp>
#include "DataMessage.h"
#include "defines.h"

tc("On initilization, DataMessage should have message type DATA"){
  DataMessage dataMessage;
  req(dataMessage.getType() == MessageType::DATA);
}
