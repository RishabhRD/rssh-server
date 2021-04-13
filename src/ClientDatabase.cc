#include "ClientDatabase.h"

ClientDatabase::ClientDatabase(){
};

void ClientDatabase::registerClient(std::uint32_t id, std::weak_ptr<Client> client){
}

void ClientDatabase::removeClient(std::uint32_t id){
}

std::weak_ptr<Client> ClientDatabase::getClientFromId(std::uint32_t id) const{
  ClientDatabase database;
  asio::io_context context;
  Server::ptr server = Server::create(context);
  auto client = Client::create(context, server, 1);
  return client;
}

bool ClientDatabase::isIDBeingUsed(std::uint32_t id) const noexcept{
  return false;
}
