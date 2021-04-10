#include <catch2/catch.hpp>
#include "CloseMessage.h"
#include "defines.h"

tc("On initilization, CloseMessage should have message type CLOSE"){
  CloseMessage closeMessage;
  req(closeMessage.getType() == MessageType::CLOSE);
  req(closeMessage.getLength() == 0);
}

tc("Construction of object with message of closed syntax should work fine"){
  Message msg(MessageType::CLOSE);
  msg.setId(3);
  CloseMessage cmsg(msg);
  req(cmsg.getType() == MessageType::CLOSE);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 0);
}

tc("Construction of CloseMessage with non-close Message should throw exception"){
  sec("When type is not CLOSE"){
    Message msg(MessageType::DATA);
    msg.setId(3);
    reqThrows(CloseMessage(msg));
  }
  sec("When length is greater than 0"){
    Message msg(MessageType::CLOSE);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    msg.setId(3);
    reqThrows(CloseMessage(msg));
  }
}

tc("Assignment to CloseMessage with proper Message should work fine"){
  Message msg(MessageType::CLOSE);
  msg.setId(3);
  CloseMessage cmsg;
  cmsg = msg;
  req(cmsg.getType() == MessageType::CLOSE);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 0);
}

tc("Assignment to CloseMessage with non-close Message should throw exception"){
  sec("When type is not CLOSE"){
    Message msg(MessageType::DATA);
    msg.setId(3);
    CloseMessage cmsg;
    reqThrows(cmsg = msg);
  }
  sec("When length is greater than 0"){
    Message msg(MessageType::CLOSE);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    msg.setId(3);
    CloseMessage cmsg;
    reqThrows(cmsg = msg);
  }
}
