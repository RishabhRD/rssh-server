#include <catch2/catch.hpp>
#include "ListenerMessage.h"
#include "defines.h"

tc("On initilization, ListenerMessage should have message type LISTEN"){
  ListenerMessage listenMessage;
  req(listenMessage.getType() == MessageType::LISTEN);
  req(listenMessage.getId() == 0);
  req(listenMessage.getLength() == sizeof(std::uint32_t));
  req(listenMessage.getPort() == 0);
}

tc("Construction of message from message of proper listen type should work fine"){
  Message msg(MessageType::LISTEN);
  std::uint32_t port = 3458;
  std::byte* rawBytes = (std::byte*)&port;
  msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
  ListenerMessage cmsg(msg);
  req(cmsg.getType() == MessageType::LISTEN);
  req(cmsg.getId() == 0);
  req(cmsg.getLength() == sizeof(std::uint32_t));
  req(cmsg.getPort() == 3458);
}

tc("Construction of ListenerMessage with non-listen Message should throw exception"){
  sec("When type is not LISTEN"){
    Message msg(MessageType::DATA);
    reqThrows(ListenerMessage(msg));
  }
  sec("When length is not sizeof(std::uint32_t)"){
    Message msg(MessageType::LISTEN);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    reqThrows(ListenerMessage(msg));
  }
  sec("When port is greater than 65535"){
    Message msg(MessageType::LISTEN);
    std::uint32_t port = 1234567;
    std::byte* rawBytes = (std::byte*)&port;
    msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
    msg.setId(3);
    reqThrows(ListenerMessage(msg));
  }
  sec("When id is not 0"){
    Message msg(MessageType::LISTEN);
    std::uint32_t port = 3264;
    std::byte* rawBytes = (std::byte*)&port;
    msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
    msg.setId(3);
    reqThrows(ListenerMessage(msg));
  }
}

tc("Assignment to ListenerMessage with proper Message should work fine"){
  Message msg(MessageType::LISTEN);
  std::uint32_t port = 3458;
  std::byte* rawBytes = (std::byte*)&port;
  msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
  ListenerMessage cmsg;
  cmsg = msg;
  req(cmsg.getType() == MessageType::LISTEN);
  req(cmsg.getId() == 0);
  req(cmsg.getLength() == 0);
  req(cmsg.getPort() == 3458);
}

tc("Assignment to ListenerMessage with non-listen Message should throw exception"){
  sec("When type is not LISTEN"){
    Message msg(MessageType::DATA);
    ListenerMessage cmsg;
    reqThrows(cmsg = msg);
  }
  sec("When length is not equal to sizoe(std::uint32_t)"){
    Message msg(MessageType::LISTEN);
    std::vector<std::byte> data;
    data.push_back(std::byte('a'));
    msg.fillData(data.begin(), data.end());
    ListenerMessage cmsg;
    reqThrows(cmsg = msg);
  }
  sec("When port is greater than 65535"){
    Message msg(MessageType::LISTEN);
    std::uint32_t port = 1234567;
    std::byte* rawBytes = (std::byte*)&port;
    msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
    ListenerMessage cmsg;
    reqThrows(cmsg = msg);
  }
  sec("When id is not zero"){
    Message msg(MessageType::LISTEN);
    std::uint32_t port = 3264;
    std::byte* rawBytes = (std::byte*)&port;
    msg.fillData(rawBytes, rawBytes + sizeof(std::uint32_t));
    msg.setId(3);
    ListenerMessage cmsg;
    reqThrows(cmsg = msg);
  }
}
