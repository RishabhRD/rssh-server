#include <catch2/catch.hpp>
#include "DataMessage.h"
#include "defines.h"

tc("On initilization, DataMessage should have message type DATA"){
  DataMessage dataMessage;
  req(dataMessage.getType() == MessageType::DATA);
}

tc("Construction of message from message of proper data type should work fine"){
  Message msg(MessageType::DATA);
  msg.setId(3);
  std::vector<std::byte> data = {std::byte('a'), std::byte('b')};
  msg.fillData(data.begin(), data.end());
  DataMessage cmsg(msg);
  req(cmsg.getType() == MessageType::DATA);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 2);
  req(cmsg.getData() == data);
}

tc("Construction of DataMessage with non-data Message should throw exception"){
  sec("When type is not DATA"){
    Message msg(MessageType::CLOSE);
    msg.setId(3);
    reqThrows(DataMessage(msg));
  }
}

tc("Assignment to DataMessage with proper Message should work fine"){
  Message msg(MessageType::DATA);
  msg.setId(3);
  std::vector<std::byte> data = {std::byte('a'), std::byte('b')};
  msg.fillData(data.begin(), data.end());
  DataMessage cmsg;
  cmsg = msg;
  req(cmsg.getType() == MessageType::DATA);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 2);
  req(cmsg.getData() == data);
}

tc("Assignment to DataMessage with non-data Message should throw exception"){
  sec("When type is not DATA"){
    Message msg(MessageType::CLOSE);
    msg.setId(3);
    DataMessage cmsg;
    reqThrows(cmsg = msg);
  }
}
