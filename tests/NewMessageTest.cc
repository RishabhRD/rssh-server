#include <catch2/catch.hpp>
#include "NewMessage.h"
#include "defines.h"

tc("On initilization, NewMessage should have message type NEW"){
  NewMessage newMessage;
  req(newMessage.getType() == MessageType::NEW);
  req(newMessage.getLength() == 0);
}

tc("Construction of message from message of proper new type should work fine"){
  Message msg(MessageType::NEW);
  msg.setId(3);
  NewMessage cmsg(msg);
  req(cmsg.getType() == MessageType::NEW);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 0);
}

tc("Construction of NewMessage with non-new Message should throw exception"){
  sec("When type is not NEW"){
    Message msg(MessageType::DATA);
    msg.setId(3);
    reqThrows(NewMessage(msg));
  }
  sec("When length is greater than 0"){
    Message msg(MessageType::NEW);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    msg.setId(3);
    reqThrows(NewMessage(msg));
  }
}

tc("Assignment to NewMessage with proper Message should work fine"){
  Message msg(MessageType::NEW);
  msg.setId(3);
  NewMessage cmsg;
  cmsg = msg;
  req(cmsg.getType() == MessageType::NEW);
  req(cmsg.getId() == 3);
  req(cmsg.getLength() == 0);
}

tc("Assignment to NewMessage with non-new Message should throw exception"){
  sec("When type is not NEW"){
    Message msg(MessageType::DATA);
    msg.setId(3);
    NewMessage cmsg;
    reqThrows(cmsg = msg);
  }
  sec("When length is greater than 0"){
    Message msg(MessageType::NEW);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    msg.setId(3);
    NewMessage cmsg;
    reqThrows(cmsg = msg);
  }
}
