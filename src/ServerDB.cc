#include "ServerDB.h"

void ServerDB::put(std::shared_ptr<uvw::TCPHandle> clientHandle,
                   std::shared_ptr<uvw::TCPHandle> serverHandle) {
  clientSocketMap[clientHandle] = serverHandle;
}

void ServerDB::remove(std::shared_ptr<uvw::TCPHandle> clientHandle) {
  clientSocketMap.erase(clientHandle);
}

bool ServerDB::contains(std::shared_ptr<uvw::TCPHandle> clientHandle) {
  return clientSocketMap.find(clientHandle) != clientSocketMap.end();
}

std::optional<std::shared_ptr<uvw::TCPHandle>>
ServerDB::get(std::shared_ptr<uvw::TCPHandle> clientHandle) {
  if (contains(clientHandle)) {
    return clientSocketMap[clientHandle];
  } else {
    return {};
  }
}

ServerDB &ServerDB::getDefault() {
  if (defaultDBInstance == nullptr) {
    defaultDBInstance = std::make_unique<ServerDB>();
  }
  return *defaultDBInstance.get();
}
