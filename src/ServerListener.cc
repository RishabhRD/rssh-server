#include "ServerListener.h"
#include "ServerDB.h"

ServerListener::ServerListener(uvw::Loop &eventLoop, int listeningPort)
    : eventLoop(eventLoop), listeningPort(listeningPort) {
  tcpHandle = eventLoop.resource<uvw::TCPHandle>();
  auto fp = std::bind(&ServerListener::onListenAccept, this,
                      std::placeholders::_1, std::placeholders::_2);
  tcpHandle->on<uvw::ListenEvent>(fp);
}

void ServerListener::onListenAccept(const uvw::ListenEvent &,
                                    uvw::TCPHandle &srv) {
  auto sshServerHandle = srv.loop().resource<uvw::TCPHandle>();
  auto sshServerEnded =
      std::bind(&ServerListener::onSSHServerConnectionClosed, this,
                std::placeholders::_1, std::placeholders::_2);
  auto sshServerGotData =
      std::bind(&ServerListener::onSSHServerSentData, this,
                std::placeholders::_1, std::placeholders::_2);
  sshServerHandle->on<uvw::EndEvent>(sshServerEnded);
  sshServerHandle->on<uvw::DataEvent>(sshServerGotData);
  createClientListenerSocket(sshServerHandle);
}

std::shared_ptr<uvw::TCPHandle>
ServerListener::createClientListenerSocket(
    std::shared_ptr<uvw::TCPHandle> &sshServerHandle) {
  ServerDB dataBase = ServerDB::getDefault();
}
