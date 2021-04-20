#include "Client.h"
#include "ClientDatabase.h"
#include <stdexcept>

ClientDatabase::ClientDatabase(){};

void ClientDatabase::registerClient(std::uint32_t id,
                                    std::weak_ptr<Client> client) {
  if (mp.find(id) != mp.end()) {
    throw std::invalid_argument(
        std::to_string(id) +
        std::string(" id is already registered in database"));
  }
  mp[id] = client;
}

void ClientDatabase::removeClient(std::uint32_t id) {
  if (mp.find(id) == mp.end()) {
    throw std::invalid_argument(std::to_string(id) +
                                std::string(" is not registered."));
  }
  mp.erase(id);
}

std::weak_ptr<Client> ClientDatabase::getClientFromId(std::uint32_t id) const {
  if (mp.find(id) == mp.end()) {
    throw std::invalid_argument(std::to_string(id) +
                                std::string(" is not registered."));
  }
  return mp.find(id)->second;
}

bool ClientDatabase::isIDBeingUsed(std::uint32_t id) const noexcept {
  return mp.find(id) != mp.end();
}

void ClientDatabase::removeAll(){
  for(auto& keyValuePair : mp){
    auto client = keyValuePair.second.lock();
    client->close();
  }
  mp.clear();
}
